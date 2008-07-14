#ifndef __WRITE_PRO_FILE_H__
#define __WRITE_PRO_FILE_H__

#include <string>

#include "definitions.h"

void write_pro_file(file_list &h_files, file_list &cpp_files, file_list &qrc_files, file_list &uic_files, path_list &depend_paths, std::string &modules, std::string &templateType, std::string &target);

#endif // __WRITE_PRO_FILE_H__
