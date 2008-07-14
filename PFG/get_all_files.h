#ifndef __GET_ALL_FILES_H__
#define __GET_ALL_FILES_H__

#include "definitions.h"

void get_all_files(char *path, file_list &h_files, file_list &cpp_files, file_list &qrc_files, file_list &uic_files, path_list &depend_paths);

#endif // __GET_ALL_FILES_H__
