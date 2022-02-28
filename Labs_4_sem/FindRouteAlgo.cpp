#include "FindRouteAlgo.h"

AStartRouteAlgo::AStartRouteAlgo(Cell* start_point, Cell* finish_point, QList<QList<Cell*>>& cells) : FindRouteAlgo(start_point, finish_point, cells), cur_point(start_point)
{
	open_list.append(cur_point);
}

void AStartRouteAlgo::findRoute()
{
	if (!consideredPoint)
	{
		cur_point->setStatus(Cell::Status::Active);
		open_list.removeOne(cur_point);
		cur_point->setClosed(true);
		cur_point->update();
		considerNearPoints(consideredPoint);
		consideredPoint++;
	}
	else if (consideredPoint < cellsGraph[cur_point].size())
	{
		if (!considerNearPoints(consideredPoint))
		{
			consideredPoint++;
			while (consideredPoint < cellsGraph[cur_point].size() && !considerNearPoints(consideredPoint))
				consideredPoint++;
		}
		else
		{
			consideredPoint++;
		}
	}
	else
	{
		cellsGraph[cur_point].last()->setStatus(Cell::Status::Inactive);
		consideredPoint = 0;
		cur_point->setStatus(Cell::Status::Inactive);
		cur_point->setPassed(true);
		int min_weight = open_list.first()->getWeight();
		int min_ind = 0;
		for (int i = 1; i < open_list.size(); i++)
		{
			if (open_list[i]->getWeight() < min_weight)
			{
				min_weight = open_list[i]->getWeight();
				min_ind = i;
			}
		}
		cur_point = open_list[min_ind];
	}
}

bool AStartRouteAlgo::isFinished()
{
	return cur_point == finish_point;
}

bool AStartRouteAlgo::considerNearPoints(int i)
{
	if (i)
		cellsGraph[cur_point][i - 1]->setStatus(Cell::Status::Inactive);

	auto cur_cell = cellsGraph[cur_point][i];
	if (cur_cell->getType() != Cell::Type::Wall && !cur_cell->getClosed())
	{
		cur_cell->setStatus(Cell::Status::Processed);
		if (!open_list.contains(cur_cell))
		{
			cur_cell->setParentCell(cur_point);
			cur_cell->setDirection(findDirection(cur_point, cur_cell));
			open_list.append(cur_cell);

			cur_cell->setManhattanDistance(findEvristicDistance(cur_cell) * 10);

			cur_cell->setCurrentRoute(cur_point->getCurrentRoute() + calcRouteToCell(cur_point, cur_cell));

			cur_cell->setWeight(cur_cell->getManhattanDistance() + cur_cell->getCurrentRoute());

			cur_cell->update();

		}
		else
		{
			if (cur_point->getCurrentRoute() + calcRouteToCell(cur_point, cur_cell) < cur_cell->getCurrentRoute())
			{
				cur_cell->setParentCell(cur_point);
				cur_cell->setDirection(findDirection(cur_point, cur_cell));
				cur_cell->setCurrentRoute(cur_point->getCurrentRoute() + calcRouteToCell(cur_point, cur_cell));

				cur_cell->setWeight(cur_cell->getManhattanDistance() + cur_cell->getCurrentRoute());
				cur_cell->update();
			}
		}
		return true;
	}
	return false;
}

int AStartRouteAlgo::findEvristicDistance(const Cell* start)
{
	int dist = 0;
	int start_x = start->getPosition().x();
	int start_y = start->getPosition().y();
	int finish_x = finish_point->getPosition().x();
	int finish_y = finish_point->getPosition().y();
	while (start_x != finish_x)
	{
		dist++;
		start_x += (start_x > finish_x ? -1 : 1);
	}
	while (start_y != finish_y)
	{
		dist++;
		start_y += (start_y > finish_y ? -1 : 1);
	}
	return dist;
}

int FindRouteAlgo::calcRouteToCell(const Cell* start, const Cell* end)
{
	int dist = 0;
	auto tp = end->getType();

	switch (tp)
	{
	case Cell::Type::Asphalt:
		dist = 10;
		break;
	case Cell::Type::Grass:
		dist = 20;
		break;
	case Cell::Type::Sand:
		dist = 30;
		break;
	case Cell::Type::Water:
		dist = 40;
		break;
	}

	int dx = end->getPosition().x() - start->getPosition().x();
	int dy = end->getPosition().y() - start->getPosition().y();

	if (dx && dy)
		dist *= 1.4;

	return dist;
}

Cell::Direction AStartRouteAlgo::findDirection(const Cell* first, const Cell* second)
{
	int dx = second->getPosition().x() - first->getPosition().x();
	int dy = second->getPosition().y() - first->getPosition().y();

	if (dx < 0)
	{
		if (dy > 0)
		{
			return Cell::Direction::TopRight;
		}
		else if (dy < 0)
		{
			return Cell::Direction::BottomRight;
		}
		else
		{
			return Cell::Direction::Right;
		}
	}
	else if (dx > 0)
	{
		if (dy > 0)
		{
			return Cell::Direction::TopLeft;
		}
		else if (dy < 0)
		{
			return Cell::Direction::BottomLeft;
		}
		else
		{
			return Cell::Direction::Left;
		}
	}
	// dx == 0
	else
	{
		if (dy > 0)
		{
			return Cell::Direction::Top;
		}
		else if (dy < 0)
		{
			return Cell::Direction::Bottom;
		}
		else
		{
			return Cell::Direction::NotDirected;
		}
	}
	return Cell::Direction::NotDirected;
}



