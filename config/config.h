#ifndef CG_CONFIG_H
#define CG_CONFIG_H

#include <gtk/gtk.h>

extern GError *cg_error;

enum{
  COL_PATH,
  COL_DISPLAY_NAME,
  COL_PIXBUF,
  COL_IS_DIRECTORY,
  NUM_COLS
};

GtkWidget *
create_config_page(void);

#endif
