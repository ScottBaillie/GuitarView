///////////////////////////////////////////////////////////////////

#include "GuitarView.h"

///////////////////////////////////////////////////////////////////

const uint32_t g_num_frets = 25;
const uint32_t g_num_strings = 6;

///////////////////////////////////////////////////////////////////

const Gdk::RGBA g_col_string1(0.725,0.710,0.663);
const Gdk::RGBA g_col_string2(0.710,0.695,0.663);
const Gdk::RGBA g_col_string3(0.700,0.680,0.655);
const Gdk::RGBA g_col_string4(0.460,0.410,0.370);
const Gdk::RGBA g_col_string5(0.400,0.380,0.348);
const Gdk::RGBA g_col_string6(0.388,0.349,0.341);
const Gdk::RGBA g_col_fretboard(0.696,0.476,0.339);
const Gdk::RGBA g_col_fret(0.527,0.500,0.425);

typedef const Gdk::RGBA* PRGB;
PRGB g_string_col[g_num_strings] = { &g_col_string1, &g_col_string2, &g_col_string3, &g_col_string4, &g_col_string5, &g_col_string6 };

const double g_string_ymin = 0.1;
const double g_string_step = 0.155;
const double g_fretgap_fac = 0.074;
const double g_factor = 1.05946309436;

///////////////////////////////////////////////////////////////////

void
NeckView::init(Glib::RefPtr<Gtk::Builder> & builder, Glib::RefPtr<Gtk::Application> & app)
{
	m_drawingArea = builder->get_widget<Gtk::DrawingArea>("drawing_area");
	m_noteLabel = builder->get_widget<Gtk::Label>("note_label");

	//
	m_neckPopover = builder->get_widget<Gtk::PopoverMenu>("neck_popover");

	Glib::RefPtr<Gio::SimpleAction> action = app->add_action("neck_popover_action");
	action->set_enabled(true);
	action->signal_activate().connect(sigc::mem_fun(*this, &NeckView::neckPopoverActivate));

	Glib::RefPtr<Gio::Menu> menumodel = Gio::Menu::create();
	menumodel->append("Label1", "app.neck_popover_action");
	menumodel->append("Label2", "app.neck_popover_action");
	m_neckPopover->set_menu_model(menumodel);
	//

	m_drawingArea->set_draw_func(sigc::mem_fun(*this, &NeckView::on_draw));

	m_mtController = Gtk::EventControllerMotion::create();
	m_drawingArea->add_controller(m_mtController);
	m_mtController->signal_motion().connect(sigc::mem_fun(*this, &NeckView::drawingAreaMotion));

	m_gcController = Gtk::GestureClick::create();
	m_drawingArea->add_controller(m_gcController);
	m_gcController->signal_pressed().connect(sigc::mem_fun(*this, &NeckView::drawingAreaClicked));

	m_neckPopover->set_parent(*m_drawingArea);
	// call unparent() to undo this.

}

//////////////////////////////////////////////////////////////////

void
NeckView::neckPopoverActivate(const Glib::VariantBase& parameter)
{
}

//////////////////////////////////////////////////////////////////

