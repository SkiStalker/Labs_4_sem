#include "RouteField.h"

RouteField::RouteField(const Ui::DekstraClass* ui)
{
    this->ui = ui;
}

void RouteField::setStartPoint(Cell* point)
{
    if (startPoint)
    {
        startPoint->setRouteStat(Cell::RouteStat::NotRoute);
        startPoint->update();
    }
    startPoint = point;
    startPoint->setRouteStat(Cell::RouteStat::Start);
    startPoint->update();
}

const Cell* RouteField::getStartPoint() const
{
    return startPoint;
}

void RouteField::setEndPoint(Cell* point)
{
    if (endPoint)
    {
        endPoint->setRouteStat(Cell::RouteStat::NotRoute);
        endPoint->update();
    }
    endPoint = point;
    endPoint->setRouteStat(Cell::RouteStat::Finish);
    endPoint->update();
}

const Cell* RouteField::getEndPoint() const
{
    return endPoint;
}

void RouteField::mousePressEvent(QGraphicsSceneMouseEvent* ev)
{
    if (ui->setStartPointButton->isChecked())
    {
        auto cur_cell = (Cell*)items(ev->scenePos()).first();
        if(cur_cell->getRouteStat() != Cell::RouteStat::Finish && cur_cell->getType() != Cell::Type::Wall)
            setStartPoint(cur_cell);
    }
    else if (ui->setEndPointButton->isChecked())
    {
        auto cur_cell = (Cell*)items(ev->scenePos()).first();
        if (cur_cell->getRouteStat() != Cell::RouteStat::Start && cur_cell->getType() != Cell::Type::Wall)
            setEndPoint(cur_cell);
    }
}

void RouteField::startFindingRoute(FindRouteAlgo::Algorithm algorithm_type)
{
    FindRouteAlgo* alg = nullptr;
    switch (algorithm_type)
    {
    case FindRouteAlgo::Algorithm::AStart:
        alg = new AStartRouteAlgo();
        break;
    case FindRouteAlgo::Algorithm::Dekstra:
        alg = new DekstraRouteAlgo();
        break;
    default:
        // TODO : throw exception();
        break;
    }

    alg->startFindRoute(*startPoint, *endPoint, cells);
    delete alg;
}
