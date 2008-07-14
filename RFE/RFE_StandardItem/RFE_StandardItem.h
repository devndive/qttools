#ifndef __RFE_STANDARDITEM_H__
#define __RFE_STANDARDITEM_H__

#include <QStandardItem>

namespace RFE
{

class StandardItem : public QStandardItem
{
private:
	QString path;

public:
	StandardItem();
	StandardItem( const QString & text );
	StandardItem( const QIcon & icon, const QString & text );
	StandardItem( int rows, int columns = 1 );

	void setPath(QString &p) { path = p; }
	QString getPath() { return path; }
};

} // namespace RFE

#endif // __RFE_STANDARDITEM_H__