void
NeckView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
	m_width = width;
	m_height = height;

	//
	// Background , i.e. the fret board.
	//
	cr->rectangle(0, 0, width, height);
	Gdk::Cairo::set_source_rgba(cr, g_col_fretboard);
	cr->fill();

	//
	// The frets.
	//
	double fretpos = 0;
	const double fretwidth = width*0.0035;
	double fretgap = width*g_fretgap_fac;
	for (uint32_t u0=0; u0<g_num_frets; u0++) {
		cr->rectangle(fretpos, 0, fretwidth, height);
		Gdk::Cairo::set_source_rgba(cr, g_col_fret);
		cr->fill();
		if ((u0==2) || (u0==6) || (u0==8) || (u0==14) || (u0==16)  || (u0==23)) {
			cr->arc(fretpos+(fretgap/2.0), height , 4, 0, 2*M_PI);
			Gdk::Cairo::set_source_rgba(cr, Gdk::RGBA(0,0,0));
			cr->fill();
		}
		if ((u0==4) || (u0==11)) {
			cr->arc(fretpos+(fretgap/2.0)-5, height , 4, 0, 2*M_PI);
			Gdk::Cairo::set_source_rgba(cr, Gdk::RGBA(0,0,0));
			cr->fill();
			cr->arc(fretpos+(fretgap/2.0)+5, height , 4, 0, 2*M_PI);
			Gdk::Cairo::set_source_rgba(cr, Gdk::RGBA(0,0,0));
			cr->fill();
		}
		fretpos += fretgap;
		fretgap = fretgap/g_factor;
	}

	//
	// The strings.
	//
	const double sy = g_string_ymin*height;
	const double ss = g_string_step*height;
	double sw[g_num_strings] = { 0.007*height, 0.008*height, 0.0085*height, 0.012*height, 0.014*height, 0.017*height};

	for (uint32_t u0=0; u0<g_num_strings; u0++) {
		cr->rectangle(fretwidth, sy+(u0*ss), width, sw[u0]);
		Gdk::Cairo::set_source_rgba(cr, *g_string_col[u0]);
		cr->fill();
	}

	const GuitarModel::MarkerList & markerList = m_parent.m_guitarModel.getMarkerList();

	//
	// The markers.
	//

	int wl = width;
	if (width<900) wl = 900;
	const double wf = 0.0055 + 0.003*(1.0-((wl-900)/900.0));
	const double radius = width*wf;
	double string_pos;

	for (uint32_t u0=0; u0<markerList.size(); u0++) {
		string_pos = sy+(u0*ss);
		fretpos = 0;
		fretgap = width*g_fretgap_fac;
		if (markerList[u0][0].type != 0) {
			cr->arc(fretwidth/2.0, string_pos+(sw[u0]/2.0), radius, 0, 2*M_PI);
			Gdk::Cairo::set_source_rgba(cr, Gdk::RGBA(1.0,0,0));
			cr->fill();
		}
		for (uint32_t u1=1; u1<markerList[u0].size(); u1++) {
			const GuitarModel::Marker & marker = markerList[u0][u1];
			if (marker.type != 0) {
				cr->arc(fretpos+(fretgap/2.0), string_pos+(sw[u0]/2.0), radius, 0, 2*M_PI);
				Gdk::Cairo::set_source_rgba(cr, Gdk::RGBA(1.0,0,0));
				cr->fill();
			}
			fretpos += fretgap;
			fretgap = fretgap/g_factor;
		}
	}
}

///////////////////////////////////////////////////////////////////

void
NeckView::drawingAreaClicked(int n_press, double x, double y)
{
	uint32_t string = getString(y);
	uint32_t fret = getFret(x);

	m_parent.m_guitarModel.toggleMarker(string, fret);

	m_drawingArea->queue_draw();
}

///////////////////////////////////////////////////////////////////

void
NeckView::drawingAreaMotion(double x, double y)
{
	uint32_t string = getString(y);
	uint32_t fret = getFret(x);
	std::string note = m_parent.m_guitarModel.getNoteStr(string, fret);
	if (note.size()==1) note += ' ';
	std::string text = " Note : " + note + " ";
	m_noteLabel->set_text(text);
}

///////////////////////////////////////////////////////////////////

uint32_t
NeckView::getString(double y)
{
	double sy = g_string_ymin*m_height;
	double ss = g_string_step*m_height;
	double string_lim;

	for (uint32_t u0=0; u0<g_num_strings; u0++) {
		string_lim = sy + (u0*ss) + (0.5*ss);
		if (y < string_lim) {
			return(u0);
		}
	}

	return(g_num_strings-1);
}

///////////////////////////////////////////////////////////////////

uint32_t
NeckView::getFret(double x)
{
	double fretpos = 0;
	double fretgap = m_width*g_fretgap_fac;

	if (x < (fretgap/3.0)) {
		return(0);
	}

	for (uint32_t u0=1; u0<g_num_frets; u0++) {
		fretpos += fretgap;
		if (x < fretpos) {
			return(u0);
		}
		fretgap = fretgap/g_factor;
	}
	return(g_num_frets-1);
}

///////////////////////////////////////////////////////////////////
