/* example-start buttons buttons.c */

#include <gtk/gtk.h>

/* Create a new hbox with an image and a label packed into it
 * and return the box. */

GtkWidget *xpm_label_box( GtkWidget *parent,
                          gchar     *xpm_filename,
                          gchar     *label_text )
{
    GtkWidget *box1;
    GtkWidget *label;
    GtkWidget *pixmapwid;
    GdkPixmap *pixmap;
    GdkBitmap *mask;
    GtkStyle *style;

    /* Create box for xpm and label */
    box1 = gtk_hbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box1), 2);

    /* Get the style of the button to get the
     * background color. */
    style = gtk_widget_get_style(parent);

    /* Now on to the xpm stuff */
    pixmap = gdk_pixmap_create_from_xpm (parent->window, &mask,
                                         &style->bg[GTK_STATE_NORMAL],
                                         xpm_filename);
    pixmapwid = gtk_pixmap_new (pixmap, mask);
é"
    /* Create a label for the button */
    label = gtk_label_new (label_text);

    /* Pack the pixmap and label into the box */
    gtk_box_pack_start (GTK_BOX (box1),
                        pixmapwid, FALSE, FALSE, 3);

    gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 3);

    gtk_widget_show(pixmapwid);
    gtk_widget_show(label);

    return(box1);
}

/* Our usual callback function */
void callback(gpointer data )
{
    g_print ("FaceUp will work... maybe %s\n", (char *) data);
}


int main( int   argc,
          char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button2;
    GtkWidget *box1;
    GtkWidget *box2;

    gtk_init (&argc, &argv);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title (GTK_WINDOW (window), "FaceUp");

    /* It's a good idea to do this for all windows. */
    gtk_signal_connect (GTK_OBJECT (window), "destroy",
                        GTK_SIGNAL_FUNC (gtk_exit), NULL);

    gtk_signal_connect (GTK_OBJECT (window), "delete_event",
                        GTK_SIGNAL_FUNC (gtk_exit), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_realize(window);

    /* Create a new button */
    button = gtk_button_new ();
    button2 = gtk_button_new ();

    /* Connect the "clicked" signal of the button to our callback */
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
                        GTK_SIGNAL_FUNC (callback), (gpointer) "Convert");

    /* This calls our box creating function */
    box1 = xpm_label_box(window, "info.xpm", "Convert");
    box2 = xpm_label_box(window, "info.xpm", "Exit");

    /* Pack and show all our widgets */
    gtk_widget_show(box1);
    gtk_widget_show(box2);

    gtk_container_add (GTK_CONTAINER (button), box1);
    gtk_container_add (GTK_CONTAINER (button2), box2);

    gtk_widget_show(button);
    gtk_widget_show(button2);

    gtk_container_add (GTK_CONTAINER (window), button);
    gtk_container_add (GTK_CONTAINER (window), button2);

    gtk_widget_show (window);

    /* Rest in gtk_main and wait for the fun to begin! */
    gtk_main ();

    return(0);
}
/*

		surface = IMG_Load(path);

		GdkPixbuf* pixbuffer;
		if (holder->format->BitsPerPixel == 24)
		{
			pixbuffer = gdk_pixbuf_new_from_data(holder->pixels,
					GDK_COLORSPACE_RGB, FALSE, 8, holder->w, holder->h,
					holder->pitch, NULL, NULL);
		}
		else
		{
			pixbuffer = gdk_pixbuf_new_from_data(holder->pixels,
					GDK_COLORSPACE_RGB, TRUE, 8, holder->w, holder->h,
					holder->pitch, NULL, NULL);
		}
		gtk_image_set_from_pixbuf(GTK_IMAGE(img), pixbuffer);

*/

