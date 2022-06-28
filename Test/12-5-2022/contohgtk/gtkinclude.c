//Library
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

#define create_gtk_window() gtk_window_new(GTK_WINDOW_TOPLEVEL)

//deklarasi variable dan widget
int custom_box_index;
GtkWidget *custom_vbox,*custom_hbox;
GtkWidget *custom_box[9999];

static char *custom_css1,*custom_css2;
int custom_cssRedin[9999],custom_cssGreenin[9999],custom_cssBluein[9999];
int custom_cssRedout[9999],custom_cssGreenout[9999],custom_cssBlueout[9999];

//css script untuk pilihan warna innerColour
static char *css1 =
	".white { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n"
    ".white:hover { background-color: rgb(128,57,0); }\n"
    ".darkcyan { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n"
    ".darkcyan:hover { background-color: darkcyan; }\n"
    ".red { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n"
    ".red:hover { background-color: red; }\n"
    ".blue { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n"
    ".blue:hover { background-color: blue; }\n"
    ".green { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n"
    ".green:hover { background-color: green; }\n"
    ".yellow { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n"
    ".yellow:hover { background-color: yellow; }\n"
    ".transparent { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n"
    ".transparent:hover { background-color: transparent; }\n"
    ;

//css script untuk pilihan warna outtercolour
static char *css2 =
    ".white1 { background-image: none; background-color: white; border: none; border-radius: 22px;}\n"
    ".darkcyan1 { background-image: none; background-color: darkcyan; border: none; border-radius: 22px;}\n"
    ".red1 { background-image: none; background-color: red; border: none; border-radius: 22px;}\n"
    ".blue1 { background-image: none; background-color: blue; border: none; border-radius: 22px;}\n"
    ".green1 { background-image: none; background-color: green; border: none; border-radius: 22px;}\n"
    ".yellow1 { background-image: none; background-color: yellow; border: none; border-radius: 22px;}\n"
    ".transparent1 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n"
    ;

//no action function
void none(){}

//function menggabungkan 2 string
char* gabung_kata(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 10); 
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

//function untuk convert integer to string
char *IntToStr(int x){
	char *str=(char *)malloc(1 * sizeof (char));
	sprintf(str, "%d", x);
	return str;
}

//Setting CSS
static void css_add(char *css)
    {
    /* CSS */
    GError *error = NULL;
    GtkStyleContext *context;
	//Buat css provider
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, strlen(css), &error);
    if (error != NULL)	//validasi css data
        {
        fprintf(stderr, "CSS: %s\n", error->message);
        }
	//Menggabungkan css provider dengan current screen
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
    }


void apply_theme(){
	css_add(css1);
    css_add(css2);
    css_add(custom_css1);
    css_add(custom_css2);
}

//Membuat tombol basic (tanpa warna, dan gambar)
static void basic_create_button(GtkWidget *nama_box,char *isi_label,void (*f)){
	GtkWidget *tombol;	//deklarasi widget
	tombol = gtk_button_new_with_label(isi_label);	//Tombol dan isi label
	gtk_box_pack_start(GTK_BOX(nama_box), tombol, TRUE, TRUE, 0); //menambahkan tombol ke box
	g_signal_connect(tombol, "clicked",G_CALLBACK(f), NULL);//respon tombol
}

//Membuat tombol dengan style (warna, gambar)
static void basic_create_picture_button(GtkWidget *box_name,char *label_name,void (*f),char *picture_file,char *outer_colour,char *inner_colour){
	GtkWidget *tombol,*btombol,*box_tombol,*gambar,*label;
	
	const char *format = "<span style=\"normal\" font_desc=\"Sans 17\" foreground=\"#000000\" >\%s</span>";
	char *markup;
	
	tombol = gtk_button_new();		//Membuat button baru , inner button
	btombol = gtk_button_new();		//Membuat outer button
	box_tombol = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(btombol)),outer_colour);	//set style outter button
	gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(tombol)),inner_colour);		//set style inner button
	
	gambar = gtk_image_new_from_file(picture_file);		//memasukkan gambar
	label = gtk_label_new(label_name);					//Set label pada button
	
	//Menyatukan format style button dengan label
	markup = g_markup_printf_escaped(format, label_name);
	gtk_label_set_markup(GTK_LABEL(label), markup);
	g_free(markup);
	
	gtk_box_pack_start(GTK_BOX(box_tombol), gambar, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box_tombol), label, TRUE, TRUE, 0);
	
	gtk_container_add(GTK_CONTAINER(tombol), box_tombol);
	gtk_container_add(GTK_CONTAINER(btombol), tombol);
	gtk_box_pack_start(GTK_BOX(box_name), btombol, TRUE, TRUE, 0);
	
	g_signal_connect(btombol, "clicked",G_CALLBACK(f), NULL);	//respon tombol
}

