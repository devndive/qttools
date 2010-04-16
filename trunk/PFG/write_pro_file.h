#ifndef __WRITE_PRO_FILE_H__
#define __WRITE_PRO_FILE_H__

#include <QtCore/QFileInfo>

class QString;
class QStringList;
class QTextStream;
class QIODevice;

namespace PFG
{

void writeList(QDir basePath, QFileInfoList listToWrite, const QString &prefix, QIODevice *device, const QString &appender = " = ");
void writeProFile(QDir basePath, QFileInfoList headerFiles, QFileInfoList sourceFiles, QFileInfoList qrcFiles, QFileInfoList uicFiles, QFileInfoList dependPaths, QStringList modules, QString &templateType, QString &target, QIODevice *device, QStringList libDirs, QStringList libs);

} // namespace PFG

#endif // __WRITE_PRO_FILE_H__

