#pragma once
#include "Cell.h"
class FindRouteAlgo
{
public:
	enum class Algorithm
	{
		AStart,
		Dekstra
	};
	virtual void startFindRoute(Cell& start_point, Cell& finish_point, QList<QList<Cell*>>& cells) = 0;
};


class AStartRouteAlgo: public FindRouteAlgo
{
public:
	void startFindRoute(Cell& start_point, Cell& finish_point, QList<QList<Cell*>>& cells) override;
};


class DekstraRouteAlgo : public FindRouteAlgo
{
public:
	void startFindRoute(Cell& start_point, Cell& finish_point, QList<QList<Cell*>>& cells) override;
};