#ifndef __GET_ALL_FILES_H__
#define __GET_ALL_FILES_H__

#include <QtCore/QFileInfo>

class QString;
class QStringList;

namespace PFG
{

void getAllFiles(const QString path, QFileInfoList& hFiles, QFileInfoList& cppFiles, QFileInfoList& qrcFiles, QFileInfoList& uicFiles, QFileInfoList& dependPaths);

} // namespace PFG

#endif // __GET_ALL_FILES_H__

