from pathlib import Path

import gi
gi.require_version("Gtk", '3.0')
from gi.repository import Gtk
from gi.repository.GdkPixbuf import Pixbuf


class Store(Gtk.ListStore):
    extensions = ["png", "jpg", "jpeg", "gif"]

    def __init__(self, dir_path=None):
        Gtk.ListStore.__init__(self, Pixbuf, str, str)
        if dir_path:
            self.populate(dir_path)

    def populate(self, dir_path):
        self.clear()
        p = Path(dir_path)
        if not p.is_dir():
            return False
        for child in p.iterdir():
            item = Path(child)
            if not self.check_file(item) and p.is_dir():
                continue
            try:
                pixbuf = Pixbuf.new_from_file_at_scale(bytes(child), 150, 150, True)
            except:
                continue
            self.append([pixbuf, item.name, str(item)])

    def check_file(self, path):
        """
        check if file extension is in allowed extensions
        """
        p = Path(path)
        if not len(p.suffixes):
            return False
        return p.suffixes[-1][1:] in self.extensions
