#ifndef __GET_ALL_FILES_H__
#define __GET_ALL_FILES_H__

#include <string>
#include "definitions.h"

void get_all_files(std::string &path, fileList &h_files, fileList &cpp_files, fileList &qrc_files, fileList &uic_files, pathList &depend_paths);

#endif // __GET_ALL_FILES_H__
