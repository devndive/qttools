#include "RFE_ImagePreview.h"

namespace RFE
{

ImagePreview::ImagePreview(QString &filename)
: image(filename)
{
	setWindowTitle(QString("RFE").append(tr("Preview")).append("- ") + filename.mid(filename.lastIndexOf('/') + 1));
	if( image.width() > 50 )
	{
		setGeometry( 100, 100, image.width() + 10, image.height() + 10 );
	}
	else
	{
		setGeometry( 100, 100, 50, 50 );
	}
}

void ImagePreview::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if( image.width() < 50 )
	{
		painter.drawImage((width() -image.width()) / 2, (height() -image.height()) / 2, image);
	}
	else
	{
		if( image.scaledToWidth(width()).height() > height() )
		{
			painter.drawImage(0, 1, image.scaledToHeight(height()));
		}
		else
		{
			painter.drawImage(0, 1, image.scaledToWidth(width()));
		}
	}
}

} // namespace RFE