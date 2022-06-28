#include "gtkinclude.c"			//Memasukkan file gtkinclude.c

int main(int argc, char *argv[])
{
	
	init_gtk_component(&argc, &argv);
	
    GtkWidget *window,*gambar;		//Inisialisasi widget

    window = create_gtk_window();	//Membuat window
    create_new_window_from_widget(window,"Coba Aplikasi");	//membuat window dan setting title
    

    allocate_widget_space(3,5);		//alokasi ruang untuk widget
	
	custom_cssRedin[0] = 255;
    custom_cssGreenin[0] = 0;		//Merah
    custom_cssBluein[0] = 0;
    
    custom_cssRedin[1] = 0;
    custom_cssGreenin[1] = 255;		//Hijau
    custom_cssBluein[1] = 0;
    
    custom_cssRedin[2] = 0;
    custom_cssGreenin[2] = 0;		//Biru
    custom_cssBluein[2] = 255;
    
    custom_cssRedin[3] = 128;
    custom_cssGreenin[3] = 57;
    custom_cssBluein[3] = 220;
    
    custom_cssRedout[0] = 255;
    custom_cssGreenout[0] = 100;
    custom_cssBlueout[0] = 0;
    
    custom_cssRedout[1] = 100;
    custom_cssGreenout[1] = 255;
    custom_cssBlueout[1] = 0;
    
    custom_cssRedout[2] = 0;
    custom_cssGreenout[2] = 100;
    custom_cssBlueout[2] = 255;
    
    custom_cssRedout[3] = 128;
    custom_cssGreenout[3] = 157;
    custom_cssBlueout[3] = 220;
    set_widget_rgb();		//set warna diatas ke outerColour dan Innercolour
    
    //Membuat tombol dan st baris dan kolom
	create_picture_button(0,1,"Pulsa / Data",buat_window,"logo_bt1.png","outerColour0","innerColour0");//coloumn 0, row 1
	create_picture_button(1,1,"Internet/TV Kabel",buat_window,"logo_bt1.png","outerColour1","innerColour1");//coloumn 1, row 1
	create_picture_button(2,1,"Pajak",none,"logo_bt1.png","outerColour2","innerColour2");//coloumn 2, row 1
	create_picture_button(2,3,"Exit",gtk_main_quit,"logo_bt1.png","outerColour3","innerColour3");//coloumn 2, row 3
	create_button(1,3,"Coba Tanpa Gaya",none);//coloumn 1, row 3
    
    
    apply_theme();		//Apply CSS
    
    make_fullscreen(window);	//set window fullscreen
    show_window(window);		//print window
    g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL); //respond saat window di close

    gtk_main();
    return(0);
}

//compile : gcc `pkg-config --cflags gtk+-3.0` cobagtk.c -o cobagtk `pkg-config --libs gtk+-3.0` 
