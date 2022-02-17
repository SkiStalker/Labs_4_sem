#pragma once
#include "INCLUDES.h"
#include <exception>

class Cell :
    public QGraphicsRectItem
{
public:
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
        Processed
    };

    enum class RouteStat
    {
        NotRoute,
        Start,
        Finish
    };

    static int sz;

    void setType(const Type& tp);
    Type getType() const;

    void setStatus(const Status& st);

    Status getStatus() const;

    void setRouteStat(const RouteStat& r_st);

    RouteStat getRouteStat() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
private:
    bool is_passed = false;
    Type tp = Type::Asphalt;
    Status status = Status::Inactive;
    RouteStat route_stat = RouteStat::NotRoute;
};

