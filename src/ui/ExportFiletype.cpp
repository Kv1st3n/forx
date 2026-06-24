#include <string>
#include <iostream>
#include <fstream>
#include <gtkmm.h>
#include "ExportFiletype.h"

ExportFiletype::ExportFiletype() {}

void ExportFiletype::export_as_txt(const std::string& final_output_path) {
    std::ofstream out_file(final_output_path);

    // current placeholder text

    if (out_file.is_open()) {
        out_file << "# Forx Forensic Log Output\n";
        out_file << "===========================\n";
        out_file << "00000000  23 69 6E 63 6C 75 64 65  |#include |\n"; 
        out_file.close();
        std::cout << "Successfully saved TXT log." << std::endl;
    }
}

void ExportFiletype::export_as_png(const std::string& final_output_path) {
    auto surface = Cairo::ImageSurface::create(Cairo::ImageSurface::Format::ARGB32, 800, 400);
    auto cr = Cairo::Context::create(surface);
    
    cr->set_source_rgb(0.1, 0.1, 0.1);
    cr->paint();
    
    cr->set_source_rgb(0.0, 1.0, 0.0);
    cr->select_font_face("Sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
    cr->set_font_size(14.0);
    cr->move_to(20, 40);
    cr->show_text("FORX IMAGE EXPORT - DATA VALID");
    
    surface->write_to_png(final_output_path);
    std::cout << "Successfully saved PNG visualization." << std::endl;
}

void ExportFiletype::export_as_pdf(const std::string& final_output_path) {
    auto op = Gtk::PrintOperation::create();
    op->set_export_filename(final_output_path);

    op->signal_begin_print().connect([op](const Glib::RefPtr<Gtk::PrintContext>& /* context */) {
        op->set_n_pages(1); 
    });

    op->signal_draw_page().connect([](const Glib::RefPtr<Gtk::PrintContext>& context, int page_nr) {
        (void)page_nr;
        auto cr = context->get_cairo_context();
        
        cr->select_font_face("Sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
        cr->set_font_size(12.0);
        cr->move_to(50.0, 50.0);
        cr->show_text("Raw Forensic Dump Data Output Placeholder");
    });

    op->run(Gtk::PrintOperation::Action::EXPORT);
}