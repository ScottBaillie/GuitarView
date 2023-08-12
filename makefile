

all:
	gtk4-builder-tool simplify --3to4 GuitarAppUi.glade > GuitarAppUi.tmp1
	cat GuitarAppUi.tmp1 | grep -v shadow-type > GuitarAppUi.tmp2
	cat GuitarAppUi.tmp2 | grep -v label-yalign > GuitarAppUi.ui
	rm -f GuitarAppUi.tmp1
	rm -f GuitarAppUi.tmp2
	g++ -o guitar_view *.cpp `pkgconf --cflags gtkmm-4.0` `pkgconf --libs gtkmm-4.0`


clean:
	rm -f guitar_view
	rm -f GuitarAppUi.tmp1
	rm -f GuitarAppUi.tmp2
	rm -f GuitarAppUi.ui
 
