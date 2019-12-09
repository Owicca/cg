from pathlib import Path

import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk
from gi.repository.GdkPixbuf import Pixbuf


class ConfigPage(Gtk.Grid):
    def __init__(self, store):
        Gtk.Grid.__init__(self)
        self.store = store

        self.iconv = self.create_iconv()
        self.opendir_button = self.create_opendir_button()
        scrolled = Gtk.ScrolledWindow()
        scrolled.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC)
        scrolled.set_propagate_natural_height(True)
        scrolled.add(self.iconv)

        self.attach(scrolled, 0, 0, 4, 4)
        self.attach(self.opendir_button, 5, 0, 1, 1)

    def create_iconv(self):
        iconv = Gtk.IconView.new()
        iconv.set_model(self.store)
        iconv.set_selection_mode(Gtk.SelectionMode.SINGLE)
        iconv.set_activate_on_single_click(True)
        iconv.set_columns(4)
        iconv.set_item_width(100)
        iconv.set_margin(15)
        iconv.set_pixbuf_column(0)
        iconv.set_text_column(1)

        return iconv

    def create_opendir_button(self):
        b = Gtk.Button(label="Scan Directory")

        def open_dialog(widget):
            dialog = Gtk.FileChooserDialog(
                title="Scan Directory",
                action=Gtk.FileChooserAction.SELECT_FOLDER,
                buttons=(Gtk.STOCK_OPEN, Gtk.ResponseType.OK))

            dialog.set_select_multiple(False)
            res = dialog.run()

            if res == Gtk.ResponseType.OK:
                path = dialog.get_file().get_path()
                self.store.populate(path)
                dialog.hide()

        b.connect("clicked", open_dialog)
        return b
