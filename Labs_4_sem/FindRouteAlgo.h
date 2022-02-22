#pragma once
#include "Cell.h"

class FindRouteAlgo:public QObject
{
	Q_OBJECT;
public:

	FindRouteAlgo(Cell* start_point, Cell* finish_point, QList<QList<Cell*>>& cells);
	~FindRouteAlgo();
	enum class Algorithm
	{
		AStart,
		Dekstra
	};

	virtual bool isFinished() = 0;

public slots:
	virtual void findRoute() = 0;

protected:
	Cell* start_point = nullptr;
	Cell* finish_point = nullptr;
	QMap<Cell*, QList<Cell*>> cellsGraph;
};


class AStartRouteAlgo: public FindRouteAlgo
{
public:
	AStartRouteAlgo(Cell* start_point, Cell* finish_point, QList<QList<Cell*>>& cells);
	void findRoute() override;
	bool isFinished() override;
private:
	int consideredPoint = 0;
	QList<Cell*> open_list;
	Cell* cur_point = nullptr;
	void considerNearPoints(int i);
	int findEvristicDistance(const Cell* start);
	int calcRouteToCell(const Cell* start, const Cell* end);
	Cell::Direction findDirection(const Cell* first, const Cell* second);
};

class DekstraRouteAlgo : public FindRouteAlgo
{
public:
	DekstraRouteAlgo(Cell* start_point, Cell* finish_point, QList<QList<Cell*>>& cells);
	void findRoute() override;
	bool isFinished() override;
};