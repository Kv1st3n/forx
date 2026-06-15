#include "CustomButton.h"
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <iostream>

Custom_Button::Custom_Button() {
    auto label = Gtk::make_managed<Gtk::Label>("Execute");
    label->set_expand(true);

    auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
    hbox->append(*label);

    m_button.set_child(*hbox);

    m_button.signal_clicked().connect(sigc::mem_fun(*this, &Custom_Button::on_button_clicked));

    m_button.set_margin(10);
    set_child(m_button);
}

Custom_Button::Custom_Button() {}

void Custom_Button::on_button_clicked() {
    std::cout << "Action executed!" << std::endl;
}