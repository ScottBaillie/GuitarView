///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

///////////////////////////////////////////////////////////////////

void
Search1View::init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app)
{
	m_search1TreeView = builder->get_widget<Gtk::TreeView>("search1_treeview");
	m_search1SearchButton = builder->get_widget<Gtk::Button>("search1_search");
	m_search1ApplyButton = builder->get_widget<Gtk::Button>("search1_apply");

	m_search1_2CheckButton = builder->get_widget<Gtk::CheckButton>("search1_2");
	m_search1_3CheckButton = builder->get_widget<Gtk::CheckButton>("search1_3");
	m_search1_4CheckButton = builder->get_widget<Gtk::CheckButton>("search1_4");
	m_search1_5CheckButton = builder->get_widget<Gtk::CheckButton>("search1_5");
	m_search1_6CheckButton = builder->get_widget<Gtk::CheckButton>("search1_6");
	m_search1_7CheckButton = builder->get_widget<Gtk::CheckButton>("search1_7");
	m_search1_8CheckButton = builder->get_widget<Gtk::CheckButton>("search1_8");
	m_search1_phyCheckButton = builder->get_widget<Gtk::CheckButton>("search1_phy");
	m_search1_chordsCheckButton = builder->get_widget<Gtk::CheckButton>("search1_chords");
	m_search1_scalesCheckButton = builder->get_widget<Gtk::CheckButton>("search1_scales");
	m_search1_inexactCheckButton = builder->get_widget<Gtk::CheckButton>("search1_inexact");

	m_search1_inexactCombo = builder->get_widget<Gtk::ComboBoxText>("search1_inexact_value");

	m_search1_inexactCombo->set_active_text("1");

	m_search1SearchButton->signal_clicked().connect(sigc::mem_fun(*this, &Search1View::search1SearchButtonClicked));
	m_search1ApplyButton->signal_clicked().connect(sigc::mem_fun(*this, &Search1View::search1ApplyButtonClicked));

	Gtk::TreeModelColumn<Glib::ustring> strcol1;
	Gtk::TreeModelColumn<Glib::ustring> strcol2;
	Gtk::TreeModelColumn<Glib::ustring> strcol3;
//	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > imagecol;
	Gtk::TreeModelColumnRecord columns;
	columns.add(strcol1);
	columns.add(strcol2);
	columns.add(strcol3);
	m_search1Model = Gtk::ListStore::create(columns);
	m_search1TreeView->set_model(m_search1Model);
	m_search1TreeView->set_headers_visible();

	static Gtk::TreeViewColumn column1("Pattern", strcol1);
	m_search1TreeView->append_column(column1);
	static Gtk::TreeViewColumn column2("Note", strcol2);
	m_search1TreeView->append_column(column2);
	static Gtk::TreeViewColumn column3("Name", strcol3);
	m_search1TreeView->append_column(column3);
}

//////////////////////////////////////////////////////////////////

void
Search1View::search1SearchButtonClicked()
{
	bool val_2 = m_search1_2CheckButton->get_active();
	bool val_3 = m_search1_3CheckButton->get_active();
	bool val_4 = m_search1_4CheckButton->get_active();
	bool val_5 = m_search1_5CheckButton->get_active();
	bool val_6 = m_search1_6CheckButton->get_active();
	bool val_7 = m_search1_7CheckButton->get_active();
	bool val_8 = m_search1_8CheckButton->get_active();
	bool val_phy = m_search1_phyCheckButton->get_active();
	bool val_chords = m_search1_chordsCheckButton->get_active();
	bool val_scales = m_search1_scalesCheckButton->get_active();
	bool val_inexact = m_search1_inexactCheckButton->get_active();

	std::string val_inexactval = m_search1_inexactCombo->get_active_text();

	std::vector<std::string> patternList;
	std::vector<std::string> noteList;
	std::vector<std::string> nameList;

	m_parent.m_guitarModel.search(
		patternList,
		noteList,
		nameList,
		val_2,
		val_3,
		val_4,
		val_5,
		val_6,
		val_7,
		val_8,
		val_phy,
		val_chords,
		val_scales,
		val_inexact,
		val_inexactval
		);

	m_search1Model->clear();

	for (uint32_t u0=0; u0<patternList.size(); u0++) {
		auto iter = m_search1Model->append();
		iter->set_value(0, patternList[u0]);
		iter->set_value(1, noteList[u0]);
		iter->set_value(2, nameList[u0]);
	}
}

///////////////////////////////////////////////////////////////////

void
Search1View::search1ApplyButtonClicked()
{
}

///////////////////////////////////////////////////////////////////
