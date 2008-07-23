#ifndef __WRITE_PRO_FILE_H__
#define __WRITE_PRO_FILE_H__

#include <string>
#include <iostream>
#include "definitions.h"

namespace PFG
{

void writeProFile(stringList &h_files, stringList &cpp_files, stringList &qrc_files, stringList &uic_files, stringList &depend_paths, stringList &modules, std::string &templateType, std::string &target, std::streambuf *sbuf, stringList &libDirs, stringList &libs);

} // namespace PFG

#endif // __WRITE_PRO_FILE_H__

