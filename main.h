#ifndef CG_MAIN_H
#define CG_MAIN_H

#include <stdio.h>
#include <gtk/gtk.h>

#include "view/view.h"
#include "config/config.h"


GError *cg_error;

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
