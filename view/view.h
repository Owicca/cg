#ifndef CG_VIEW_H
#define CG_VIEW_H

#include <gtk/gtk.h>

extern GError *cg_error;

GtkWidget *
create_view_page(void);

void
toggle_play(GtkWidget *button,
    gpointer user_data);

gboolean
update_view(GtkWidget *view, const gchar *path);

#endif
