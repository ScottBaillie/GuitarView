///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

///////////////////////////////////////////////////////////////////

void
TuningView::init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app)
{
	m_tuningNumString = builder->get_widget<Gtk::ComboBoxText>("tuning_numstring");
	m_tuningSelect = builder->get_widget<Gtk::ComboBoxText>("tuning_select");
	m_tuningTreeView = builder->get_widget<Gtk::TreeView>("tuning_treeview");

	m_tuningNumString->set_active_text("6 String");
	m_tuningSelect->set_active_text("Standard Tuning");

	Gtk::TreeModelColumn<Glib::ustring> strcol1;
	Gtk::TreeModelColumn<Glib::ustring> strcol2;
	Gtk::TreeModelColumnRecord columns;
	columns.add(strcol1);
	columns.add(strcol2);
	m_tuningModel = Gtk::ListStore::create(columns);
	m_tuningTreeView->set_model(m_tuningModel);
	m_tuningTreeView->set_headers_visible();
	static Gtk::TreeViewColumn column1("Number of Strings", strcol1);
	m_tuningTreeView->append_column(column1);
	static Gtk::TreeViewColumn column2("Tuning", strcol2);
	m_tuningTreeView->append_column(column2);

	auto iter = m_tuningModel->append();
	iter->set_value(0, std::string("6"));
	iter->set_value(1, std::string("Standard"));

	iter = m_tuningModel->append();
	iter->set_value(0, std::string("6"));
	iter->set_value(1, std::string("Drop"));

	iter = m_tuningModel->append();
	iter->set_value(0, std::string("7"));
	iter->set_value(1, std::string("Standard"));

	iter = m_tuningModel->append();
	iter->set_value(0, std::string("7"));
	iter->set_value(1, std::string("Drop"));
}

///////////////////////////////////////////////////////////////////
