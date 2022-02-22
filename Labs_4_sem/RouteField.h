#pragma once
#include "INCLUDES.h"
#include "Cell.h"
#include "ui_Dekstra.h"
#include "FindRouteAlgo.h"


class RouteField :
    public QGraphicsScene
{
    Q_OBJECT;


public:
    RouteField(const Ui::DekstraClass* ui);
    QList<QList<Cell*>> cells;

    void setStartPoint(Cell* point);

    const Cell* getStartPoint() const;


    void setEndPoint(Cell* point);

    const Cell* getEndPoint() const;

    void mousePressEvent(QGraphicsSceneMouseEvent* ev) override;

    void startFindingRoute(FindRouteAlgo::Algorithm algorithm_type);

private:
    const Ui::DekstraClass* ui = nullptr;
    Cell* startPoint = nullptr;
    Cell* endPoint = nullptr;
    FindRouteAlgo* curfindAlgo = nullptr;
    QTimer* updateTimer = new QTimer(this);

private slots:
    void updateField();
};

