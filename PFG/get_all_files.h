#ifndef __GET_ALL_FILES_H__
#define __GET_ALL_FILES_H__

#include <string>
#include "definitions.h"

namespace PFG
{

void getAllFiles(const std::string &path, stringList &hFiles, stringList &cppFiles, stringList &qrcFiles, stringList &uicFiles, stringList &dependPaths);

} // namespace PFG

#endif // __GET_ALL_FILES_H__

