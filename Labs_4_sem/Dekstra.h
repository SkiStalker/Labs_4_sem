#pragma once


#include "INCLUDES.h"
#include "Cell.h"
#include "ui_Dekstra.h"


class Dekstra : public QMainWindow
{
    Q_OBJECT

public:
    Dekstra(QWidget *parent = Q_NULLPTR);
    ~Dekstra();

private:
    Ui::DekstraClass ui;
    QGraphicsScene* field = nullptr;
    QList<Cell*> cells;
    void drawFiled();
    void initField();
};
