#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>

#include "../main.h"
#include "config.h"


GtkListStore *
populate_store(GtkListStore *store, gchar *dir_path);

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
      populate_store(store, open_dir);
    }
  }

  gtk_widget_destroy(open_dir_dialog);
  printf("%p%p", button, user_data);
}

  GtkListStore *
populate_store(GtkListStore *store, gchar *dir_path)
{
  // dummy values to get rid of warnings
  GtkTreeIter ttt = {5264354, NULL, NULL, NULL};
  GtkTreeIter *iter = &ttt;
  GDir *dir;
  const gchar *cur_file;

  gtk_list_store_clear(store);
  dir = g_dir_open(dir_path, 0, NULL);
  if(!dir)
    return store;

  cur_file = g_dir_read_name(dir);

  while(cur_file != NULL)
  {
    cur_file = g_dir_read_name(dir);

    gchar *path = g_build_filename(dir_path, cur_file, NULL);
    if(g_file_test(path, G_FILE_TEST_IS_DIR))
      continue;
    gchar *display_name = g_filename_to_utf8(cur_file, -1, NULL,
        NULL, NULL);

    GdkPixbuf *cur_pixbuf = gdk_pixbuf_new_from_file(path, &cg_error);
    if(cg_error != NULL) {
      printf("%s\n", cg_error->message);
      cg_error = NULL;
      cur_pixbuf = gdk_pixbuf_new_from_file("./images/placeholder.jpg",
          &cg_error);
    }
    gdk_pixbuf_scale_simple(GDK_PIXBUF(cur_pixbuf),
        15, 15, GDK_INTERP_BILINEAR);

    gtk_list_store_append(GTK_LIST_STORE(store), iter);
    gtk_list_store_set(GTK_LIST_STORE(store), iter,
        COL_PATH, path,
        COL_DISPLAY_NAME, display_name,
        COL_IS_DIRECTORY, FALSE,
        COL_PIXBUF, cur_pixbuf,
        -1);
    g_free(path);
    g_free(display_name);
  }

  g_dir_close(dir);

  return store;
}

  GtkListStore *
create_store(void)
{
  store = gtk_list_store_new(NUM_COLS,
      G_TYPE_STRING,
      G_TYPE_STRING,
      GDK_TYPE_PIXBUF,
      G_TYPE_BOOLEAN);
  return store;
}

  GtkWidget *
create_config_page(void)
{
  GtkWidget *open_dir_button = gtk_button_new_with_label("Open Directory");
  g_signal_connect(GTK_WIDGET(open_dir_button), "clicked",
      G_CALLBACK(choose_directory), NULL);

  GtkWidget *sw = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),
      GTK_POLICY_AUTOMATIC,
      GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_min_content_width(
      GTK_SCROLLED_WINDOW(sw), 720);
  gtk_scrolled_window_set_min_content_height(
      GTK_SCROLLED_WINDOW(sw), 480);

  create_store();

  GtkWidget *icon_view = gtk_icon_view_new_with_model(GTK_TREE_MODEL(store));
  gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(icon_view),
      GTK_SELECTION_MULTIPLE);
  gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view),
      COL_DISPLAY_NAME);
  gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view),
      COL_PIXBUF);
  //gtk_icon_view_set_item_width(GTK_ICON_VIEW(icon_view), -1);
  //  g_signal_connect(icon_view, "item-activated",
  //      G_CALLBACK(item_activated), store);

  gtk_container_add(GTK_CONTAINER(sw), GTK_WIDGET(icon_view));

  config_page = gtk_grid_new();
  gtk_grid_attach(GTK_GRID(config_page), sw, 1, 1, 720, 480);
  gtk_grid_attach_next_to(GTK_GRID(config_page), open_dir_button,
      sw, GTK_POS_RIGHT, 75, 75);

  return config_page;
}
