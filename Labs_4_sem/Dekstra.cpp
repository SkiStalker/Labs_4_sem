#include "Dekstra.h"

Dekstra::Dekstra(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initField();
	createFiled();
}

Dekstra::~Dekstra()
{
}

void Dekstra::pressgenMapButton()
{
}

void Dekstra::presssetStartPointButton()
{
	if (ui.setEndPointButton->isChecked())
		ui.setEndPointButton->setChecked(false);
}

void Dekstra::presssetEndPointButton()
{
	if (ui.setStartPointButton->isChecked())
		ui.setStartPointButton->setChecked(false);
}

void Dekstra::pressfindRouteButton()
{
	FindRouteAlgo::Algorithm alg_type;
	if (!ui.comboBox->currentIndex())
	{
		alg_type = FindRouteAlgo::Algorithm::AStart;
	}
	else
	{
		alg_type = FindRouteAlgo::Algorithm::Dekstra;
	}
	field->startFindingRoute(alg_type);
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


	connect(ui.findRouteButton, &QPushButton::pressed, this, &Dekstra::pressfindRouteButton);
	connect(ui.genMapButton, &QPushButton::pressed, this, &Dekstra::pressgenMapButton);
	connect(ui.setStartPointButton, &QPushButton::pressed, this, &Dekstra::presssetStartPointButton);
	connect(ui.setEndPointButton, &QPushButton::pressed, this, &Dekstra::presssetEndPointButton);
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
			field->cells[i].append(c);
			field->addItem(c);
		}
	}
	
	field->setStartPoint(field->cells[4][2]);
	field->setEndPoint(field->cells[4][w_cells - 2]);

	field->cells[4][8]->setType(Cell::Type::Wall);
}

void Dekstra::drawMarkup()
{
	for (int i = 0; i < w_cells; i++)
	{
		QGraphicsTextItem* txth = new QGraphicsTextItem(QString::number(i));
		field->addItem(txth);
		txth->setPos(QPoint(15 + i*Cell::sz + Cell::sz / 2, -4));
		if (i < h_cells)
		{
			QGraphicsTextItem* txtv = new QGraphicsTextItem(QString::number(i));
			field->addItem(txtv);
			txtv->setPos(QPoint(0, 10 + i * Cell::sz + Cell::sz / 2));
		}
	}

}