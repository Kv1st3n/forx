#include "CustomWindow.h"
#include <iostream>

CustomWindow::CustomWindow() {}

void CustomWindow::show_picker(Gtk::Window& parent_window) {
    std::cout << "CustomWindow class: Launching file selection..." << std::endl;
    
    auto dialog = Gtk::FileDialog::create();
    auto filters = Gio::ListStore<Gtk::FileFilter>::create();

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    filters->append(filter_any);
    dialog->set_filters(filters);

    dialog->open(parent_window, sigc::bind(sigc::mem_fun(*this, &CustomWindow::on_file_dialog_finish), dialog));
}

void CustomWindow::show_mode_menu(Gtk::Button& parent_button) {
    std::cout << "CustomWindow class: Launching mode menu" << std::endl;

    if (!m_mode_popover.get_parent()) {
        auto mode_menu = Gio::Menu::create();

        mode_menu ->append("MD5");
        mode_menu ->append("SHA1");
        mode_menu ->append("SHA256");

        m_mode_popover.set_menu_model(mode_menu);

        m_mode_popover.set_parent(parent_button);
    }

    m_mode_popover.popup();

}

void CustomWindow::on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result, const Glib::RefPtr<Gtk::FileDialog>& dialog) {
    try {
        auto file = dialog->open_finish(result);
        std::string filename = file->get_path();
        
        std::cout << "CustomWindow successfully caught file path: " << filename << std::endl;
        
    }
    catch (const Gtk::DialogError& err) {
        std::cout << "CustomWindow: User cancelled choice. " << err.what() << std::endl;
    }
    catch (const Glib::Error& err) {
        std::cout << "CustomWindow: Unexpected exception. " << err.what() << std::endl;
    }
}

