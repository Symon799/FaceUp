/*
 * ============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  watashi wa purojectu desu
 *
 *        Version:  1.0
 *        Created:  10/10/2015 11:53:44 PM
 *       Revision:  none
 *       Compiler:  clang
 *
 *
 * ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <gtk/gtk.h>

#include "pixel_operations.h"
#include "haar.h"
#include "integral.h"

GtkWidget *box;
GtkWidget *window;
GtkWidget *image;
SDL_Surface *im;
char *ori;

void init_sdl(void) 
{
	// Init only the video part
	if(SDL_Init(SDL_INIT_VIDEO) == -1) 
	{
		// If it fails, die with an error message
		errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
	}
}

SDL_Surface* load_image(char *path) 
{
	SDL_Surface *img;
	// Load an image using SDL_image with format detection
	img = IMG_Load(path);
	if (!img)
		// If it fails, die with an error message
		errx(3, "can't load %s: %s", path, IMG_GetError());
	return img;
}

void wait_for_keypressed(void)
{
	SDL_Event event;
	for (;;) 
	{
		// Take an event
		SDL_PollEvent( &event );
		// Switch on event type
		switch (event.type)
		{
			// Someone pressed a key -> leave the function
			case SDL_KEYDOWN: return;
			default: break;
		}
	}
}

SDL_Surface* display_image(SDL_Surface *img) 
{
	SDL_Surface *screen;
	// Set the window to the same size as the image
	screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
	
	if ( screen == NULL ) 
	{
		// error management
		errx(1, "Couldn't set %dx%d video mode: %s\n",
				img->w, img->h, SDL_GetError());
	}

	/*  Blit onto the screen surface */
	if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
		warnx("BlitSurface error: %s\n", SDL_GetError());

	// Update the screen
	SDL_UpdateRect(screen, 0, 0, img->w, img->h);

	// wait for a key
	wait_for_keypressed();

	// return the screen for further uses
	return screen;
}

gint delete_event()
{
    gtk_main_quit ();
    return(FALSE);
}

GtkWidget *xpm_label_box(gchar *label_text)
{
    GtkWidget *label;
    GtkWidget *box = NULL;

    //Create a box for the image and label
    box = gtk_hbox_new(TRUE,2);
    gtk_container_set_border_width(GTK_CONTAINER(box),2);

    //Create a label for the button
    label = gtk_label_new(label_text);

    //The image and the button assembly into the box
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,50);
    
    gtk_widget_show(label);
    
    return box;
}

void changeImage()
{
	SDL_Surface *holder = im;
	GdkPixbuf* pixbuffer;
	if (holder->format->BitsPerPixel == 24)
		pixbuffer = gdk_pixbuf_new_from_data(holder->pixels, GDK_COLORSPACE_RGB, FALSE, 8, holder->w, holder->h, holder->pitch, NULL, NULL);
	else
		pixbuffer = gdk_pixbuf_new_from_data(holder->pixels, GDK_COLORSPACE_RGB, TRUE, 8, holder->w, holder->h, holder->pitch, NULL, NULL);
	gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuffer);

}

GtkWidget *xpm_image_box()
{
	SDL_Surface *holder = im;
	GdkPixbuf* pixbuffer;
	if (holder->format->BitsPerPixel == 24)
		pixbuffer = gdk_pixbuf_new_from_data(holder->pixels, GDK_COLORSPACE_RGB, FALSE, 8, holder->w, holder->h, holder->pitch, NULL, NULL);
	else
		pixbuffer = gdk_pixbuf_new_from_data(holder->pixels, GDK_COLORSPACE_RGB, TRUE, 8, holder->w, holder->h, holder->pitch, NULL, NULL);
	image = gtk_image_new_from_pixbuf(pixbuffer);

    /*Create a box for the image and label*/
    box = gtk_hbox_new(TRUE,3);
    gtk_container_set_border_width(GTK_CONTAINER(box),50);

    /*The image and the button assembly into the box*/
    gtk_box_pack_start(GTK_BOX(box),image,FALSE,FALSE,100);
    
    gtk_widget_show(image);

    //convertGreyLevel(holder);
    return box;
}

void convert_event()
{
    g_print("converted !\n");
    im = load_image(ori);
    convertGreyLevel(im);
    changeImage();
}

void find_event()
{
    g_print("Face Found !\n");
    im = load_image(ori);
    displaySquare(im, 82, 100, 100);
    changeImage();
}

