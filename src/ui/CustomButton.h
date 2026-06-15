#ifndef GTKMM_CUSTOMBUTTON_H
#define GTKMM_CUSTOMBUTTON_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class Custom_Button : public Gtk::Window {

    public:
        Custom_Button();
        virtual ~Custom_Button();

    protected:
        void on_button_clicked();

        Gtk::Button m_button;
};

#endif