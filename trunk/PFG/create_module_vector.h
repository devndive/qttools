#ifndef __CREATE_MODULE_VECTOR_H__
#define __CREATE_MODULE_VECTOR_H__

template <typename T>
class QList;
class QStringList;

namespace PFG
{

void createModuleVector( QList<QStringList> &moduleVectorShort, bool shortModules );

}

#endif // __CREATE_MODULE_VECTOR_H__
