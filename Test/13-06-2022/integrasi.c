//Compile : gcc -Wno-format -o integrasi integrasi.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

void send_data(char* a);
char input[1000];


//Inisialisasi window menu
GtkWidget	*window;
GtkWidget	*box, *fixed;
GtkWidget	*entry1;
GtkWidget	*button_soal1, *button_soal2, *button_soal3, *button_soal4, *button_soal5, *LED;



GtkBuilder	*builder; 

int main (int argc, char **argv)
{
	gtk_init (&argc, &argv);
	
	//connect dengan glade
	builder = gtk_builder_new_from_file ("glade.glade");
	
	//WindowMenu
	window = GTK_WIDGET (gtk_builder_get_object(builder, "window"));
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	gtk_builder_connect_signals (builder, NULL);
	box = GTK_WIDGET (gtk_builder_get_object (builder, "box"));
	fixed = GTK_WIDGET (gtk_builder_get_object (builder, "fixed"));
	entry1 = GTK_WIDGET (gtk_builder_get_object (builder, "entry1"));
	button_soal1 = GTK_WIDGET (gtk_builder_get_object (builder, "button_soal1"));
	button_soal2 = GTK_WIDGET (gtk_builder_get_object (builder, "button_soal2"));
	button_soal3 = GTK_WIDGET (gtk_builder_get_object (builder, "button_soal3"));
	button_soal4 = GTK_WIDGET (gtk_builder_get_object (builder, "button_soal4"));
	button_soal5 = GTK_WIDGET (gtk_builder_get_object (builder, "button_soal5"));
	LED = GTK_WIDGET (gtk_builder_get_object (builder, "LED"));
	
	gtk_widget_show(window);			//Print window

	gtk_main();
	
	return EXIT_SUCCESS;
}



void on_LED_toggled (GtkCheckButton *b)
{
		gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
		if (T) send_data("a");
		else send_data("b");
}

void	on_entry_changed (GtkEntry *e) {
	sprintf(input, "%s", gtk_entry_get_text(e));
	
	
}

void	on_button_ok_clicked (GtkButton *b) {
	send_data(input);
	
	}

void	on_button_soal1_clicked (GtkButton *b) {
	send_data("1");
	
	}
	
void	on_button_soal2_clicked (GtkButton *b) {
	send_data("2");
	
	}
	
void	on_button_soal3_clicked (GtkButton *b) {
	send_data("3");
	
	}
	
void	on_button_soal4_clicked (GtkButton *b) {
	send_data("4");
	
	}
	
void	on_button_soal5_clicked (GtkButton *b) {
	send_data("5");
	
	}

void send_data (char *a){
	int fd, len;
	char text[255];
	struct termios options; /* Serial ports setting */

	fd = open("/dev/ttyACM0", O_RDWR | O_NDELAY | O_NOCTTY);
	if (fd < 0) {
		perror("Error opening serial port");
		
	}

	/* Read current serial port settings */
	// tcgetattr(fd, &options);
	
	/* Set up serial port */
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;

	/* Apply the settings */
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options);

	/* Write to serial port */
	strcpy(text, a);
	len = strlen(text);
	len = write(fd, text, len);
	

	close(fd);
	}
