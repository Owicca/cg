import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk
from gi.repository.GdkPixbuf import Pixbuf

class ViewPage(Gtk.Grid):
    cur_idx = 0

    def __init__(self, store):
        Gtk.Grid.__init__(self)
        self.store = store

        self.image = self.create_image()
        self.speed_scale = self.create_scale()
        self.progress_bar = self.create_progressbar()

        control_box = self.create_control_box()

        self.attach(self.image, 0, 0, 3, 3)
        self.attach(self.speed_scale, 4, 0, 1, 3)

        self.attach(self.progress_bar, 0, 4, 3, 1)
        self.attach(control_box, 0, 5, 1, 1)

    def create_progressbar(self):
        p = Gtk.ProgressBar()
        #p.set_pulse_step(0.25)
        #p.pulse()

        return p

    def create_scale(self):
        s = Gtk.Scale.new_with_range(Gtk.Orientation.VERTICAL, min=0.0,
                                     max=100.0, step=25.0)
        s.set_draw_value(False)
        s.set_inverted(True)
        s.set_value(50.0)
        s.add_mark(0.0, Gtk.PositionType.RIGHT, "Stopped")
        s.add_mark(25.0, Gtk.PositionType.RIGHT, "Slow")
        s.add_mark(50.0, Gtk.PositionType.RIGHT, "Normal")
        s.add_mark(75.0, Gtk.PositionType.RIGHT, "Fast")
        s.add_mark(100.0, Gtk.PositionType.RIGHT, "Very Fast")

        return s

    def create_image(self):
        pixbuf = Pixbuf.new_from_file_at_scale("./images/placeholder.png",
                                               720, 480, True)
        i = Gtk.Image.new_from_pixbuf(pixbuf)

        return i

    def update_image(self, path=None, pixbuf=None):
        if path:
            pixbuf = Pixbuf.new_from_file_at_scale(path,
                                                   720, 480, True)
        self.image.set_from_pixbuf(pixbuf)

    def play_pause(self, widget):
        self.play.set_label("Playing" if self.play.get_active() else "Paused")


    def create_control_box(self):
        """
        previous, play, next button creation
        """
        control_box = Gtk.Grid()
        self.prv = Gtk.Button(label="Previous")
        self.prv.set_sensitive(False)
        self.play = Gtk.ToggleButton(label="Paused")
        self.play.connect("toggled", self.play_pause)
        self.nxt = Gtk.Button(label="Next")

        control_box.attach(self.prv, 0, 0, 1, 1)
        control_box.attach(self.play, 1, 0, 1, 1)
        control_box.attach(self.nxt, 2, 0, 1, 1)

        return control_box

    def prev_image(self, widget, data):
        """
        this is shit, get some sleep and rewrite it
        """
        if self.cur_idx == 0:
            return True
        if self.cur_idx > 0:
            self.prv.set_sensitive(False)

        if self.cur_idx < len(self.store):
            self.nxt.set_sensitive(True)

        if self.cur_idx == 0:
            tree_iter = self.store.get_iter(Gtk.TreePath(0))
        else:
            tree_iter = self.store.get_iter(Gtk.TreePath(self.cur_idx - 1))

        path = self.store.get_value(tree_iter, 2)
        self.update_image(path=path)
        self.cur_idx -= 1

    def next_image(self, widget, data):
        """
        same shit as above
        """
        if self.cur_idx + 1 > len(self.store):
            return True
        if self.cur_idx + 1 == len(self.store):
            self.nxt.set_sensitive(False)
        else:
            self.prv.set_sensitive(True)

        if self.cur_idx == 0:
            tree_iter = self.store.get_iter(Gtk.TreePath(1))
        else:
            tree_iter = self.store.get_iter(Gtk.TreePath(self.cur_idx + 1))

        path = self.store.get_value(tree_iter, 2)
        self.update_image(path=path)
        self.cur_idx += 1

    def change_image(self, iconv, treepath_index, data):
        items = iconv.get_selected_items()
        tree_iter = self.store.get_iter(items[0])
        path = self.store.get_value(tree_iter, 2)
        self.update_image(path=path)
        data["notebook"].set_current_page(0)
