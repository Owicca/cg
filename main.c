#include "main.h"

GError *cg_error = NULL;

  static void
activate(GtkApplication* app, gpointer user_data)
{
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "cg");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

  GtkWidget *pages = gtk_notebook_new();
  gtk_notebook_append_page(GTK_NOTEBOOK(pages), create_view_page(), gtk_label_new("View"));
  gtk_notebook_append_page(GTK_NOTEBOOK(pages), create_config_page(), gtk_label_new("Config"));
  gtk_container_add(GTK_CONTAINER(window), pages);

  gtk_widget_show_all(window);

  printf("%p", user_data);
}

  int
main(int argc,
    char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example",
      G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
