#include "soal_common1.c"

// Make variable global

GtkWidget	*window;
GtkWidget	*fixed1;
GtkWidget	*button1;
GtkWidget	*buttonlink1;
GtkWidget	*button2;
GtkWidget	*label1;
GtkWidget	*entry1;
GtkWidget   *layout;
GtkWidget   *image;

GtkBuilder	*builder; 

char input[128];

void    css_set(GtkCssProvider *, GtkWidget *);

GtkAdjustment	*adjustment2;

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // init Gtk
	
	builder = gtk_builder_new_from_file ("main.glade");		//Menyambungkan dengan file glade
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window")); //connect window dengan window di glade
	
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //respon window

        gtk_builder_connect_signals(builder, NULL);
        
	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));				//Set widget fixed
	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));			//Set button1
	button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));			//Set button2
	buttonlink1 = GTK_WIDGET(gtk_builder_get_object(builder, "buttonlink1"));	//Set buttonlink1
	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));				//Set label1
	entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));				//Set entry1

	GtkCssProvider  *cssBtn1;			//set pointer CSS untuk button1
	GtkCssProvider  *cssBtnlnk1;		//set pointer CSS untuk buttonlink1
	GtkCssProvider  *csswindow;			//set pointer CSS untuk window

	cssBtn1 = gtk_css_provider_new();		//Membuat CSS baru
	cssBtnlnk1 = gtk_css_provider_new();	//Membuat CSS baru
	csswindow = gtk_css_provider_new();		//Membuat CSS baru

	gtk_css_provider_load_from_data(csswindow,
		"* { background-image: url('Delameta.png'); background-position:center;  background-repeat:repeat; background-size:50px 50px;}\n", 
		-1, NULL);
	css_set(csswindow, window);		//Input gambar ke window

	gtk_css_provider_load_from_data(cssBtn1,
		"* { background-image: radial-gradient(circle farthest-side at left bottom, red, yellow 50px, green);}", 
		-1, NULL);
	css_set(cssBtn1, button1);		//Warna untuk button1

	gtk_css_provider_load_from_data(cssBtnlnk1,
		"* { background-image: linear-gradient(to top right, blue 20%, #f0f 80%); }", 
		-1, NULL);
	css_set(cssBtnlnk1, buttonlink1);		//Warna untuk buttonlink1

	gtk_widget_show(window);			//Print window

	gtk_main();

	return EXIT_SUCCESS;
	}


//SET css
void    css_set(GtkCssProvider * cssProvider, GtkWidget *g_widget) {

        GtkStyleContext *context;

        context = gtk_widget_get_style_context(g_widget);

        gtk_style_context_add_provider (context,
                GTK_STYLE_PROVIDER(cssProvider),
                GTK_STYLE_PROVIDER_PRIORITY_USER);

        gtk_style_context_save (context);
        }

//function ketika button1 ditekan
void	on_button1_clicked (GtkButton *b) {
	
	get_data_from_rawdata(input);
	calender();
	}
	
//function ketika button2 ditekan
void	on_button2_clicked (GtkButton *b) {

	gtk_widget_destroy(window);
	
	}
	
//function ketika entry1 berubah	
void	on_entry1_changed(GtkEntry *e) {
	sprintf(input, "%s", gtk_entry_get_text(e));
	
	}

// Compile : gcc -Wno-format -o GUI GUI.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

