
#include "GuitarModel.h"

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <iostream> // For std::cout

class GuitarView
{
public:
	void init(Glib::RefPtr<Gtk::Builder> & builder);

private:
	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
	void drawingAreaClicked(int n_press, double x, double y);
	void drawingAreaMotion(double x, double y);

	void clearButtonClicked();
	void expandButtonClicked();
	void phyApplyButtonClicked();
	void scalesApplyButtonClicked();
	void chordsApplyButtonClicked();
	void search1SearchButtonClicked();
	void search1ApplyButtonClicked();
	void mr1ButtonClicked();
	void mr2ButtonClicked();
	void mr3ButtonClicked();
	void mr4ButtonClicked();
	void ms1ButtonClicked();
	void ms2ButtonClicked();
	void ms3ButtonClicked();
	void ms4ButtonClicked();

	uint32_t getString(double y); /* strings 0 -> 5 */
	uint32_t getFret(double x); /* frets 0 -> 24 */

	void init_buttons();
	void init_phyTreeView();
	void init_chordsTreeView();
	void init_scalesTreeView();
	void init_search1TreeView();

private:
	Glib::RefPtr<Gtk::Builder>	m_builder;
	Gtk::DrawingArea*		m_drawingArea;

	Gtk::Label*			m_noteLabel;

	Gtk::Button*			m_clearButton;
	Gtk::Button*			m_expandButton;
	Gtk::Button*			m_phyApplyButton;
	Gtk::Button*			m_scalesApplyButton;
	Gtk::Button*			m_chordsApplyButton;
	Gtk::Button*			m_search1SearchButton;
	Gtk::Button*			m_search1ApplyButton;
	Gtk::Button*			m_mr1Button;
	Gtk::Button*			m_mr2Button;
	Gtk::Button*			m_mr3Button;
	Gtk::Button*			m_mr4Button;
	Gtk::Button*			m_ms1Button;
	Gtk::Button*			m_ms2Button;
	Gtk::Button*			m_ms3Button;
	Gtk::Button*			m_ms4Button;

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

	Gtk::ComboBoxText*		m_chordsNoteCombo;
	Gtk::ComboBoxText*		m_scalesNoteCombo;

	Gtk::TreeView*			m_phyTreeView;
	Gtk::TreeView*			m_chordsTreeView;
	Gtk::TreeView*			m_scalesTreeView;
	Gtk::TreeView*			m_search1TreeView;

	int				m_width;
	int				m_height;
	Glib::RefPtr<Gtk::GestureClick> m_gcController;
	Glib::RefPtr<Gtk::EventControllerMotion> m_mtController;
	Glib::RefPtr<Gtk::ListStore>	m_phyModel;
	Glib::RefPtr<Gtk::ListStore>	m_chordsModel;
	Glib::RefPtr<Gtk::ListStore>	m_scalesModel;
	Glib::RefPtr<Gtk::ListStore>	m_search1Model;

	GuitarModel::MarkerList		m_memory1;
	GuitarModel::MarkerList		m_memory2;
	GuitarModel::MarkerList		m_memory3;
	GuitarModel::MarkerList		m_memory4;

	GuitarModel			m_guitarModel;
};


