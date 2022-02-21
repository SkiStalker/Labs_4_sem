#pragma once


#include "INCLUDES.h"
#include "ui_Dekstra.h"
#include "RouteField.h"

class Dekstra : public QMainWindow
{
    Q_OBJECT

public:
    Dekstra(QWidget *parent = Q_NULLPTR);
    ~Dekstra();

public slots:
    void pressfindRouteButton();
    void pressgenMapButton();
    void presssetStartPointButton();
    void presssetEndPointButton();




private:
    int h_cells = 8;
    int w_cells = 13;
    Cell* startCell = nullptr;

    Cell* finishCell = nullptr;
    Ui::DekstraClass ui;

    RouteField* field = nullptr;

    void createFiled();
    void initField();

    void createCells();

    void drawMarkup();
};
