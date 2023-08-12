///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

///////////////////////////////////////////////////////////////////

class GuitarApp
{
public:
	int main(int argc, char**argv);

private:
	void activate();

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
		builder->add_from_file("/home/sbaillie/projects/guitarApp/GuitarAppUi.ui");
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

	m_guitarView.init(builder);

	pWindow->show();
}

///////////////////////////////////////////////////////////////////

int main(int argc, char**argv)
{
	GuitarApp guitarApp;
	return(guitarApp.main(argc,argv));
}

///////////////////////////////////////////////////////////////////
