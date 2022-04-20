#pragma once

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QString>

class ImageWidget : public QWidget
{
	Q_OBJECT

private:
	QPainter curPainter;
	QImage* image = nullptr;

public:

	void paintEvent(QPaintEvent* event) override;

	QImage& getImage() const;

	bool loadImage(const QString& path);

	void clearImage();

	ImageWidget(QWidget *parent = Q_NULLPTR);
	~ImageWidget();
};
