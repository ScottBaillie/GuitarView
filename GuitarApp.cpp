///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

#include <gtkmm/stylecontext.h>

///////////////////////////////////////////////////////////////////

// CSS Styles to apply to widgets.

const std::string style = R"(
    frame {
        color: grey;
        border-style:solid;
        border-width: 4px;
        border-color: grey;
        background-color: white;
    }
)";

///////////////////////////////////////////////////////////////////

class GuitarApp
{
public:
	int main(int argc, char**argv);

private:
	void activate();
	void shutdown();

private:
	Glib::RefPtr<Gtk::Application> m_app;
	GuitarView	m_guitarView;
};

///////////////////////////////////////////////////////////////////

int
GuitarApp::main(int argc, char**argv)
{
	m_app = Gtk::Application::create();

	m_app->signal_activate().connect(sigc::mem_fun(*this, &GuitarApp::activate));
	m_app->signal_shutdown().connect(sigc::mem_fun(*this, &GuitarApp::shutdown));

	int ret = m_app->run();

	return ret;
}

///////////////////////////////////////////////////////////////////

void
GuitarApp::activate()
{
	// Load the XML file and instantiate its widgets:
	auto builder = Gtk::Builder::create();
	try
	{
		builder->add_from_file("GuitarAppUi.ui");
	}
	catch (const Glib::Error& error)
	{
		std::cout << "Error loading GuitarAppUi.glade: " << error.what() << std::endl;
		return;
	}
	
	// Get the GtkBuilder-instantiated window:
	auto pWindow = builder->get_widget<Gtk::ApplicationWindow>("main_window");
	if (!pWindow)
	{
		std::cout << "Could not get 'main_window' from the builder." << std::endl;
		return;
	}

	m_app->add_window(*pWindow);

	m_guitarView.init(builder, m_app);

	auto css = Gtk::CssProvider::create();
	css->load_from_data(style);
	Gtk::StyleContext::add_provider_for_display(pWindow->get_display(),css,GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	pWindow->show();
}

///////////////////////////////////////////////////////////////////

void
GuitarApp::shutdown()
{
	m_guitarView.shutdown();
}

///////////////////////////////////////////////////////////////////

int main(int argc, char**argv)
{
	GuitarApp guitarApp;
	return(guitarApp.main(argc,argv));
}

///////////////////////////////////////////////////////////////////
