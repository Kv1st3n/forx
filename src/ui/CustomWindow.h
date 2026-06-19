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
    void show_about(Gtk::Window& parent_window);

protected:
    void on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result, const Glib::RefPtr<Gtk::FileDialog>& dialog);


private:
    Gtk::PopoverMenu m_mode_popover;
    Gtk::PopoverMenu m_about_popover;
    Gtk::TextView m_about_text_view;
    Glib::RefPtr<Gtk::TextTagTable> m_ref_text_tag_table;
    Glib::RefPtr<Gtk::TextBuffer> m_ref_text_buffer;

    void fill_text_tag_table();
    void fill_buffer();
};


#endif