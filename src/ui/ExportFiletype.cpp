#include <string>
#include <iostream>
#include <fstream>
#include <gtkmm.h>
#include "ExportFiletype.h"

ExportFiletype::ExportFiletype() {}

void ExportFiletype::export_as_pdf(const std::string& final_output_path) {
    auto op = Gtk::PrintOperation::create();
    op->set_export_filename(final_output_path);

    op->signal_begin_print().connect([op](const Glib::RefPtr<Gtk::PrintContext>& /* context */) {
        op->set_n_pages(1); 
    });

    op->signal_draw_page().connect([](const Glib::RefPtr<Gtk::PrintContext>& context, int page_nr) {
        auto cr = context->get_cairo_context();
        
        cr->select_font_face("Sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
        cr->set_font_size(12.0);
        cr->move_to(50.0, 50.0);
        cr->show_text("Raw Forensic Dump Data Output Placeholder");
    });

    op->run(Gtk::PrintOperation::Action::EXPORT);
}