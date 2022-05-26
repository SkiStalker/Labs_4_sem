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
	if (!image->load(path, "jpg"))
	{
		repaint();
		return false;
	}
	else
	{
		auto res = std::max(height(), width());
		*image = image->scaled(std::min(256, res), std::min(256, res));
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
