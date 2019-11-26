#ifndef _CG_DATA
#define _CG_DATA 1

#include <gtk/gtk.h>


GError *cg_error = NULL;

GtkWidget *view_page;
GtkWidget *view;
GdkPixbuf *current_pixbuf;
GtkWidget *speed_range;
GtkWidget *play_button;
GtkWidget *progress_bar;

GtkWidget *config_page;
GtkListStore *store;
char *open_dir;
#endif
