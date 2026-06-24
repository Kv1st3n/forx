#include "CustomWindow.h"
#include "CustomButton.h"
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
        auto master_menu = Gio::Menu::create();
        auto mode_menu = Gio::Menu::create();

        std::vector<std::string> modes = {"Hex dump", "Reverse Mode", "File identifier", "Directory Scanner"
        "String extractor", "MD5", "SHA1", "SHA256", "SHA512"};

        for (const auto& mode : modes) {
            mode_menu ->append(mode);
        }

        auto sub_menu = Gio::Menu::create();

        std::vector<std::string> sub_modes = {
            "Compact", "Lowercase", "Output"
        };

        for (const auto& sub_mode : sub_modes) {
            sub_menu ->append(sub_mode);
        }

        master_menu ->append_section(mode_menu);
        master_menu ->append_section(sub_menu);

        m_mode_popover.set_menu_model(master_menu);
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

    // always create a 'master'-box, which then contains all the customizable features
    // due to gtk and its architecture, it is the only way
    auto* master_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    master_box->set_spacing(15); 
    master_box->set_margin(20);

    // specifies the current version of the tool
    auto* app_version = Gtk::make_managed<Gtk::Label>("Version 1.0.0 (Stable)");
    app_version->set_halign(Gtk::Align::START);
    app_version->add_css_class("about-subtitle");
    master_box->append(*app_version);

    // calls the customized functions for the text in about section
    fill_text_tag_table();
    fill_buffer();

    m_about_text_view.set_buffer(m_ref_text_buffer);
    m_about_text_view.set_editable(false);
    m_about_text_view.set_cursor_visible(false);

    auto* visual_divider = Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::HORIZONTAL);
    master_box->append(*visual_divider);

    // two buttons, left and right, left is about the tool, right is about us / license and stuff 
    Gtk::Grid* m_grid = create_button_grid_for_about_section();   

    master_box->append(*m_grid);

    auto* scrolled_window = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolled_window->set_child(m_about_text_view);
    scrolled_window->set_min_content_width(400);
    scrolled_window->set_min_content_height(250);
    scrolled_window->set_expand(true);
    master_box->append(*scrolled_window);
    
    about_window->set_child(*master_box);
    about_window->present();
} 

// creates a grid of x-amount of buttons for about
Gtk::Grid* CustomWindow::create_button_grid_for_about_section() {
    m_button_about_tool.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &CustomWindow::fill_buffer_about), 1));
    m_button_about_us.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &CustomWindow::fill_buffer_about), 2));

    m_grid.attach(m_button_about_tool, 0, 0);
    m_grid.attach(m_button_about_us, 1, 0);

    return &m_grid;
}

