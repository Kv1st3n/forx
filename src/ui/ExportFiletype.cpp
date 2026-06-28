#include "ExportFiletype.h"
#include <fstream>
#include <iostream>

void ExportFiletype::set_content(const std::string &content) {
    m_content = content;
}

void ExportFiletype::dispatch(const std::string &path, const std::string &format) {
    if (format == "txt") {
        export_as_txt(path);
    }
    else if (format == "pdf") {
        export_as_pdf(path);
    }
    else if (format == "png") {
        export_as_png(path);
    }
    else if (format == "csv") {
        export_as_csv(path);
    }
    else {
        std::cerr << "Unknown format: " << format << "\n";
    }
}

void ExportFiletype::export_as_txt(const std::string &path) {
    std::ofstream out(path);
    if (!out) { 
        std::cerr << "Cannot write: " << path << "\n"; 
        return; 
    }
    out << m_content;
    std::cout << "Saved TXT: " << path << "\n";
}

void ExportFiletype::export_as_csv(const std::string &path) {
    std::ofstream out(path);
    if (!out) { 
        std::cerr << "Cannot write: " << path << "\n"; 
        return; 
    }
    out << "offset,hex,ascii\n" << m_content;
    std::cout << "Saved CSV: " << path << "\n";
}

void ExportFiletype::export_as_pdf(const std::string &path) {
    std::cout << "PDF not yet implemented: " << path << "\n";
}

void ExportFiletype::export_as_png(const std::string &path) {
    std::cout << "PNG not yet implemented: " << path << "\n";
}