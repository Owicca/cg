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
        scrolled = Gtk.ScrolledWindow(propagate_natural_height=True)
        scrolled.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC)
        scrolled.add(self.iconv)

        opendir_button = self.create_opendir_button()

        self.attach(scrolled, 0, 0, 3, 4)
        self.attach(opendir_button, 4, 0, 1, 1)

    def create_iconv(self):
        return Gtk.IconView(activate_on_single_click=True, model = self.store, selection_mode=Gtk.SelectionMode.SINGLE,
                             columns=3, item_width = 100, margin=15, pixbuf_column=0, text_column=1)

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
                tree_iter = self.store.get_iter_first()
                self.iconv.item_activated(self.store.get_path(tree_iter))
                self.iconv.select_path(self.store.get_path(tree_iter))
            dialog.destroy()

        b.connect("clicked", open_dialog)
        return b
