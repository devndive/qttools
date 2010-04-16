#ifndef __GET_ALL_INCLUDES_H__
#define __GET_ALL_INCLUDES_H__

#include <QtCore/QFileInfo>

class QString;
class QStringList;

namespace PFG
{

void getAllIncludes(QString path, QFileInfoList h_files, QFileInfoList cpp_files, QStringList& includes);

} // namespace PFG

#endif // __GET_ALL_INCLUDES_H__

