import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk
from gi.repository.GdkPixbuf import Pixbuf

class ViewPage(Gtk.Grid):
    def __init__(self, title="Window"):
        Gtk.Grid.__init__(self)

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
                                               700, 480, True)
        i = Gtk.Image.new_from_pixbuf(pixbuf)

        return i

    def play_pause(self, widget):
        self.play.set_label("Playing" if self.play.get_active() else "Paused")


    def create_control_box(self):
        control_box = Gtk.Grid()
        self.prv = Gtk.Button(label="Previous")
        self.play = Gtk.ToggleButton(label="Paused")
        self.play.connect("toggled", self.play_pause)
        self.nxt = Gtk.Button(label="Next")

        control_box.attach(self.prv, 0, 0, 1, 1)
        control_box.attach(self.play, 1, 0, 1, 1)
        control_box.attach(self.nxt, 2, 0, 1, 1)

        return control_box
