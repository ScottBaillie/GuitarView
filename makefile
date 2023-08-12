

all:
	gtk4-builder-tool simplify --3to4 GuitarAppUi.glade 2>/dev/null | grep -v shadow-type | grep -v label-yalign > GuitarAppUi.ui
	g++ -o guitar_view *.cpp `pkgconf --cflags gtkmm-4.0` `pkgconf --libs gtkmm-4.0`


clean:
	rm -f guitar_view
	rm -f GuitarAppUi.ui
 