void CustomWindow::fill_buffer_about(const int& choice) {
    if (!m_ref_text_buffer) {
        m_ref_text_buffer = Gtk::TextBuffer::create(m_ref_text_tag_table);
        m_about_text_view.set_buffer(m_ref_text_buffer);
    }
    
    // clear the current text
    m_ref_text_buffer->set_text(""); 
    auto iterable = m_ref_text_buffer->begin();

    // depending on choice, display the appropiate text
    if (choice == 1) {
        // ── overview ─────────────────────────────────────────
        iterable  = m_ref_text_buffer->insert_with_tag(iterable ,
            "forx — Binary Analysis Tool\n"
            "===========================\n\n"
            "forx is a forensics-focused workbench for binary visualisation, "
            "file auditing, and system data analysis. The graphical interface "
            "mirrors the CLI version, exposing every feature through a clean "
            "desktop workspace.\n\n",
            "plain-text");

        iterable  = m_ref_text_buffer->insert_with_tag(iterable ,
            "Features\n"
            "--------\n",
            "plain-text");

        // feature list — one entry per insert for clarity
        const std::vector<std::string> features = {
            "  Hex Viewer       Raw memory offsets, hex values, and ASCII column\n",
            "  Mode Selector    Switch between standard, compact, and lowercase output\n",
            "  File Identifier  Magic byte detection against a runtime signature database\n",
            "  Directory Scan   Recursive file type cataloguing across a directory tree\n",
            "  Checksum Engine  MD5, SHA1, and SHA256 integrity verification\n",
            "  String Extractor Isolates printable ASCII sequences from binary files\n",
        };

        for (const auto &line : features)
            iterable  = m_ref_text_buffer->insert_with_tag(iterable , line, "plain-text");

        iterable  = m_ref_text_buffer->insert_with_tag(iterable ,
            "\nPlatform\n"
            "--------\n"
            "  macOS — compiled with Apple Clang via Xcode Command Line Tools\n"
            "  GTK4 and gtkmm4 for the graphical layer\n",
            "plain-text");

    } else if (choice == 2) {
        // ── build info ───────────────────────────────────────
        iterable  = m_ref_text_buffer->insert_with_tag(iterable ,
            "Build Information\n"
            "=================\n\n"
            "  Version   :  forx 0.1.0\n"
            "  Language  :  C / C++17\n"
            "  Compiler  :  Apple Clang (clang-1700.4.4.1)\n"
            "  UI Layer  :  gtkmm4 — C++ bindings for GTK4\n\n",
            "plain-text");

        iterable  = m_ref_text_buffer->insert_with_tag(iterable ,
            "Dependencies\n"
            "------------\n\n",
            "plain-text");

        iterable  = m_ref_text_buffer->insert_with_tag(iterable ,
            "  # install dependencies\n"
            "  brew install openssl gtk4 gtkmm4\n\n"
            "  # build\n"
            "  make clean && make\n\n"
            "  # run CLI\n"
            "  ./forx -h <file>\n\n"
            "  # run GUI\n"
            "  ./forx --gui\n",
            "script");

        iterable  = m_ref_text_buffer->insert_with_tag(iterable ,
            "\nSource\n"
            "------\n"
            "  https://github.com/Kv1st3n/forx\n",
            "plain-text");

    } else {
        m_ref_text_buffer->insert_with_tag(iterable ,
            "Error: unknown section identifier.\n",
            "plain-text");
    }
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
    text_tag->property_background() = "#EFEFEF";
    text_tag->property_foreground()  = "#1A1A2E";
    text_tag->property_pixels_above_lines() = 4;
    text_tag->property_pixels_below_lines() = 4;
    m_ref_text_tag_table->add(text_tag);

}

void CustomWindow::fill_buffer() {

    m_ref_text_buffer = Gtk::TextBuffer::create(m_ref_text_tag_table);

    auto iterable = m_ref_text_buffer->begin();

    const std::vector<std::pair<std::string, std::string>> sections = {
        { "forx — Binary Analysis Tool\n\n",              "plain-text" },
        { "A forensics workbench for binary inspection, ",  "plain-text" },
        { "file identification, and system data analysis.\n","plain-text" },
    };

    for (const auto &[text, tag] : sections)
        iterable = m_ref_text_buffer->insert_with_tag(iterable, text, tag);
}

