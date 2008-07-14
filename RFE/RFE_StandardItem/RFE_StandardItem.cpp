#include "RFE_StandardItem.h"

namespace RFE
{

StandardItem::StandardItem()
: QStandardItem()
{
}

StandardItem::StandardItem( const QString & text )
: QStandardItem(text)
{
}

StandardItem::StandardItem( const QIcon & icon, const QString & text )
: QStandardItem(icon, text)
{
}

StandardItem::StandardItem( int rows, int columns )
: QStandardItem(rows, columns)
{
}

} // namespace RFE