///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

///////////////////////////////////////////////////////////////////

void
GuitarView::init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app)
{
	m_builder = builder;
	m_app = app;

	m_guitarModel.init(g_num_strings,g_num_frets);
	m_guitarModel.setTuning("standard");

	m_mainButtons.init(m_builder, m_app);
	m_physicalView.init(m_builder, m_app);
	m_chordView.init(m_builder, m_app);
	m_scaleView.init(m_builder, m_app);
	m_search1View.init(m_builder, m_app);
	m_neckView.init(m_builder, m_app);
}

///////////////////////////////////////////////////////////////////

void
GuitarView::shutdown()
{
	m_neckView.m_neckPopover->unparent();
}

///////////////////////////////////////////////////////////////////
