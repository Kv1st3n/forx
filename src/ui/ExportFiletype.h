#ifndef EXPORT_FILETYPE_H
#define EXPORT_FILETYPE_H

#include <string>

class ExportFiletype {
public:
    ExportFiletype();
    ~ExportFiletype() = default;

    void export_file();

protected:
    void export_as_pdf(const std::string& final_output_path);
};

#endif