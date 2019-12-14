#!/usr/bin/env python3
import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk

from view.view_page import ViewPage
from config.config_page import ConfigPage
from config.store import Store


class App(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="CG")
        self.set_default_size(800, 600)

        store = Store()
        config_page = ConfigPage(store)
        view_page = ViewPage(store)

        notebook = Gtk.Notebook()
        notebook.append_page(view_page, Gtk.Label("View"))
        notebook.append_page(config_page, Gtk.Label("Config"))
        store.populate("./images")

        config_page.iconv.connect("item-activated", view_page.change_image, {
            "notebook": notebook
        })
        view_page.prv.connect("clicked", view_page.prev_image, {
            "iconv": config_page.iconv
        })
        view_page.nxt.connect("clicked", view_page.next_image, {
            "iconv": config_page.iconv
        })

        self.add(notebook)

app = App()
app.connect("destroy", Gtk.main_quit)
app.show_all()
Gtk.main()
