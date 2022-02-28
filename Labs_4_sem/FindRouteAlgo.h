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
		None,
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
	int calcRouteToCell(const Cell* start, const Cell* end);
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
	bool considerNearPoints(int i);
	int findEvristicDistance(const Cell* start);
	Cell::Direction findDirection(const Cell* first, const Cell* second);
};

class DekstraRouteAlgo : public FindRouteAlgo
{
public:
	DekstraRouteAlgo(Cell* start_point, Cell* finish_point, QList<QList<Cell*>>& cells);
	void findRoute() override;
	bool isFinished() override;
private:
	void drawRoute(Cell* end, bool val);
	struct DekstraRouteAlgoCell
	{
		DekstraRouteAlgoCell(Cell* cell_ptr, double prior);
		DekstraRouteAlgoCell();
		Cell* cell_ptr = nullptr;
		double prior;
		bool operator <(const DekstraRouteAlgoCell& right) const;
	};
	QList<Cell*> H;
	QMap<Cell*, double> D;
	std::vector	<DekstraRouteAlgoCell> Q;
	int considerPoint;
	Cell* v = nullptr;
	DekstraRouteAlgoCell cur;
	Cell* u = nullptr;
};