#include "HistogramWidget.h"

HistogramWidget::HistogramWidget(QWidget* parent) : QWidget(parent)
{
	auto szPol = sizePolicy();
	szPol.setVerticalPolicy(QSizePolicy::Expanding);
	setSizePolicy(szPol);
	memset(data, 0, sizeof(uint) * 256);
}

void HistogramWidget::setData(uint *data)
{
	for (int i = 0; i < 256; i++)
		this->data[i] = data[i];
	repaint();
}

void HistogramWidget::paintEvent(QPaintEvent* event)
{
	painter.begin(&picture);
	painter.setPen(Qt::black);

	painter.drawLine(0, 0, 0, height());
	painter.drawLine(0, height() - 1, width(), height() - 1);

	painter.setPen(Qt::gray);
	painter.setBrush(Qt::gray);

	int h = height();

	int w = width();

	uint _max = 1;

	for (int i = 0; i < 256; i++)
		if (data[i] > _max)
			_max = data[i];

	double dh = height() / (double)_max;

	double dw = (width() - 1) / (double)256;

	for (int i = 0; i < 256; i++)
	{
		painter.drawRect(QRectF(dw * i + 2, height() - 2 - data[i] * dh, dw, data[i] * dh));
	}
	painter.end();
	painter.begin(this);
	painter.drawPicture(0, 0, picture);
	painter.end();
}
