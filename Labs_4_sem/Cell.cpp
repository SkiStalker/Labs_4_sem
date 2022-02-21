#include "Cell.h"

int Cell::sz = 60;

Cell::Cell(QPoint _pos)
{
	_position = _pos;
}

void Cell::setType(const Type& tp)
{
	this->tp = tp;
}

Cell::Type Cell::getType() const
{
	return tp;
}

void Cell::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QColor clr;

	switch (tp)
	{
	case Cell::Type::Wall:
		clr = QColor("black");
		break;
	case Cell::Type::Asphalt:
		clr = QColor("grey");
		break;
	case Cell::Type::Grass:
		clr = QColor("green");
		break;
	case Cell::Type::Sand:
		clr = QColor("yellow");
		break;
	case Cell::Type::Water:
		clr = QColor("blue");
		break;
	default:
		break;
	}
	painter->setBrush(QBrush(clr));
	painter->drawRect(QRect(0, 0, sz, sz));

	if (route_stat != RouteStat::NotRoute)
	{
		QString txt;
		if (route_stat == RouteStat::Start)
		{
			txt = "S";
		}
		else
		{
			txt = "F";
		}
		painter->save();
		QFont fnt = painter->font();
		fnt.setPointSizeF(20);
		painter->setFont(fnt);
		painter->drawText(QPoint(sz / 2 - 5, sz / 2 + 5), txt);
		painter->restore();
	}

	if (status != Status::Inactive)
	{
		if (status == Status::Active)
		{
			clr = QColor("pink");
		}
		else
		{
			clr = QColor("red");
		}
		painter->setBrush(QBrush(clr));
		painter->drawEllipse(QRect(0, 0, sz, sz));
	}

	if (consider != Considered::NotConsider)
	{
		painter->setPen(QColor("black"));
		painter->setBrush(QColor("black"));

		switch (consider)
		{
		case Cell::Considered::Left:
			// Draw rect
			painter->drawRect(QRect(sz / 2 - sz / 3, sz / 2 - sz / 30, sz / 1.5 - 5, sz / 15));
			// Draw triangle
			painter->drawPolygon(QPolygon({ QPoint(5, sz / 2), QPoint(15, sz / 2 - 10),QPoint(15, sz / 2 + 10) }));
			break;

		case Cell::Considered::TopLeft:
			painter->drawPolygon(QPolygon({ QPoint(14, 16) , QPoint(16, 14), QPoint(sz - 14, sz - 16), QPoint(sz - 16, sz - 14) }));
			painter->drawPolygon(QPolygon({ QPoint(10, 10), QPoint(10, 20), QPoint(20, 10) }));
			break;

		case Cell::Considered::Top:
			painter->drawRect(QRect(sz / 2 - sz / 30, sz / 2 - sz / 3, sz / 15, sz / 1.5 - 5));
			painter->drawPolygon(QPolygon({ QPoint(sz / 2, 5), QPoint(sz / 2 - 10, 15),QPoint(sz / 2 + 10, 15) }));
			break;

		case Cell::Considered::TopRight:
			painter->drawPolygon(QPolygon({ QPoint(sz - 14, 16) , QPoint(sz - 16, 14), QPoint(14, sz - 16), QPoint(16, sz - 14) }));
			painter->drawPolygon(QPolygon({ QPoint(sz - 10, 10), QPoint(sz - 10, 20), QPoint(sz - 20, 10) }));
			break;

		case Cell::Considered::Right:
			painter->drawRect(QRect(sz / 2 - sz / 3, sz / 2 - sz / 30, sz / 1.5 - 5, sz / 15));
			painter->drawPolygon(QPolygon({ QPoint(sz - 5, sz / 2), QPoint(sz - 15, sz / 2 - 10),QPoint(sz - 15, sz / 2 + 10) }));
			break;

		case Cell::Considered::BottomRight:
			painter->drawPolygon(QPolygon({ QPoint(14, 16) , QPoint(16, 14), QPoint(sz - 14, sz - 16), QPoint(sz - 16, sz - 14) }));
			painter->drawPolygon(QPolygon({ QPoint(sz - 10, sz - 10), QPoint(sz - 10, sz - 20), QPoint(sz - 20, sz - 10) }));
			break;

		case Cell::Considered::Bottom:
			painter->drawRect(QRect(sz / 2 - sz / 30, sz / 2 - sz / 3, sz / 15, sz / 1.5 - 5));
			painter->drawPolygon(QPolygon({ QPoint(sz / 2, sz - 5), QPoint(sz / 2 - 10, sz - 15),QPoint(sz / 2 + 10, sz - 15) }));
			break;

		case Cell::Considered::BottomLeft:
			painter->drawPolygon(QPolygon({ QPoint(sz - 14, 16) , QPoint(sz - 16, 14), QPoint(14, sz - 16), QPoint(16, sz - 14) }));
			painter->drawPolygon(QPolygon({ QPoint(10, sz - 10), QPoint(10, sz - 20), QPoint(20,sz-  10) }));
			break;

		default:
			break;
		}

		painter->setPen(QColor("green"));
		painter->drawText(QPoint(2, sz - 1), QString::number(cur_route));

		painter->setPen(QColor("blue"));
		painter->drawText(QPoint(sz - 7, sz - 1), QString::number(manhattan_distance));


		painter->setPen(QColor("red"));
		painter->drawText(QPoint(2, 11), QString::number(cell_weight));
	}

}

void Cell::setConsidered(Considered consider)
{
	this->consider = consider;
}

Cell::Considered Cell::getConsider() const
{
	return consider;
}

const QPoint& Cell::getPosition() const
{
	return _position;
}

void Cell::setClosed(bool closed)
{
	this->closed = closed;
}

bool Cell::getClosed() const
{
	return closed;
}

void Cell::setManhattanDistance(int dist)
{
	manhattan_distance = dist;
}

int Cell::getManhattanDistance() const
{
	return manhattan_distance;
}

void Cell::setCurrentRoute(int route)
{
	cur_route = route;
}

int Cell::getCurrentRoute() const
{
	return cur_route;
}

void Cell::setWeight(int weight)
{
	cell_weight = weight;
}

int Cell::getWeight() const
{
	return cell_weight;
}

void Cell::setStatus(const Status& st)
{
	this->status = st;
}

Cell::Status Cell::getStatus() const
{
	return status;
}

void Cell::setRouteStat(const RouteStat& r_st)
{
	route_stat = r_st;
}

Cell::RouteStat Cell::getRouteStat() const
{
	return route_stat;
}
