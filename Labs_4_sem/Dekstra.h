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
    void pressFindRouteButton();
    void pressGenMapButton();
    void pressSetStartPointButton();
    void pressSetEndPointButton();
    void pressClearMapButton();
    void pressPauseFindRouteButton();

    void spinBoxChangingValue();




private:
    QList<QList<int>> map1 = { {1,1,3,3,3,1,1,1,1,1,1,1,1},
                    {1,1,3,3,3,1,1,1,2,2,1,1,1},
                    {1,1,1,1,1,1,1,0,1,1,1,1,1},
                    {1,1,1,1,1,1,1,0,1,1,1,1,1},
                    {1,1,1,1,1,1,1,0,1,1,1,1,1},
                    {1,2,2,1,1,1,1,0,1,1,3,3,1},
                    {1,1,1,1,3,4,1,1,1,2,1,1,1},
                    {1,1,1,1,3,4,1,1,1,2,1,1,1}
    };
    void changeRunning(bool stat);

    FindRouteAlgo::Algorithm alg_type = FindRouteAlgo::Algorithm::None;
    int h_cells = 8;
    int w_cells = 13;
    Cell* startCell = nullptr;

    Ui::DekstraClass ui;

    RouteField* field = nullptr;

    void createFiled();
    void initField();

    void createCells();

    void drawMarkup();
};
