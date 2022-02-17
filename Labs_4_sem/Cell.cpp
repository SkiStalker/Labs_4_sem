#include "Cell.h"

int Cell::sz = 60;

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
		painter->drawText(QPoint(sz/2 - 5, sz/2 + 5), txt);
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
