#ifndef GTKMM_CUSTOM_WINDOW_H
#define GTKMM_CUSTOM_WINDOW_H

#include <gtkmm.h>
#include <string>

class CustomWindow {
public:
    CustomWindow();
    ~CustomWindow() = default;

    void show_picker(Gtk::Window& parent_window);
    void show_mode_menu(Gtk::Button& parent_button);

protected:
    void on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result, const Glib::RefPtr<Gtk::FileDialog>& dialog);


private:
    Gtk::PopoverMenu m_mode_popover;
};




#endif