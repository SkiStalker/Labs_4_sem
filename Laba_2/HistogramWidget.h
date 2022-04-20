#pragma once
#include <QWidget>
#include <QSizePolicy>
#include <QPainter>
#include <QPicture>
#include <QPolygonF>
#include <QPointF>

using uint = unsigned int;

class HistogramWidget :
    public QWidget
{
private:
    uint data[256];
    QPainter painter;
    QPicture picture;
    
public:
    HistogramWidget(QWidget* parent = (QWidget*)nullptr);

    void setData(uint *data);

    void paintEvent(QPaintEvent* event) override;
};

