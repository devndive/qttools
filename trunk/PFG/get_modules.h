#ifndef __GET_MODULES_STRING_H__
#define __GET_MODULES_STRING_H__

class QString;
class QStringList;

namespace PFG
{

void getModules(QStringList& includes, QStringList& modules, bool useShortModules = false);

} // namespace PFG

#endif // __GET_MODULES_STRING_H__

