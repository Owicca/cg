#include "../data.h"
#include "view.h"
#include <gtk/gtk.h>


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
}

  GtkWidget *
create_view_page()
{
  view_page = gtk_grid_new();
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

  //play_button
  play_button = gtk_toggle_button_new_with_label("Paused");
  g_signal_connect(play_button, "toggled",
      G_CALLBACK(toggle_play), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(play_button), 15);

  //progress_bar
  progress_bar = gtk_progress_bar_new();
  gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress_bar),
      25.0);
  gtk_progress_bar_pulse(GTK_PROGRESS_BAR(progress_bar));

  //pixbuff
  view = gtk_image_new();
  current_pixbuf = gdk_pixbuf_new_from_file_at_size("./images/jpg.jpg",
      720,
      480,
      &cg_error);
  gtk_image_set_from_pixbuf(
      GTK_IMAGE(view),
      GDK_PIXBUF(current_pixbuf));

  //view_page grid
  gtk_container_set_border_width(GTK_CONTAINER(view_page), 15);
  gtk_grid_attach(GTK_GRID(view_page), view,
      1, 1, 720, 480);
  gtk_grid_attach_next_to(GTK_GRID(view_page), speed_range,
      view,
      GTK_POS_RIGHT, 1, 500);
  gtk_grid_attach_next_to(GTK_GRID(view_page), progress_bar,
      view,
      GTK_POS_BOTTOM, 720, 10);
  gtk_grid_attach_next_to(GTK_GRID(view_page), play_button,
      speed_range,
      GTK_POS_BOTTOM, 50, 10);

  return view_page;
}
