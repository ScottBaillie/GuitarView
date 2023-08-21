///////////////////////////////////////////////////////////////////

#include "GuitarModel.h"

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <iostream> // For std::cout

///////////////////////////////////////////////////////////////////

extern const uint32_t g_num_frets;
extern const uint32_t g_num_strings;

///////////////////////////////////////////////////////////////////

class GuitarView;

///////////////////////////////////////////////////////////////////

class PhysicalView
{
public:
	PhysicalView(GuitarView & parent)
		: m_parent(parent)
	{
	}

	void init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app);

	void phyApplyButtonClicked();

public:
	GuitarView &			m_parent;
	Gtk::Button*			m_phyApplyButton;
	Gtk::TreeView*			m_phyTreeView;
	Glib::RefPtr<Gtk::ListStore>	m_phyModel;
};

///////////////////////////////////////////////////////////////////

class ChordView
{
public:
	ChordView(GuitarView & parent)
		: m_parent(parent)
	{
	}

	void init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app);

	void chordsApplyButtonClicked();

public:
	GuitarView &			m_parent;
	Gtk::Button*			m_chordsApplyButton;
	Gtk::ComboBoxText*		m_chordsNoteCombo;
	Gtk::TreeView*			m_chordsTreeView;
	Glib::RefPtr<Gtk::ListStore>	m_chordsModel;
};

///////////////////////////////////////////////////////////////////

class ScaleView
{
public:
	ScaleView(GuitarView & parent)
		: m_parent(parent)
	{
	}

	void init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app);
	void scalesApplyButtonClicked();

public:
	GuitarView &			m_parent;
	Gtk::Button*			m_scalesApplyButton;
	Gtk::ComboBoxText*		m_scalesNoteCombo;
	Gtk::TreeView*			m_scalesTreeView;
	Glib::RefPtr<Gtk::ListStore>	m_scalesModel;
};

///////////////////////////////////////////////////////////////////

class Search1View
{
public:
	Search1View(GuitarView & parent)
		: m_parent(parent)
	{
	}

	void init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app);
	void search1SearchButtonClicked();
	void search1ApplyButtonClicked();

public:
	GuitarView &			m_parent;
	Gtk::Button*			m_search1SearchButton;
	Gtk::Button*			m_search1ApplyButton;

	Gtk::CheckButton*		m_search1_2CheckButton;
	Gtk::CheckButton*		m_search1_3CheckButton;
	Gtk::CheckButton*		m_search1_4CheckButton;
	Gtk::CheckButton*		m_search1_5CheckButton;
	Gtk::CheckButton*		m_search1_6CheckButton;
	Gtk::CheckButton*		m_search1_7CheckButton;
	Gtk::CheckButton*		m_search1_8CheckButton;
	Gtk::CheckButton*		m_search1_phyCheckButton;
	Gtk::CheckButton*		m_search1_chordsCheckButton;
	Gtk::CheckButton*		m_search1_scalesCheckButton;
	Gtk::CheckButton*		m_search1_inexactCheckButton;

	Gtk::ComboBoxText*		m_search1_inexactCombo;

	Gtk::TreeView*			m_search1TreeView;
	Glib::RefPtr<Gtk::ListStore>	m_search1Model;
};

///////////////////////////////////////////////////////////////////

class NeckView
{
public:
	NeckView(GuitarView & parent)
		: m_parent(parent)
	{
	}

	void init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app);

	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
	void drawingAreaClicked(int n_press, double x, double y);
	void drawingAreaMotion(double x, double y);

	void neckPopoverActivate(const Glib::VariantBase& parameter);

	uint32_t getString(double y); /* strings 0 -> 5 */
	uint32_t getFret(double x); /* frets 0 -> 24 */

public:
	GuitarView &			m_parent;

	Gtk::DrawingArea*		m_drawingArea;
	Gtk::Label*			m_noteLabel;
	Gtk::PopoverMenu*		m_neckPopover;

	int				m_width;
	int				m_height;
	Glib::RefPtr<Gtk::GestureClick> m_gcController;
	Glib::RefPtr<Gtk::EventControllerMotion> m_mtController;
};

///////////////////////////////////////////////////////////////////

class MainButtons
{
public:
	MainButtons(GuitarView & parent)
		: m_parent(parent)
	{
	}

	void init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app);

	void clearButtonClicked();
	void expandButtonClicked();
	void mr1ButtonClicked();
	void mr2ButtonClicked();
	void mr3ButtonClicked();
	void mr4ButtonClicked();
	void ms1ButtonClicked();
	void ms2ButtonClicked();
	void ms3ButtonClicked();
	void ms4ButtonClicked();

public:
	GuitarView &		m_parent;
	Gtk::Button*		m_clearButton;
	Gtk::Button*		m_expandButton;
	Gtk::Button*		m_mr1Button;
	Gtk::Button*		m_mr2Button;
	Gtk::Button*		m_mr3Button;
	Gtk::Button*		m_mr4Button;
	Gtk::Button*		m_ms1Button;
	Gtk::Button*		m_ms2Button;
	Gtk::Button*		m_ms3Button;
	Gtk::Button*		m_ms4Button;

	GuitarModel::MarkerList	m_memory1;
	GuitarModel::MarkerList	m_memory2;
	GuitarModel::MarkerList	m_memory3;
	GuitarModel::MarkerList	m_memory4;
};

///////////////////////////////////////////////////////////////////

class GuitarView
{
public:
	GuitarView()
		: m_mainButtons(*this)
		, m_physicalView(*this)
		, m_chordView(*this)
		, m_scaleView(*this)
		, m_search1View(*this)
		, m_neckView(*this)
	{
	}

	void init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app);
	void shutdown();

public:
	Glib::RefPtr<Gtk::Builder>	m_builder;
	Glib::RefPtr<Gtk::Application>	m_app;

	MainButtons			m_mainButtons;
	PhysicalView			m_physicalView;
	ChordView			m_chordView;
	ScaleView			m_scaleView;
	Search1View			m_search1View;
	NeckView			m_neckView;

	GuitarModel			m_guitarModel;
};

///////////////////////////////////////////////////////////////////
