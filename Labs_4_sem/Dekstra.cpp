#include "Dekstra.h"

Dekstra::Dekstra(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initField();
	createFiled();
	srand(time(nullptr));
}

Dekstra::~Dekstra()
{
}

void Dekstra::pressGenMapButton()
{
	for(auto line: field->cells)
		for (auto cell : line)
		{
			int tp = rand() % 5;
			if (!tp && (cell->getRouteStat() == Cell::RouteStat::Start || cell->getRouteStat() == Cell::RouteStat::Finish))
				cell->setType(Cell::Type::Asphalt);
			else
				cell->setType((Cell::Type)tp);
		}
	field->update();
}

void Dekstra::pressSetStartPointButton()
{
	if (ui.setEndPointButton->isChecked())
		ui.setEndPointButton->setChecked(false);
}

void Dekstra::pressSetEndPointButton()
{
	if (ui.setStartPointButton->isChecked())
		ui.setStartPointButton->setChecked(false);
}

void Dekstra::pressClearMapButton()
{
	field->clearField();
	changeRunning(false);
	alg_type = FindRouteAlgo::Algorithm::None;
	field->update();
}

void Dekstra::pressPauseFindRouteButton()
{
	field->pauseFindingRoute();
}

void Dekstra::spinBoxChangingValue()
{
	pressFindRouteButton();
}

void Dekstra::changeRunning(bool stat)
{
	ui.comboBox->setEnabled(!stat);
	ui.setStartPointButton->setEnabled(!stat);
	ui.setEndPointButton->setEnabled(!stat);
	ui.genMapButton->setEnabled(!stat);
	ui.pauseFindRouteButton->setEnabled(stat);
}

void Dekstra::pressFindRouteButton()
{
	if (alg_type == FindRouteAlgo::Algorithm::None)
	{
		changeRunning(true);
		if (!ui.comboBox->currentIndex())
		{
			alg_type = FindRouteAlgo::Algorithm::AStart;
		}
		else
		{
			alg_type = FindRouteAlgo::Algorithm::Dekstra;
		}
	}
	field->startFindingRoute(alg_type, ui.spinBox->value());
}


void Dekstra::createFiled()
{
	createCells();

	drawMarkup();

	field->update();
}

void Dekstra::initField()
{
	field = new RouteField(&ui);
	field->setSceneRect(QRect(0, 0, ui.graphicsView->rect().width(), ui.graphicsView->rect().height()));

	ui.graphicsView->setScene(field);


	connect(ui.findRouteButton, &QPushButton::pressed, this, &Dekstra::pressFindRouteButton);
	connect(ui.genMapButton, &QPushButton::pressed, this, &Dekstra::pressGenMapButton);
	connect(ui.setStartPointButton, &QPushButton::pressed, this, &Dekstra::pressSetStartPointButton);
	connect(ui.setEndPointButton, &QPushButton::pressed, this, &Dekstra::pressSetEndPointButton);
	connect(ui.cleanMapButton, &QPushButton::pressed, this, &Dekstra::pressClearMapButton);
	connect(ui.pauseFindRouteButton, &QPushButton::pressed, this, &Dekstra::pressPauseFindRouteButton);
	connect(ui.spinBox, &QSpinBox::valueChanged, this, &Dekstra::spinBoxChangingValue);
}

void Dekstra::createCells()
{
	for (int i = 0; i < h_cells; i++)
	{
		field->cells.append(QList<Cell*>());
		for (int j = 0; j < w_cells; j++)
		{
			Cell* c = new Cell(QPoint(j, i));
			c->setRect(QRect(0, 0, Cell::sz, Cell::sz));
			c->setPos(15 + j * Cell::sz, 15 + i * Cell::sz);
			c->setType((Cell::Type)map1[i][j]);
			field->cells[i].append(c);
			field->addItem(c);
		}
	}

	field->setStartPoint(field->cells[4][2]);
	field->setEndPoint(field->cells[4][w_cells - 2]);
}

void Dekstra::drawMarkup()
{
	for (int i = 0; i < w_cells; i++)
	{
		QGraphicsTextItem* txth = new QGraphicsTextItem(QString::number(i));
		field->addItem(txth);
		txth->setPos(QPoint(15 + i * Cell::sz + Cell::sz / 2, -4));
		if (i < h_cells)
		{
			QGraphicsTextItem* txtv = new QGraphicsTextItem(QString::number(i));
			field->addItem(txtv);
			txtv->setPos(QPoint(0, 10 + i * Cell::sz + Cell::sz / 2));
		}
	}
}