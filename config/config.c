#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>

#include "../data.h"
#include "config.h"


  void
choose_directory(GtkWidget *button,
    gpointer user_data)
{
  GtkWidget *open_dir_dialog;
  char *filename;

  open_dir_dialog = gtk_file_chooser_dialog_new("Open Directory",
      //TODO: make convert config_page to gtk_window
      NULL,
      GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
      "Cancel",
      GTK_RESPONSE_CANCEL,
      "Open",
      GTK_RESPONSE_ACCEPT,
      NULL);

  gint response = gtk_dialog_run(GTK_DIALOG(open_dir_dialog));
  if(response == GTK_RESPONSE_ACCEPT) {
    filename = gtk_file_chooser_get_filename(
        GTK_FILE_CHOOSER(open_dir_dialog));
    if(access(filename, F_OK) != -1) {
      open_dir = filename;
    }
  }

  gtk_widget_destroy(open_dir_dialog);
  printf("%p%p", button, user_data);
}

  void
populate_icon_list()
{
  gtk_list_store_clear(icon_list);
  printf("%s\n", open_dir);
}

  static void
edited(GtkCellRendererText *cell,
    gchar *path_string,
    gchar *text,
    gpointer *data)
{
  GtkTreeModel *model = gtk_icon_view_get_model(GTK_ICON_VIEW(data));
  GtkTreePath *path = gtk_tree_path_new_from_string(path_string);
  GtkTreeIter iter;

  gtk_tree_model_get_iter(model, &iter, path);
  gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0, "", -1);

  gtk_tree_path_free(path);

  printf("%p%p", cell, text);
}

  void
set_cell_data(GtkCellLayout *cell_layout, GtkCellRenderer *cell,
    GtkTreeModel *tree_model, GtkTreeIter *iter, gpointer data)
{
  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE,
      8, 24, 24);
  guint32 pixel = 0;
  gdk_pixbuf_fill(pixbuf, pixel);

  g_object_set(cell, "pixbuf", pixbuf, NULL);

  g_object_unref(pixbuf);
  printf("%p%p%p%p", cell_layout, tree_model, iter, data);
}

  GtkWidget *
create_icon_list()
{
  GtkCellRenderer *renderer;

  icon_list = gtk_list_store_new(1, GDK_TYPE_PIXBUF);
  icon_view = gtk_icon_view_new_with_model(
      GTK_TREE_MODEL(icon_list));
  gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(icon_view),
      GTK_SELECTION_SINGLE);
  gtk_icon_view_set_item_orientation(GTK_ICON_VIEW(icon_view),
      GTK_ORIENTATION_HORIZONTAL);
  gtk_icon_view_set_reorderable(GTK_ICON_VIEW(icon_view), TRUE);

  renderer = gtk_cell_renderer_pixbuf_new();
  gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(icon_view),
      renderer, TRUE);
  gtk_cell_layout_set_cell_data_func(GTK_CELL_LAYOUT(icon_view),
      renderer,
      set_cell_data,
      NULL, NULL);

  renderer = gtk_cell_renderer_text_new();
  gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(icon_view), renderer,
      TRUE);
  g_object_set(renderer, "editable", TRUE, NULL);
  g_signal_connect(renderer, "edited", G_CALLBACK(edited), icon_view);
  gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(icon_view), renderer,
      "text", 0, NULL);

  populate_icon_list();

  return icon_view;
}

  GtkWidget *
create_config_page()
{
  GtkWidget *open_dir_button = gtk_button_new_with_label("Open Directory");
  g_signal_connect(GTK_WIDGET(open_dir_button), "clicked",
      G_CALLBACK(choose_directory), NULL);

  config_page = gtk_grid_new();
  gtk_grid_attach(GTK_GRID(config_page), create_icon_list(),
      1, 1, 720, 480);
  gtk_grid_attach_next_to(GTK_GRID(config_page), open_dir_button,
      icon_view, GTK_POS_RIGHT, 75, 75);

  return config_page;
}
