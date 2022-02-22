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
		considerNearPoints(consideredPoint);
		consideredPoint++;
	}
	else
	{
		cellsGraph[cur_point].last()->setStatus(Cell::Status::Inactive);
		consideredPoint = 0;
		cur_point->setStatus(Cell::Status::Inactive);
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

void AStartRouteAlgo::considerNearPoints(int i)
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

			cur_cell->setCurrentRoute(cur_point->getCurrentRoute() + calcRouteToCell(cur_cell, cur_point));

			cur_cell->setWeight(cur_cell->getManhattanDistance() + cur_cell->getCurrentRoute());

			cur_cell->update();

		}
		else
		{
			if (cur_point->getCurrentRoute() + calcRouteToCell(cur_point, cur_cell) < cur_cell->getCurrentRoute())
			{
				cur_cell->setParentCell(cur_point);
				cur_cell->setDirection(findDirection(cur_point, cur_cell));
				cur_cell->setCurrentRoute(cur_point->getCurrentRoute() + calcRouteToCell(cur_cell, cur_point));

				cur_cell->setWeight(cur_cell->getManhattanDistance() + cur_cell->getCurrentRoute());
				cur_cell->update();
			}
		}
	}
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

int AStartRouteAlgo::calcRouteToCell(const Cell* start, const Cell* end)
{
	int dist = 0;
	auto tp = start->getType();

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
}

void DekstraRouteAlgo::findRoute()
{

}

bool DekstraRouteAlgo::isFinished()
{
	return false;
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


