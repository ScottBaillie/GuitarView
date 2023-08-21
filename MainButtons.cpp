///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

///////////////////////////////////////////////////////////////////

void
MainButtons::init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app)
{
	m_clearButton = builder->get_widget<Gtk::Button>("clear_button");
	m_expandButton = builder->get_widget<Gtk::Button>("expand_button");
	m_mr1Button = builder->get_widget<Gtk::Button>("mr1");
	m_mr2Button = builder->get_widget<Gtk::Button>("mr2");
	m_mr3Button = builder->get_widget<Gtk::Button>("mr3");
	m_mr4Button = builder->get_widget<Gtk::Button>("mr4");
	m_ms1Button = builder->get_widget<Gtk::Button>("ms1");
	m_ms2Button = builder->get_widget<Gtk::Button>("ms2");
	m_ms3Button = builder->get_widget<Gtk::Button>("ms3");
	m_ms4Button = builder->get_widget<Gtk::Button>("ms4");

	m_clearButton->signal_clicked().connect(sigc::mem_fun(*this, &MainButtons::clearButtonClicked));
	m_expandButton->signal_clicked().connect(sigc::mem_fun(*this, &MainButtons::expandButtonClicked));
	m_mr1Button->signal_clicked().connect(sigc::mem_fun(*this, &MainButtons::mr1ButtonClicked));
	m_mr2Button->signal_clicked().connect(sigc::mem_fun(*this, &MainButtons::mr2ButtonClicked));
	m_mr3Button->signal_clicked().connect(sigc::mem_fun(*this, &MainButtons::mr3ButtonClicked));
	m_mr4Button->signal_clicked().connect(sigc::mem_fun(*this, &MainButtons::mr4ButtonClicked));
	m_ms1Button->signal_clicked().connect(sigc::mem_fun(*this, &MainButtons::ms1ButtonClicked));
	m_ms2Button->signal_clicked().connect(sigc::mem_fun(*this, &MainButtons::ms2ButtonClicked));
	m_ms3Button->signal_clicked().connect(sigc::mem_fun(*this, &MainButtons::ms3ButtonClicked));
	m_ms4Button->signal_clicked().connect(sigc::mem_fun(*this, &MainButtons::ms4ButtonClicked));

	m_memory1.resize(g_num_strings);
	for (auto & m : m_memory1) m.resize(g_num_frets);
	m_memory2.resize(g_num_strings);
	for (auto & m : m_memory2) m.resize(g_num_frets);
	m_memory3.resize(g_num_strings);
	for (auto & m : m_memory3) m.resize(g_num_frets);
	m_memory4.resize(g_num_strings);
	for (auto & m : m_memory4) m.resize(g_num_frets);
}

//////////////////////////////////////////////////////////////////

void
MainButtons::clearButtonClicked()
{
	m_parent.m_guitarModel.clear();
	m_parent.m_neckView.m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
MainButtons::expandButtonClicked()
{
	m_parent.m_guitarModel.expand();
	m_parent.m_neckView.m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
MainButtons::ms1ButtonClicked()
{
	m_memory1 = m_parent.m_guitarModel.getMarkerList();
}

///////////////////////////////////////////////////////////////////

void
MainButtons::ms2ButtonClicked()
{
	m_memory2 = m_parent.m_guitarModel.getMarkerList();
}

///////////////////////////////////////////////////////////////////

void
MainButtons::ms3ButtonClicked()
{
	m_memory3 = m_parent.m_guitarModel.getMarkerList();
}

///////////////////////////////////////////////////////////////////

void
MainButtons::ms4ButtonClicked()
{
	m_memory4 = m_parent.m_guitarModel.getMarkerList();
}

///////////////////////////////////////////////////////////////////

void
MainButtons::mr1ButtonClicked()
{
	m_parent.m_guitarModel.setMarkerList(m_memory1);
	m_parent.m_neckView.m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
MainButtons::mr2ButtonClicked()
{
	m_parent.m_guitarModel.setMarkerList(m_memory2);
	m_parent.m_neckView.m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
MainButtons::mr3ButtonClicked()
{
	m_parent.m_guitarModel.setMarkerList(m_memory3);
	m_parent.m_neckView.m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
MainButtons::mr4ButtonClicked()
{
	m_parent.m_guitarModel.setMarkerList(m_memory4);
	m_parent.m_neckView.m_drawingArea->queue_draw();

	m_parent.m_neckView.m_neckPopover->set_offset(0, -100);
	m_parent.m_neckView.m_neckPopover->popup();
}

///////////////////////////////////////////////////////////////////
