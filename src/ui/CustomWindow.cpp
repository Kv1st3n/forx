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

        mode_menu ->append("Hex dump");
        mode_menu ->append("Reverse Mode");
        mode_menu ->append("File identifier");
        mode_menu ->append("Directory Scanner");
        mode_menu ->append("String extractor");
        mode_menu ->append("MD5");
        mode_menu ->append("SHA1");
        mode_menu ->append("SHA256");

        // compact mode, lowercase and output will be additional settings / options

        m_mode_popover.set_menu_model(mode_menu);

        m_mode_popover.set_parent(parent_button);
    }

    m_mode_popover.popup();

}

void CustomWindow::show_about(Gtk::Window& parent_window) {
    std::cout << "CustomWindow class: Launching About" << std::endl;

    auto* about_window = Gtk::make_managed<Gtk::Window>();
    about_window->set_title("About");
    about_window->set_default_size(750, 500);
    about_window->set_resizable(false);
    about_window->set_transient_for(parent_window);
    about_window->set_modal(true);

    auto* master_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    master_box->set_spacing(15); 
    master_box->set_margin(20);

    auto* app_version = Gtk::make_managed<Gtk::Label>("Version 1.0.0 (Stable)");
    app_version->set_halign(Gtk::Align::START);
    app_version->add_css_class("about-subtitle");
    master_box->append(*app_version);

    fill_text_tag_table();
    fill_buffer();

    m_about_text_view.set_buffer(m_ref_text_buffer);
    m_about_text_view.set_editable(false);
    m_about_text_view.set_cursor_visible(false);

    auto* scrolled_window = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolled_window->set_child(m_about_text_view);
    scrolled_window->set_min_content_width(400);
    scrolled_window->set_min_content_height(250);
    scrolled_window->set_expand(true);
    master_box->append(*scrolled_window);
    
    about_window->set_child(*master_box);
    about_window->present();
} 

void CustomWindow::fill_text_tag_table() {
    m_ref_text_tag_table = Gtk::TextTagTable::create();
    auto text_tag = Gtk::TextTag::create("plain-text");
    text_tag->property_wrap_mode() = Gtk::WrapMode::WORD;

    m_ref_text_tag_table->add(text_tag);

    text_tag = Gtk::TextTag::create("script");
    text_tag->property_wrap_mode() = Gtk::WrapMode::NONE;
    text_tag->property_indent() = 20;
    text_tag->property_family() = "Monospace";
    text_tag->property_background() = "rgb(92%, 92%, 92%)";
    m_ref_text_tag_table->add(text_tag);

}

void CustomWindow::fill_buffer() {

    m_ref_text_buffer = Gtk::TextBuffer::create(m_ref_text_tag_table);

    auto iterable = m_ref_text_buffer->begin();

    iterable = m_ref_text_buffer->insert_with_tag(iterable, "Forx is a binary analysis tool used for forensic purposes."
    " It just works.\n\n",
    " Test");
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