DekstraRouteAlgo::DekstraRouteAlgo(Cell* start_point, Cell* finish_point, QList<QList<Cell*>>& cells) : FindRouteAlgo(start_point, finish_point, cells)
{
	for (auto line : cells)
		for (auto cell : line)
		{
			if (cell->getPosition() == start_point->getPosition())
			{
				D[cell] = 0;
				Q.push_back(DekstraRouteAlgoCell(cell, 0));
			}
			else if(cell->getType() != Cell::Type::Wall)
			{
				D[cell] = INFINITY;
				Q.push_back(DekstraRouteAlgoCell(cell, INFINITY));
			}
		}
	std::make_heap(Q.begin(), Q.end());
	considerPoint = 0;
}

void DekstraRouteAlgo::findRoute()
{
	if (!considerPoint)
	{
		//if(v)
			//drawRoute(v, false);

		cur = Q.front();
		v = cur.cell_ptr;
		std::pop_heap(Q.begin(), Q.end());
		Q.pop_back();
		H.append(v);
		v->update();

		//drawRoute(v, true);
	}
	if (considerPoint < cellsGraph[v].size())
	{
		if (considerPoint)
			cellsGraph[v][considerPoint - 1]->setStatus(Cell::Status::Inactive);

		if (u)
			drawRoute(u, false);


		u = cellsGraph[v][considerPoint];
		if (u->getType() != Cell::Type::Wall)
		{
			if (!H.contains(u))
			{
				int route = calcRouteToCell(v, u);
				if (D[v] + route < D[u])
				{
					D[u] = D[v] + route;
					for (auto& q : Q)
					{
						if (q.cell_ptr == u)
						{
							q.prior = D[u];
							break;
						}
					}
					std::make_heap(Q.begin(), Q.end());
					u->setParentCell(v);
				}
			}
			drawRoute(u, true);
		}
		considerPoint++;
	}
	else
	{
		drawRoute(u, false);
		v->setStatus(Cell::Status::Inactive);
		v->setPassed(true);
		v->update();
		cellsGraph[v].last()->setStatus(Cell::Status::Inactive);
		cellsGraph[v].last()->update();
		considerPoint = 0;
	}
}

bool DekstraRouteAlgo::isFinished()
{
	return v == finish_point;
}

void DekstraRouteAlgo::drawRoute(Cell* end, bool val)
{
	while (end->getParentCell())
	{
		end = end->getParentCell();
		end->setInRoute(val);
		end->update();
	}
	end->setInRoute(val);
	end->update();
}

FindRouteAlgo::FindRouteAlgo(Cell* start_point, Cell* finish_point, QList<QList<Cell*>>& cells) :start_point(start_point), finish_point(finish_point)
{
	for (auto line : cells)
	{
		for (auto cell : line)
		{
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
					// left
				case 0:
				{
					if (cell->getPosition().x() - 1 > -1)
					{
						cellsGraph[cell].append(cells[cell->getPosition().y()][cell->getPosition().x() - 1]);
					}
					break;
				}
				// top left
				case 1:
				{
					if (cell->getPosition().x() - 1 > -1 && cell->getPosition().y() - 1 > -1)
					{
						cellsGraph[cell].append(cells[cell->getPosition().y() - 1][cell->getPosition().x() - 1]);

					}
					break;
				}
				// top
				case 2:
				{
					if (cell->getPosition().y() - 1 > -1)
					{
						cellsGraph[cell].append(cells[cell->getPosition().y() - 1][cell->getPosition().x()]);

					}
					break;
				}
				// top right
				case 3:
				{
					if (cell->getPosition().x() + 1 < 13 && cell->getPosition().y() - 1 > -1)
					{
						cellsGraph[cell].append(cells[cell->getPosition().y() - 1][cell->getPosition().x() + 1]);

					}
					break;
				}
				// right
				case 4:
				{
					if (cell->getPosition().x() + 1 < 13)
					{
						cellsGraph[cell].append(cells[cell->getPosition().y()][cell->getPosition().x() + 1]);

					}
					break;
				}
				// bottom right
				case 5:
				{
					if (cell->getPosition().x() + 1 < 13 && cell->getPosition().y() + 1 < 8)
					{
						cellsGraph[cell].append(cells[cell->getPosition().y() + 1][cell->getPosition().x() + 1]);

					}
					break;
				}
				// bottom
				case 6:
				{
					if (cell->getPosition().y() + 1 < 8)
					{
						cellsGraph[cell].append(cells[cell->getPosition().y() + 1][cell->getPosition().x()]);

					}
					break;
				}
				// bottom left
				case 7:
				{
					if (cell->getPosition().x() - 1 > -1 && cell->getPosition().y() + 1 < 8)
					{
						cellsGraph[cell].append(cells[cell->getPosition().y() + 1][cell->getPosition().x() - 1]);
					}
					break;
				}
				}
			}
		}
	}
}

FindRouteAlgo::~FindRouteAlgo()
{
}

DekstraRouteAlgo::DekstraRouteAlgoCell::DekstraRouteAlgoCell(Cell* cell_ptr, double prior) : cell_ptr(cell_ptr), prior(prior)
{
}

DekstraRouteAlgo::DekstraRouteAlgoCell::DekstraRouteAlgoCell() : cell_ptr(nullptr), prior(0)
{
}

bool DekstraRouteAlgo::DekstraRouteAlgoCell::operator<(const DekstraRouteAlgoCell& right) const
{
	return prior > right.prior;
}
