#ifndef GTKMM_CUSTOM_WINDOW_H
#define GTKMM_CUSTOM_WINDOW_H

#include <gtkmm.h>
#include <string>
#include "CustomButton.h"

class CustomWindow {
public:
    CustomWindow();
    ~CustomWindow() = default;

    void show_picker(Gtk::Window& parent_window);
    void show_mode_menu(Gtk::Button& parent_button);
    void show_about(Gtk::Window& parent_window);
    Gtk::Grid* create_button_grid_for_about_section();
    void fill_buffer_about(const int& choice);
    void show_save(Gtk::Window& parent_window);
    void on_submit();
    void show_file_types(Gtk::Button& parent_button);
    void show_settings(Gtk::Window& parent_window);

protected:
    void on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result, const Glib::RefPtr<Gtk::FileDialog>& dialog);


private:
    Gtk::PopoverMenu m_mode_popover;
    Gtk::PopoverMenu m_file_type_popover;
    Gtk::PopoverMenu m_about_popover;
    Gtk::TextView m_about_text_view;
    Gtk::Grid m_grid;
    Gtk::Entry m_entry;

    Glib::RefPtr<Gtk::TextTagTable> m_ref_text_tag_table;
    Glib::RefPtr<Gtk::TextBuffer> m_ref_text_buffer;

    Custom_Button m_button_about_tool{"About tool"};
    Custom_Button m_button_about_us{"About us"};

    Custom_Button m_button_file_name{"Submit"};
    Custom_Button m_button_file_save{"Save"};
    std::string m_selected_folder_path;

    void fill_text_tag_table();
    void fill_buffer();
};


#endif