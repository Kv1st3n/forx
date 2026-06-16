#include "CustomButton.h"
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <iostream>
#include <string>

Custom_Button::Custom_Button(const std::string& label) : Gtk::Button(label) {
    set_margin_start(6);
    set_margin_end(6);
    set_margin_top(6);
    set_margin_bottom(6);
    set_hexpand(false);
}

