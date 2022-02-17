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

public slots:
    void generateAction(bool b);

    void findPathAction(bool b);

    void chooseAlgAAction(bool b);

    void chooseAlgDeckstraAction(bool b);

private:

    int cur_algo = 0;

    Ui::DekstraClass ui;

    QGraphicsScene* field = nullptr;
    QList<QList<Cell*>> cells;

    void createFiled();
    void initField();

    void createCells();

    void drawMarkup();
};
