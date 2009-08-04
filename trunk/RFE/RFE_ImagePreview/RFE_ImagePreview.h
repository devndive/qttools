#ifndef __RFE_IMAGEPREVIEW_H__
#define __RFE_IMAGEPREVIEW_H__

#include <QWidget>
#include <QPainter>

namespace RFE
{

class ImagePreview : public QWidget
{
Q_OBJECT

private:
   QImage image;

public:
   ImagePreview(QString&);
   void paintEvent(QPaintEvent*);
};

} // namespace RFE

#endif // __RFE_IMAGEPREVIEW_H__