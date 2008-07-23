#ifndef __WRITE_PRO_FILE_H__
#define __WRITE_PRO_FILE_H__

#include <string>
#include <iostream>
#include "definitions.h"

namespace PFG
{

void writeProFile(fileList &h_files, fileList &cpp_files, fileList &qrc_files, fileList &uic_files, pathList &depend_paths, std::string &modules, std::string &templateType, std::string &target, std::streambuf *sbuf);

} // namespace PFG

#endif // __WRITE_PRO_FILE_H__

