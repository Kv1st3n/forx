#include <iostream>
#include <gtkmm.h>
#include <gtkmm/button.h>
#include "CustomButton.h"

class ForxWindow : public Gtk::ApplicationWindow {
public:
    ForxWindow() {
        set_title("forx");
        set_default_size(800, 600);

        m_main_box.set_orientation(Gtk::Orientation::VERTICAL);
        m_main_box.set_spacing(10);
        m_main_box.set_margin(15);

        m_label.set_text("forx — binary analysis tool");
        m_main_box.append(m_label);

        m_button.set_label("Execute");
        m_button.signal_clicked().connect(sigc::mem_fun(*this, &ForxWindow::on_button_clicked));
        m_main_box.append(m_button);
        
        set_child(m_main_box);
    }

protected:
    void on_button_clicked() {
        std::cout << "Action executed!" << std::endl;
    }

private:
    Gtk::Box m_main_box;
    Gtk::Label m_label;
    Gtk::Button m_button;
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