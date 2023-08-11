///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

///////////////////////////////////////////////////////////////////

void
GuitarView::clearButtonClicked()
{
	m_guitarModel.clear();
	m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::expandButtonClicked()
{
	m_guitarModel.expand();
	m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::phyApplyButtonClicked()
{
	Glib::RefPtr<Gtk::TreeSelection> ts = m_phyTreeView->get_selection();
	if (!ts) return;
	if (ts->count_selected_rows()==0) return;
	Gtk::TreeModel::iterator i = ts->get_selected();
	if (!i) return;
	std::string name;
	i->get_value(0, name);

	m_guitarModel.applyPhysical(name);
	m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::chordsApplyButtonClicked()
{
	Glib::RefPtr<Gtk::TreeSelection> ts = m_chordsTreeView->get_selection();
	if (ts->count_selected_rows()==0) return;
	Gtk::TreeModel::iterator i = ts->get_selected();
	std::string name;
	i->get_value(0, name);
	Glib::ustring note = m_chordsNoteCombo->get_active_text();

	m_guitarModel.applyChord(name, note);
	m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::scalesApplyButtonClicked()
{
	Glib::RefPtr<Gtk::TreeSelection> ts = m_scalesTreeView->get_selection();
	if (ts->count_selected_rows()==0) return;
	Gtk::TreeModel::iterator i = ts->get_selected();
	std::string name;
	i->get_value(0, name);
	Glib::ustring note = m_scalesNoteCombo->get_active_text();

	m_guitarModel.applyScale(name, note);
	m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::search1SearchButtonClicked()
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

	m_guitarModel.search(
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
GuitarView::search1ApplyButtonClicked()
{
}

///////////////////////////////////////////////////////////////////

void
GuitarView::ms1ButtonClicked()
{
	m_memory1 = m_guitarModel.getMarkerList();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::ms2ButtonClicked()
{
	m_memory2 = m_guitarModel.getMarkerList();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::ms3ButtonClicked()
{
	m_memory3 = m_guitarModel.getMarkerList();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::ms4ButtonClicked()
{
	m_memory4 = m_guitarModel.getMarkerList();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::mr1ButtonClicked()
{
	m_guitarModel.setMarkerList(m_memory1);
	m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::mr2ButtonClicked()
{
	m_guitarModel.setMarkerList(m_memory2);
	m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::mr3ButtonClicked()
{
	m_guitarModel.setMarkerList(m_memory3);
	m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::mr4ButtonClicked()
{
	m_guitarModel.setMarkerList(m_memory4);
	m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
GuitarView::init_buttons()
{
	m_clearButton->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::clearButtonClicked));
	m_expandButton->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::expandButtonClicked));
	m_phyApplyButton->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::phyApplyButtonClicked));
	m_scalesApplyButton->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::scalesApplyButtonClicked));
	m_chordsApplyButton->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::chordsApplyButtonClicked));
	m_search1SearchButton->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::search1SearchButtonClicked));
	m_search1ApplyButton->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::search1ApplyButtonClicked));
	m_mr1Button->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::mr1ButtonClicked));
	m_mr2Button->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::mr2ButtonClicked));
	m_mr3Button->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::mr3ButtonClicked));
	m_mr4Button->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::mr4ButtonClicked));
	m_ms1Button->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::ms1ButtonClicked));
	m_ms2Button->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::ms2ButtonClicked));
	m_ms3Button->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::ms3ButtonClicked));
	m_ms4Button->signal_clicked().connect(sigc::mem_fun(*this, &GuitarView::ms4ButtonClicked));
}

///////////////////////////////////////////////////////////////////

void
GuitarView::init_phyTreeView()
{
	Gtk::TreeModelColumn<Glib::ustring> strcol;
	Gtk::TreeModelColumnRecord columns;
	columns.add(strcol);
	m_phyModel = Gtk::ListStore::create(columns);
	m_phyTreeView->set_model(m_phyModel);
	m_phyTreeView->set_headers_visible();
	static Gtk::TreeViewColumn column1("Physical Name", strcol);
	m_phyTreeView->append_column(column1);

	Glib::RefPtr<Gtk::TreeSelection> ts = m_phyTreeView->get_selection();

	std::vector<std::string> names;
	m_guitarModel.getPhysicalNames(names);
	for (const auto & name : names) {
		auto iter = m_phyModel->append();
		iter->set_value(0, name);
		ts->select(iter);
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarView::init_chordsTreeView()
{
	Gtk::TreeModelColumn<Glib::ustring> strcol;
	Gtk::TreeModelColumnRecord columns;
	columns.add(strcol);
	m_chordsModel = Gtk::ListStore::create(columns);
	m_chordsTreeView->set_model(m_chordsModel);
	m_chordsTreeView->set_headers_visible();
	static Gtk::TreeViewColumn column1("Chord Name", strcol);
	m_chordsTreeView->append_column(column1);

	Glib::RefPtr<Gtk::TreeSelection> ts = m_chordsTreeView->get_selection();

	std::vector<std::string> names;
	m_guitarModel.getChordNames(names);
	for (const auto & name : names) {
		auto iter = m_chordsModel->append();
		iter->set_value(0, name);
		ts->select(iter);
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarView::init_scalesTreeView()
{
	Gtk::TreeModelColumn<Glib::ustring> strcol;
	Gtk::TreeModelColumnRecord columns;
	columns.add(strcol);
	m_scalesModel = Gtk::ListStore::create(columns);
	m_scalesTreeView->set_model(m_scalesModel);
	m_scalesTreeView->set_headers_visible();
	static Gtk::TreeViewColumn column1("Scale Name", strcol);
	m_scalesTreeView->append_column(column1);

	Glib::RefPtr<Gtk::TreeSelection> ts = m_scalesTreeView->get_selection();

	std::vector<std::string> names;
	m_guitarModel.getScaleNames(names);
	for (const auto & name : names) {
		auto iter = m_scalesModel->append();
		iter->set_value(0, name);
		ts->select(iter);
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarView::init_search1TreeView()
{
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

///////////////////////////////////////////////////////////////////
