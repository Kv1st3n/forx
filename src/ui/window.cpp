#include <iostream>
#include <vector>
#include <string>
#include <gtkmm.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h> 
#include <gdkmm/display.h> 
#include "CustomButton.h"
#include "CustomWindow.h"

class ForxWindow : public Gtk::ApplicationWindow {
public:
    ForxWindow() {
        set_title("forx");
        set_default_size(1200, 800);

        // dark theme
        //Gtk::Settings::get_default()->property_gtk_application_prefer_dark_theme() = true;

        setup_custom_header();
        
        m_main_box.set_orientation(Gtk::Orientation::VERTICAL);
        m_main_box.set_margin(15);

        m_label.set_text("Welcome to Forx");
        m_main_box.append(m_label);
        
        
        set_child(m_main_box);
    }

    virtual ~ForxWindow() {}

    // setup button actions
protected:
    void on_open_clicked() { 
        std::cout << "Routing open action to CustomWindow context..." << std::endl; 
    
        m_file_picker_manager.show_picker(*this);
    }

    void on_mode_clicked() {
        m_mode_selector.show_mode_menu(m_button_mode);
    }

    void on_run_clicked()  { 
        std::cout << "Run clicked" << std::endl; 
    }

    void on_save_clicked() { 
        std::cout << "Save clicked" << std::endl; 
        m_save_mode.show_save(*this);
    }

    void on_about_clicked() {
        m_about_mode.show_about(*this);
    }

    void on_settings_clicked() {
        std::cout << "Settings clocked" << std::endl;
        m_settings_mode.show_settings(*this);
    }

private:

    // sets up header
    void setup_custom_header() {
        auto *title_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
        auto *title_lable = Gtk::make_managed<Gtk::Label>("<b>forx</b>");
        title_lable -> set_use_markup(true);

        auto *subtitle_label = Gtk::make_managed<Gtk::Label>("Binary analysis tool");
        subtitle_label->set_css_classes({"subtitle"});

        title_box -> append(*title_lable);
        title_box -> append(*subtitle_label);

        m_header_bar.set_title_widget(*title_box);

        setup_custom_buttons();

        // iterates and packs each button
        for (auto &btn : buttons) {
            m_header_bar.pack_start(*btn);
        }

        m_header_bar.set_show_title_buttons(true);

        set_titlebar(m_header_bar);

    }

    void setup_custom_buttons() {
        m_button_open.signal_clicked().connect(sigc::mem_fun(*this, &ForxWindow::on_open_clicked));
        m_button_mode.signal_clicked().connect(sigc::mem_fun(*this, &ForxWindow::on_mode_clicked));
        m_button_run.signal_clicked().connect(sigc::mem_fun(*this, &ForxWindow::on_run_clicked));
        m_button_save.signal_clicked().connect(sigc::mem_fun(*this, &ForxWindow::on_save_clicked));
        m_button_settings.signal_clicked().connect(sigc::mem_fun(*this, &ForxWindow::on_settings_clicked));
        m_button_about.signal_clicked().connect(sigc::mem_fun(*this, &ForxWindow::on_about_clicked));

    }

    Gtk::Box m_main_box;
    Gtk::Label m_label;
    Gtk::Button m_button;
    Gtk::HeaderBar m_header_bar;

    Custom_Button m_button_open{"Open File"};
    Custom_Button m_button_mode{"Mode"};
    Custom_Button m_button_run{"Run"};
    Custom_Button m_button_save{"Save"};
    Custom_Button m_button_settings{"Settings"};
    Custom_Button m_button_about{"About"};

    std::vector<Custom_Button*> buttons = {&m_button_open, &m_button_mode, &m_button_run, 
        &m_button_save, &m_button_settings, &m_button_about
    };

    CustomWindow m_file_picker_manager;
    CustomWindow m_mode_selector;
    CustomWindow m_about_mode;
    CustomWindow m_save_mode;
    CustomWindow m_settings_mode;
};

class ForxApp : public Gtk::Application {
public:
    static Glib::RefPtr<ForxApp> create() {
        return Glib::make_refptr_for_instance<ForxApp>(
            new ForxApp()
        );
    }

protected:
    ForxApp() : Gtk::Application("org.example.forx") {}

    void on_activate() override {

        auto provider = Gtk::CssProvider::create();
        provider->load_from_path("style.css");
        Gtk::StyleContext::add_provider_for_display(
            Gdk::Display::get_default(),
            provider,
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
        );

        auto *window = new ForxWindow();
        add_window(*window);
        window->present();
    }
};

int main(int argc, char **argv) {
    auto app = ForxApp::create();
    return app->run(argc, argv);
}