void CustomWindow::show_save(Gtk::Window& parent_window) {
    auto* save_window = Gtk::make_managed<Gtk::Window>();
    save_window->set_title("Save");
    save_window->set_default_size(600, 250);
    save_window->set_resizable(true);
    save_window->set_transient_for(parent_window);
    save_window->set_modal(true);

    auto* master_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    master_box->set_margin(25); 
    master_box->set_spacing(15);

    auto* save_grid = Gtk::make_managed<Gtk::Grid>();
    save_grid->set_row_spacing(15);   
    save_grid->set_column_spacing(12);
    master_box->append(*save_grid);

    // row 0, file name entry
    auto* type_file_name_label = Gtk::make_managed<Gtk::Label>("Save as:");
    type_file_name_label->set_halign(Gtk::Align::START);

    m_entry.set_placeholder_text("Enter file name (e.g., analysis_dump)...");
    
    m_entry.set_hexpand(true); 
    m_entry.set_halign(Gtk::Align::FILL);

    m_button_file_name.set_label("Submit");
    m_button_file_name.set_halign(Gtk::Align::END);
    m_button_file_name.signal_clicked().connect(sigc::mem_fun(*this, &CustomWindow::on_submit));

    save_grid->attach(*type_file_name_label, 0, 0, 1, 1);
    save_grid->attach(m_entry,               1, 0, 1, 1);
    save_grid->attach(m_button_file_name,   2, 0, 1, 1);

    // row 1, file format choice
    auto* type_label = Gtk::make_managed<Gtk::Label>("Select Export Format:");
    type_label->set_halign(Gtk::Align::START);

    auto* type_button = Gtk::make_managed<Gtk::Button>("Choose Type...");
    
    type_button->set_hexpand(true);
    type_button->set_halign(Gtk::Align::FILL);

    save_grid->attach(*type_label,  0, 1, 1, 1);
    save_grid->attach(*type_button, 1, 1, 1, 1); 

    type_button->signal_clicked().connect([this, type_button]() {
        show_file_types(*type_button);
    });

    // row 2, file path dialog
    auto* path_label = Gtk::make_managed<Gtk::Label>("Destination Folder:");
    path_label->set_halign(Gtk::Align::START);

    auto* chosen_path_label = Gtk::make_managed<Gtk::Label>("No folder selected...");
    chosen_path_label->set_halign(Gtk::Align::START);
    chosen_path_label->set_hexpand(true);

    auto* browse_button = Gtk::make_managed<Gtk::Button>("Browse...");
    browse_button->set_halign(Gtk::Align::END);

    save_grid->attach(*path_label,         0, 2, 1, 1);
    save_grid->attach(*chosen_path_label,  1, 2, 1, 1);
    save_grid->attach(*browse_button,      2, 2, 1, 1);

    browse_button->signal_clicked().connect([this, save_window, chosen_path_label]() {
        auto folder_dialog = Gtk::FileDialog::create();
        folder_dialog->set_title("Select Destination Folder");

        folder_dialog->select_folder(*save_window, [this, folder_dialog, chosen_path_label](const Glib::RefPtr<Gio::AsyncResult>& result) {
            try {
                Glib::RefPtr<Gio::File> folder = folder_dialog->select_folder_finish(result);
                
                m_selected_folder_path = folder->get_path();
                
                chosen_path_label->set_text(m_selected_folder_path);
            }
            catch (const Glib::Error& err) {
                std::cerr << "Folder selection canceled: " << err.what() << std::endl;
            }
        });
    });


    // row 3, final save button
    m_button_file_save.set_label("Save");
    m_button_file_name.set_halign(Gtk::Align::FILL);
    // final function that saves the file
    save_grid->attach(m_button_file_save, 2, 3, 1, 1);

    m_button_file_save.signal_clicked().connect([this, save_window]() {
        std::string filename = m_entry.get_text();

        if (m_selected_folder_path.empty()) {
            std::cerr << "Error: Please choose a destination folder first!" << std::endl;
            return; 
        }
        if (filename.empty()) {
            std::cerr << "Error: Please enter a filename!" << std::endl;
            return;
        }

        std::string final_output_path = m_selected_folder_path + "/" + filename;
        std::cout << "Executing download/save to: " << final_output_path << std::endl;

        // Call your actual file-writing function here using 'final_output_path'
        
        save_window->close(); // Close popup when done
    });

    save_window->set_child(*master_box);
    save_window->present();
}

void CustomWindow::on_submit() {
    Glib::ustring input = m_entry.get_text();
    std::cout << "User entered: " << input << std::endl;
}

void CustomWindow::show_file_types(Gtk::Button& parent_button) {

    if (!m_file_type_popover.get_parent()) {
        const std::vector<std::string> file_types = {
        "PDF", "PNG", "JPG", "CSV"
        };

        auto file_type_menu = Gio::Menu::create();

        for (const auto& file_type : file_types) {
            std::string format_id = file_type;
            std::transform(format_id.begin(), format_id.end(), format_id.begin(), ::tolower);
            
            file_type_menu->append(file_type, "win.save_as_format::" + format_id);
        }

        m_file_type_popover.set_menu_model(file_type_menu);
    }

    m_file_type_popover.unparent();
    m_file_type_popover.set_parent(parent_button);
    m_file_type_popover.popup();

}

void CustomWindow::show_settings(Gtk::Window& parent_window) {
    auto* settings_window = Gtk::make_managed<Gtk::Window>();
    settings_window->set_title("Settings");
    settings_window->set_default_size(900, 700);
    settings_window->set_resizable(true);
    settings_window->set_transient_for(parent_window);
    settings_window->set_modal(true);

    auto* master_window = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);

    settings_window->set_child(*master_window);
    settings_window->present();
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

// settings, light and dark mode

// maybe a function (for each) that does all of the set, append, etc
// maybe make a central function, that returns window, and in the function it does all the necessary setups like title, 
// resizable, etc