///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

///////////////////////////////////////////////////////////////////

void
ScaleView::init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app)
{
	m_scalesApplyButton = builder->get_widget<Gtk::Button>("scales_apply");
	m_scalesNoteCombo = builder->get_widget<Gtk::ComboBoxText>("scales_note");
	m_scalesTreeView = builder->get_widget<Gtk::TreeView>("scales_treeview");

	m_scalesApplyButton->signal_clicked().connect(sigc::mem_fun(*this, &ScaleView::scalesApplyButtonClicked));

	m_scalesNoteCombo->set_active_text("E");

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
	m_parent.m_guitarModel.getScaleNames(names);
	for (const auto & name : names) {
		auto iter = m_scalesModel->append();
		iter->set_value(0, name);
		ts->select(iter);
	}
}

//////////////////////////////////////////////////////////////////

void
ScaleView::scalesApplyButtonClicked()
{
	Glib::RefPtr<Gtk::TreeSelection> ts = m_scalesTreeView->get_selection();
	if (ts->count_selected_rows()==0) return;
	Gtk::TreeModel::iterator i = ts->get_selected();
	std::string name;
	i->get_value(0, name);
	Glib::ustring note = m_scalesNoteCombo->get_active_text();

	m_parent.m_guitarModel.applyScale(name, note);
	m_parent.m_neckView.m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////
