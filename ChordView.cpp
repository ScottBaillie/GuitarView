///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

///////////////////////////////////////////////////////////////////

void
ChordView::init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app)
{
	m_chordsApplyButton = builder->get_widget<Gtk::Button>("chords_apply");
	m_chordsNoteCombo = builder->get_widget<Gtk::ComboBoxText>("chords_note");
	m_chordsTreeView = builder->get_widget<Gtk::TreeView>("chords_treeview");

	m_chordsApplyButton->signal_clicked().connect(sigc::mem_fun(*this, &ChordView::chordsApplyButtonClicked));

	m_chordsNoteCombo->set_active_text("E");

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
	m_parent.m_guitarModel.getChordNames(names);
	for (const auto & name : names) {
		auto iter = m_chordsModel->append();
		iter->set_value(0, name);
		ts->select(iter);
	}
}

//////////////////////////////////////////////////////////////////

void
ChordView::chordsApplyButtonClicked()
{
	Glib::RefPtr<Gtk::TreeSelection> ts = m_chordsTreeView->get_selection();
	if (ts->count_selected_rows()==0) return;
	Gtk::TreeModel::iterator i = ts->get_selected();
	std::string name;
	i->get_value(0, name);
	Glib::ustring note = m_chordsNoteCombo->get_active_text();

	m_parent.m_guitarModel.applyChord(name, note);
	m_parent.m_neckView.m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////
