#include <stdio.h>
#include <gtk/gtk.h>

#include "../main.h"
#include "view.h"


  void
toggle_play(GtkWidget *button,
    gpointer user_data)
{
  gboolean current_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
  printf("Mode changed to %s\n",
      current_state == TRUE ? "Playing" : "Paused");
  if(current_state == TRUE) {
    gtk_button_set_label(GTK_BUTTON(button), "Playing");
  } else {
    gtk_button_set_label(GTK_BUTTON(button), "Paused");
  }

  printf("%p", user_data);
}

  GtkWidget *
create_speed_range()
{
  //speed_scale
  speed_range = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL,
      0.0, 100.0, 10.0);
  gtk_scale_add_mark(GTK_SCALE(speed_range), 0.0,
      GTK_POS_RIGHT, " Stopped");
  gtk_scale_add_mark(GTK_SCALE(speed_range), 25.0,
      GTK_POS_RIGHT, " Slow");
  gtk_scale_add_mark(GTK_SCALE(speed_range), 50.0,
      GTK_POS_RIGHT, " Normal");
  gtk_scale_add_mark(GTK_SCALE(speed_range), 75.0,
      GTK_POS_RIGHT, " Fast");
  gtk_scale_add_mark(GTK_SCALE(speed_range), 100.0,
      GTK_POS_RIGHT, " Very Fast");
  //gtk_scale_set_value_pos(GTK_SCALE(speed_range), GTK_POS_BOTTOM);
  gtk_scale_set_draw_value(GTK_SCALE(speed_range), FALSE);
  gtk_scale_set_has_origin(GTK_SCALE(speed_range), TRUE);
  gtk_range_set_value(GTK_RANGE(speed_range), 50.0);
  gtk_range_set_inverted(GTK_RANGE(speed_range), TRUE);

  return speed_range;
}

  GtkWidget *
create_play_button()
{
  //play_button
  play_button = gtk_toggle_button_new_with_label("Paused");
  g_signal_connect(play_button, "toggled",
      G_CALLBACK(toggle_play), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(play_button), 15);

  return play_button;
}

  GtkWidget *
create_progress_bar()
{
  //progress_bar
  progress_bar = gtk_progress_bar_new();
  gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress_bar),
      25.0);
  gtk_progress_bar_pulse(GTK_PROGRESS_BAR(progress_bar));

  return progress_bar;
}

  gboolean
update_view(GtkWidget *view, const gchar *path)
{
  GdkPixbuf *curr = gdk_pixbuf_new_from_file_at_scale(path, 720, 480, TRUE,
      &cg_error);
  if(cg_error != NULL) {
    printf("[ERROR][in update_view] %s\n", cg_error->message);
    cg_error = NULL;
    return FALSE;
  }
  gtk_image_set_from_pixbuf(
      GTK_IMAGE(view),
      GDK_PIXBUF(curr));

  return TRUE;
}

  GtkWidget *
create_view_page(void)
{
  view_page = gtk_grid_new();

  //pixbuff
  view = gtk_image_new();
  gchar *placeholder_path = "./images/placeholder.jpg";
  update_view(view, placeholder_path);

  //view_page grid
  gtk_container_set_border_width(GTK_CONTAINER(view_page), 15);
  gtk_grid_attach(GTK_GRID(view_page), view,
      1, 1, 720, 480);
  gtk_grid_attach_next_to(GTK_GRID(view_page), create_speed_range(),
      view, GTK_POS_RIGHT, 1, 500);
  gtk_grid_attach_next_to(GTK_GRID(view_page), create_progress_bar(),
      view, GTK_POS_BOTTOM, 720, 10);
  gtk_grid_attach_next_to(GTK_GRID(view_page), create_play_button(),
      speed_range, GTK_POS_BOTTOM, 50, 10);

  return view_page;
}
