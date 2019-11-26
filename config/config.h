#include <gtk/gtk.h>

enum{
  COL_PATH,
  COL_DISPLAY_NAME,
  COL_PIXBUF,
  COL_IS_DIRECTORY,
  NUM_COLS
};

GtkWidget *
create_config_page();
