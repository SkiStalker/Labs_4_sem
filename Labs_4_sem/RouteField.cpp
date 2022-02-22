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

	connect(updateTimer, &QTimer::timeout, this, &RouteField::updateField);
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
		if (cur_cell->getRouteStat() != Cell::RouteStat::Finish && cur_cell->getType() != Cell::Type::Wall)
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
	switch (algorithm_type)
	{
	case FindRouteAlgo::Algorithm::AStart:
		curfindAlgo = new AStartRouteAlgo(startPoint, endPoint, cells);
		break;
	case FindRouteAlgo::Algorithm::Dekstra:
		curfindAlgo = new DekstraRouteAlgo(startPoint, endPoint, cells);
		break;
	default:
		// TODO : throw exception();
		break;
	}
	updateTimer->start();
}


void RouteField::updateField()
{
	curfindAlgo->findRoute();
	update();
	QApplication::processEvents();
	QThread::currentThread()->usleep(1000000 / 10);
	if (curfindAlgo->isFinished())
	{
		updateTimer->stop();
		delete curfindAlgo;
		curfindAlgo = nullptr;
		auto tmp_cell = endPoint;
		while (tmp_cell != startPoint)
		{
			tmp_cell->setStatus(Cell::Status::Passed);
			tmp_cell = tmp_cell->getParentCell();
		}
		tmp_cell->setStatus(Cell::Status::Passed);
		update();
	}
}