//function menutup window pop up
void close_current_window(GtkWidget *window){
	gtk_window_close (GTK_WINDOW(window));
}

//function window supaya diatas
void set_window_keep_above(GtkWidget *window){
	gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
}

//Membuat window baru
void create_new_window_from_widget(GtkWidget *window,char* window_label){
	gtk_window_set_title(GTK_WINDOW(window),window_label);
	custom_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    custom_hbox = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(custom_hbox), TRUE);
    
    gtk_box_set_spacing(GTK_BOX(custom_vbox), 0);
    gtk_grid_set_column_spacing(GTK_GRID(custom_hbox), 0);
    gtk_grid_set_row_spacing(GTK_GRID(custom_hbox), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(custom_hbox), TRUE);
}
//memasukan widget ke window
void attach_widget_to_window(GtkWidget *widget,int coloumb,int row){
	gtk_grid_attach(GTK_GRID(custom_hbox), widget,  coloumb, row, 1, 1);
}

//membuat window default size : fullscreen
void make_fullscreen(GtkWidget *window){
	gtk_window_fullscreen(GTK_WINDOW(window));
}

//display window 
void show_window(GtkWidget *window){
	gtk_box_pack_start(GTK_BOX(custom_vbox), custom_hbox, TRUE, TRUE, 0); 
    gtk_container_add(GTK_CONTAINER (window), custom_vbox);
    gtk_window_set_position (GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    
	gtk_widget_show_all (window);
}

//membuat button dengan style (warna dan gambar)
void create_picture_button(int coloum,int row,char *isi_label,void (*f),char *file_gambar,char *dd1,char *dd2){
	custom_box_index++;
	basic_create_picture_button(custom_box[custom_box_index],isi_label,f,file_gambar,dd1,dd2);
	attach_widget_to_window(custom_box[custom_box_index],coloum,row);
}

//membuat button tanpa style
void create_button(int coloum,int row,char *isi_label,void (*f)){
	custom_box_index++;
	basic_create_button(custom_box[custom_box_index],isi_label,f);
	attach_widget_to_window(custom_box[custom_box_index],coloum,row);
}

//alokasi widget space
void allocate_widget_space(){
	for (int i=0;i<9999;i++){custom_box[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);}
}

//set warna outercolour dan innercolour
void set_widget_rgb(){
	char *tmptxt,*tmptxt1;
	
	tmptxt = gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour0 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[0])),gabung_kata(",",IntToStr(custom_cssGreenin[0]))),gabung_kata(",",IntToStr(custom_cssBluein[0]))),"); border: none; border-radius: 22px;}\n");
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour1 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[1])),gabung_kata(",",IntToStr(custom_cssGreenin[1]))),gabung_kata(",",IntToStr(custom_cssBluein[1]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour2 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[2])),gabung_kata(",",IntToStr(custom_cssGreenin[2]))),gabung_kata(",",IntToStr(custom_cssBluein[2]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour3 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[3])),gabung_kata(",",IntToStr(custom_cssGreenin[3]))),gabung_kata(",",IntToStr(custom_cssBluein[3]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour4 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[4])),gabung_kata(",",IntToStr(custom_cssGreenin[4]))),gabung_kata(",",IntToStr(custom_cssBluein[4]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour5 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[5])),gabung_kata(",",IntToStr(custom_cssGreenin[5]))),gabung_kata(",",IntToStr(custom_cssBluein[5]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour6 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[6])),gabung_kata(",",IntToStr(custom_cssGreenin[6]))),gabung_kata(",",IntToStr(custom_cssBluein[6]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour7 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[7])),gabung_kata(",",IntToStr(custom_cssGreenin[7]))),gabung_kata(",",IntToStr(custom_cssBluein[7]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour8 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[8])),gabung_kata(",",IntToStr(custom_cssGreenin[8]))),gabung_kata(",",IntToStr(custom_cssBluein[8]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour9 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[9])),gabung_kata(",",IntToStr(custom_cssGreenin[9]))),gabung_kata(",",IntToStr(custom_cssBluein[9]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour10 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[10])),gabung_kata(",",IntToStr(custom_cssGreenin[10]))),gabung_kata(",",IntToStr(custom_cssBluein[10]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour11 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[11])),gabung_kata(",",IntToStr(custom_cssGreenin[11]))),gabung_kata(",",IntToStr(custom_cssBluein[11]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour12 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[12])),gabung_kata(",",IntToStr(custom_cssGreenin[12]))),gabung_kata(",",IntToStr(custom_cssBluein[12]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour13 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[13])),gabung_kata(",",IntToStr(custom_cssGreenin[13]))),gabung_kata(",",IntToStr(custom_cssBluein[13]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour14 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[14])),gabung_kata(",",IntToStr(custom_cssGreenin[14]))),gabung_kata(",",IntToStr(custom_cssBluein[14]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour15 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[15])),gabung_kata(",",IntToStr(custom_cssGreenin[15]))),gabung_kata(",",IntToStr(custom_cssBluein[15]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour16 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[16])),gabung_kata(",",IntToStr(custom_cssGreenin[16]))),gabung_kata(",",IntToStr(custom_cssBluein[16]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour17 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[17])),gabung_kata(",",IntToStr(custom_cssGreenin[17]))),gabung_kata(",",IntToStr(custom_cssBluein[17]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour18 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[18])),gabung_kata(",",IntToStr(custom_cssGreenin[18]))),gabung_kata(",",IntToStr(custom_cssBluein[18]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour19 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[19])),gabung_kata(",",IntToStr(custom_cssGreenin[19]))),gabung_kata(",",IntToStr(custom_cssBluein[19]))),"); border: none; border-radius: 22px;}\n"));
	tmptxt = gabung_kata(tmptxt,gabung_kata(gabung_kata(gabung_kata(gabung_kata(".innerColour20 { background-image: none; background-color: rgb(",IntToStr(custom_cssRedin[20])),gabung_kata(",",IntToStr(custom_cssGreenin[20]))),gabung_kata(",",IntToStr(custom_cssBluein[20]))),"); border: none; border-radius: 22px;}\n"));
	
	tmptxt1 = gabung_kata(".outerColour0 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour0:hover { background-color: rgb(",IntToStr(custom_cssRedout[0])),gabung_kata(",",IntToStr(custom_cssGreenout[0]))),gabung_kata(",",IntToStr(custom_cssBlueout[0]))),"); }\n"));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour1 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour1:hover { background-color: rgb(",IntToStr(custom_cssRedout[1])),gabung_kata(",",IntToStr(custom_cssGreenout[1]))),gabung_kata(",",IntToStr(custom_cssBlueout[1]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour2 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour2:hover { background-color: rgb(",IntToStr(custom_cssRedout[2])),gabung_kata(",",IntToStr(custom_cssGreenout[2]))),gabung_kata(",",IntToStr(custom_cssBlueout[2]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour3 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour3:hover { background-color: rgb(",IntToStr(custom_cssRedout[3])),gabung_kata(",",IntToStr(custom_cssGreenout[3]))),gabung_kata(",",IntToStr(custom_cssBlueout[3]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour4 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour4:hover { background-color: rgb(",IntToStr(custom_cssRedout[4])),gabung_kata(",",IntToStr(custom_cssGreenout[4]))),gabung_kata(",",IntToStr(custom_cssBlueout[4]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour5 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour5:hover { background-color: rgb(",IntToStr(custom_cssRedout[5])),gabung_kata(",",IntToStr(custom_cssGreenout[5]))),gabung_kata(",",IntToStr(custom_cssBlueout[5]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour6 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour6:hover { background-color: rgb(",IntToStr(custom_cssRedout[6])),gabung_kata(",",IntToStr(custom_cssGreenout[6]))),gabung_kata(",",IntToStr(custom_cssBlueout[6]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour7 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour7:hover { background-color: rgb(",IntToStr(custom_cssRedout[7])),gabung_kata(",",IntToStr(custom_cssGreenout[7]))),gabung_kata(",",IntToStr(custom_cssBlueout[7]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour8 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour8:hover { background-color: rgb(",IntToStr(custom_cssRedout[8])),gabung_kata(",",IntToStr(custom_cssGreenout[8]))),gabung_kata(",",IntToStr(custom_cssBlueout[8]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour9 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour9:hover { background-color: rgb(",IntToStr(custom_cssRedout[9])),gabung_kata(",",IntToStr(custom_cssGreenout[9]))),gabung_kata(",",IntToStr(custom_cssBlueout[9]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour10 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour10:hover { background-color: rgb(",IntToStr(custom_cssRedout[10])),gabung_kata(",",IntToStr(custom_cssGreenout[10]))),gabung_kata(",",IntToStr(custom_cssBlueout[10]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour11 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour11:hover { background-color: rgb(",IntToStr(custom_cssRedout[11])),gabung_kata(",",IntToStr(custom_cssGreenout[11]))),gabung_kata(",",IntToStr(custom_cssBlueout[11]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour12 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour12:hover { background-color: rgb(",IntToStr(custom_cssRedout[12])),gabung_kata(",",IntToStr(custom_cssGreenout[12]))),gabung_kata(",",IntToStr(custom_cssBlueout[12]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour13 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour13:hover { background-color: rgb(",IntToStr(custom_cssRedout[13])),gabung_kata(",",IntToStr(custom_cssGreenout[13]))),gabung_kata(",",IntToStr(custom_cssBlueout[13]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour14 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour14:hover { background-color: rgb(",IntToStr(custom_cssRedout[14])),gabung_kata(",",IntToStr(custom_cssGreenout[14]))),gabung_kata(",",IntToStr(custom_cssBlueout[14]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour15 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour15:hover { background-color: rgb(",IntToStr(custom_cssRedout[15])),gabung_kata(",",IntToStr(custom_cssGreenout[15]))),gabung_kata(",",IntToStr(custom_cssBlueout[15]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour16 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour16:hover { background-color: rgb(",IntToStr(custom_cssRedout[16])),gabung_kata(",",IntToStr(custom_cssGreenout[16]))),gabung_kata(",",IntToStr(custom_cssBlueout[16]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour17 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour17:hover { background-color: rgb(",IntToStr(custom_cssRedout[17])),gabung_kata(",",IntToStr(custom_cssGreenout[17]))),gabung_kata(",",IntToStr(custom_cssBlueout[17]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour18 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour18:hover { background-color: rgb(",IntToStr(custom_cssRedout[18])),gabung_kata(",",IntToStr(custom_cssGreenout[18]))),gabung_kata(",",IntToStr(custom_cssBlueout[18]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour19 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour19:hover { background-color: rgb(",IntToStr(custom_cssRedout[19])),gabung_kata(",",IntToStr(custom_cssGreenout[19]))),gabung_kata(",",IntToStr(custom_cssBlueout[19]))),"); }\n")));
	tmptxt1 = gabung_kata(tmptxt1,gabung_kata(".outerColour20 { background-image: none; background-color: transparent; border: none; border-radius: 22px;}\n",gabung_kata(gabung_kata(gabung_kata(gabung_kata(".outerColour20:hover { background-color: rgb(",IntToStr(custom_cssRedout[20])),gabung_kata(",",IntToStr(custom_cssGreenout[20]))),gabung_kata(",",IntToStr(custom_cssBlueout[20]))),"); }\n")));
	
	custom_css1 = tmptxt;
	custom_css2 = tmptxt1;
}

//initialize gtk function
void init_gtk_component(int *argc, char ***argv){
	custom_box_index = 0;
	gtk_init(argc, argv);
}


//membuat window baru 
void buat_window(){
	GtkWidget *window; //declare window baru
	
	window = create_gtk_window(); //membuat window baru
	create_new_window_from_widget(window,"Coba Window"); //create new window n set titile window
	set_window_keep_above(window); //window stay on top
	allocate_widget_space(5,10);
	create_picture_button(2,10,"Exit",close_current_window,"logo_bt1.png","red","red1");//coloumn 2, row 10 
    show_window(window);
}
