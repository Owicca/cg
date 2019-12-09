import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk

class ConfigPage(Gtk.Grid):
    def __init__(self):
        Gtk.Grid.__init__(self)

        self.attach(button, 0, 0, 1, 1)
