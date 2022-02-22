#pragma once
#include "INCLUDES.h"
#include <exception>

class Cell :
    public QGraphicsRectItem
{
public:
    Cell(QPoint _pos);
    enum class Type
    {
        Wall,
        Asphalt,
        Grass,
        Sand,
        Water
    };

    enum class Status
    {
        Inactive,
        Active,
        Processed,
        Passed
    };

    enum class RouteStat
    {
        NotRoute,
        Start,
        Finish
    };

    enum class Direction
    {
        NotDirected,
        Left,
        TopLeft,
        Top,
        TopRight,
        Right,
        BottomRight,
        Bottom,
        BottomLeft
    };

    static int sz;

    void setType(const Type& tp);
    Type getType() const;

    void setStatus(const Status& st);

    Status getStatus() const;

    void setRouteStat(const RouteStat& r_st);

    RouteStat getRouteStat() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void setDirection(Direction consider);

    Direction getDirection() const;

    const QPoint& getPosition() const;

    void setClosed(bool closed);

    bool getClosed() const;

    void setManhattanDistance(int dist);

    int getManhattanDistance() const;

    void setCurrentRoute(int route);

    int getCurrentRoute() const;

    void setWeight(int weight);

    int getWeight() const;

    Cell* getParentCell() const;

    void setParentCell(Cell* parent_cell);

private:
    bool in_route = false;
    Cell* parent_cell = nullptr;
    int manhattan_distance = 0;
    int cur_route = 0;
    int cell_weight = 0;

    bool closed = false;
    QPoint _position;
    Type tp = Type::Asphalt;
    Status status = Status::Inactive;
    RouteStat route_stat = RouteStat::NotRoute;
    Direction direction = Direction::NotDirected;
};

