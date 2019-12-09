#!/usr/bin/env python3
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk

from view.view_page import ViewPage
from config.config_page import ConfigPage


class App(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="CG")
        self.set_default_size(800, 600)

        config_page = ConfigPage()
        view_page = ViewPage()
        notebook = Gtk.Notebook()
        notebook.append_page(view_page, Gtk.Label("View"))
        notebook.append_page(config_page, Gtk.Label("Config"))
        self.add(notebook)

app = App()
app.connect("destroy", Gtk.main_quit)
app.show_all()
Gtk.main()
