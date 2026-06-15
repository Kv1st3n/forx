#include <iostream>
#include <gtkmm.h>
#include <gtkmm/button.h>
#include "CustomButton.h"

class ForxWindow : public Gtk::ApplicationWindow {
public:
    ForxWindow() {
        set_title("forx");
        set_default_size(1200, 800);

        setup_custom_header();
        
        m_main_box.set_orientation(Gtk::Orientation::VERTICAL);
        m_main_box.set_margin(15);

        m_label.set_text("Welcome Forx");
        m_main_box.append(m_label);
        
        
        set_child(m_main_box);
    }

protected:
    void on_button_clicked() {
        std::cout << "Action executed!" << std::endl;
    }

private:

    void setup_custom_header() {
        auto *title_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
        auto *title_lable = Gtk::make_managed<Gtk::Label>("<b>forx</b>");
        title_lable -> set_use_markup(true);

        auto *subtitle_label = Gtk::make_managed<Gtk::Label>("Binary analysis tool");
        subtitle_label->set_css_classes({"subtitle"});

        title_box -> append(*title_lable);
        title_box -> append(*subtitle_label);

        m_header_bar.set_title_widget(*title_box);

        m_button.set_label("Execute");
        m_button.set_size_request(100, 34);
        m_button.signal_clicked().connect(
            sigc::mem_fun(*this, &ForxWindow::on_button_clicked)
        );

        m_header_bar.pack_start(m_button);

        m_header_bar.set_show_title_buttons(true);

        set_titlebar(m_header_bar);

    }

    void setup_custom_buttons() {
        m_button.set_label("Execute");
        m_button.set_size_request(200, 60); 
        m_button.set_halign(Gtk::Align::CENTER); 
        m_button.set_margin_top(50); 
        
        m_button.signal_clicked().connect(
            sigc::mem_fun(*this, &ForxWindow::on_button_clicked)
        );
    }

    Gtk::Box m_main_box;
    Gtk::Label m_label;
    Gtk::Button m_button;
    Gtk::HeaderBar m_header_bar;
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
        auto *window = new ForxWindow();
        add_window(*window);
        window->present();
    }
};

int main(int argc, char **argv) {
    auto app = ForxApp::create();
    return app->run(argc, argv);
}