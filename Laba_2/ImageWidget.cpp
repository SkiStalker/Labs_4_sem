#include "ImageWidget.h"



ImageWidget::ImageWidget(QWidget* parent)
	: QWidget(parent)
{
	auto szPolicy = sizePolicy();
	szPolicy.setVerticalPolicy(QSizePolicy::Expanding);
	setSizePolicy(szPolicy);

	image = new QImage();
}

ImageWidget::~ImageWidget()
{
	delete image;
}

QImage& ImageWidget::getImage() const
{
	return *image;
}

bool ImageWidget::loadImage(const QString& path)
{
	if (!image->load(path))
	{
		repaint();
		return false;
	}
	else
	{
		auto w = width();
		auto h = height();
		*image = image->scaled(width(), height(), Qt::KeepAspectRatio);
		repaint();
		return true;
	}
}

void ImageWidget::clearImage()
{
	*image = QImage();
	repaint();
}

void ImageWidget::paintEvent(QPaintEvent* event)
{
	if (image)
	{
		curPainter.begin(this);
		curPainter.drawImage(0, 0, *image);
		curPainter.end();
	}
}
