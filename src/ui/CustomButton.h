#ifndef GTKMM_CUSTOMBUTTON_H
#define GTKMM_CUSTOMBUTTON_H

#include <gtkmm/button.h>
#include <string>

class Custom_Button : public Gtk::Button {

    public:
        Custom_Button(const std::string& label_text);
        virtual ~Custom_Button() = default;

};

#endif