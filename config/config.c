#include <gtk/gtk.h>

  GtkWidget *
create_config_page()
{
  config_page = gtk_grid_new();
  return config_page;
}
