///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

///////////////////////////////////////////////////////////////////

void
PhysicalView::init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app)
{
	m_phyTreeView = builder->get_widget<Gtk::TreeView>("phy_treeview");
	m_phyApplyButton = builder->get_widget<Gtk::Button>("phy_apply");

	m_phyApplyButton->signal_clicked().connect(sigc::mem_fun(*this, &PhysicalView::phyApplyButtonClicked));

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
	m_parent.m_guitarModel.getPhysicalNames(names);
	for (const auto & name : names) {
		auto iter = m_phyModel->append();
		iter->set_value(0, name);
		ts->select(iter);
	}
}

//////////////////////////////////////////////////////////////////

void
PhysicalView::phyApplyButtonClicked()
{
	Glib::RefPtr<Gtk::TreeSelection> ts = m_phyTreeView->get_selection();
	if (!ts) return;
	if (ts->count_selected_rows()==0) return;
	Gtk::TreeModel::iterator i = ts->get_selected();
	if (!i) return;
	std::string name;
	i->get_value(0, name);

	m_parent.m_guitarModel.applyPhysical(name);
	m_parent.m_neckView.m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////