void ori_event()
{
    g_print("Original !\n");
    im = load_image(ori);
    changeImage();
}

void haar_event()
{
    struct Matrix myMatrix;
    myMatrix.x = im->h;
    myMatrix.y = im->w;

    g_print("Haar !\n");
    im = load_image(ori);
    changeImage();
    alloc_Mat(&myMatrix);
    //myMatrix.arr = convertToMatrix(&myMatrix, im);
}

void open_event()
{
	GtkWidget *dialog;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File",
     				      GTK_WINDOW(window),
     				      GTK_FILE_CHOOSER_ACTION_OPEN,
     				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
     				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
     				      NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));

	if (res == GTK_RESPONSE_ACCEPT)
	{
	    char *filename;
	    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
	    filename = gtk_file_chooser_get_filename (chooser);
	    im = load_image(filename);
	    ori = filename;
	    changeImage();
	    g_print("%s\n",filename);
	}

	gtk_widget_destroy (dialog);
}

void interface(int argc, char *argv[])
{
	GtkWidget *button0;
	GtkWidget *button;
	GtkWidget *button2;
	GtkWidget *button3;
	GtkWidget *button4;
	GtkWidget *button5;
	GtkWidget *table;
	
	gtk_init (&argc, &argv);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "FaceUp");

	gtk_container_set_border_width (GTK_CONTAINER (window), 40);

	table = gtk_table_new (3, 4, TRUE);
	gtk_container_add (GTK_CONTAINER (window), table);

	//ADD BUTTON ORIGINAL
	button0 = gtk_button_new_with_label ("Original");
	gtk_signal_connect (GTK_OBJECT (button0), "clicked", GTK_SIGNAL_FUNC (ori_event), NULL);
	
	gtk_table_attach_defaults (GTK_TABLE(table), button0, 0, 1, 2, 3);
	gtk_widget_show(button0);

	//ADD BUTTON
	button = gtk_button_new_with_label ("Convert Grey");
	gtk_signal_connect (GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC (convert_event), NULL);
	
	gtk_table_attach_defaults (GTK_TABLE(table), button, 1, 2, 2, 3);
	gtk_widget_show(button);

	//ADD BUTTON2
	button2 = gtk_button_new_with_label ("Find");
	gtk_signal_connect (GTK_OBJECT (button2), "clicked", GTK_SIGNAL_FUNC (find_event), NULL);
	
	gtk_table_attach_defaults (GTK_TABLE(table), button2, 2, 3, 2, 3);
	gtk_widget_show(button2);

	//ADD BUTTON3
	button3 = gtk_button_new_with_label ("Exit");
	gtk_signal_connect (GTK_OBJECT (button3), "clicked", GTK_SIGNAL_FUNC (delete_event), NULL);

	
	gtk_table_attach_defaults (GTK_TABLE(table), button3, 3, 4, 2, 3);
	gtk_widget_show(button3);

	//ADD BUTTON4
	button4 = gtk_button_new_with_label ("Open image");
	gtk_signal_connect (GTK_OBJECT (button4), "clicked", GTK_SIGNAL_FUNC (open_event), NULL);

	
	gtk_table_attach_defaults (GTK_TABLE(table), button4, 1, 3, 3, 4);
	gtk_widget_show(button4);

	//ADD BUTTON5
	button5 = gtk_button_new_with_label ("Haar Features");
	gtk_signal_connect (GTK_OBJECT (button5), "clicked", GTK_SIGNAL_FUNC (haar_event), NULL);

	
	gtk_table_attach_defaults (GTK_TABLE(table), button5, 0, 1, 3, 4);
	gtk_widget_show(button5);

	//ADD IMAGE	
	box = xpm_image_box();
	
	gtk_table_attach_defaults (GTK_TABLE(table), box, 0, 4, 0, 2);
	gtk_widget_show (box);
	
	gtk_widget_show (table);
	gtk_widget_show (window);
	gtk_main();
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		errx(2, "Usage:\n%s <image>", argv[0]);

	init_sdl();
	im = load_image(argv[1]);
	ori = argv[1];
	
	interface( argc, argv);
	
	//myMatrix.arr = convertToMatrix(&myMatrix, load_image(argv[1]));
	//printf("1st result using the Haar function: %ld\n", Haar(myMatrix,0,0,24)[0].Haar);
	//printf("Result expected : %ld\n",  (2*myMatrix.arr[0][0] - myMatrix.arr[0][1]));

	SDL_FreeSurface(im);

	return 0;
}
