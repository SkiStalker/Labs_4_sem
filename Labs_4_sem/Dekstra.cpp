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

void Dekstra::generateAction(bool b)
{
	qDebug() << "gen";
}

void Dekstra::findPathAction(bool b)
{
	qDebug() << "find";
}

void Dekstra::chooseAlgAAction(bool b)
{
	qDebug() << "choose A";
}

void Dekstra::chooseAlgDeckstraAction(bool b)
{
	qDebug() << "choose Dek";
}

void Dekstra::createFiled()
{
	createCells();

	drawMarkup();

	field->update();
}

void Dekstra::initField()
{
	field = new QGraphicsScene();
	field->setSceneRect(QRect(0, 0, ui.graphicsView->rect().width(), ui.graphicsView->rect().height()));
	
	ui.graphicsView->setScene(field);

	connect(ui.findpathAction, &QAction::triggered, this, &Dekstra::findPathAction);
	connect(ui.genAction, &QAction::triggered, this, &Dekstra::generateAction);
	connect(ui.actionA, &QAction::triggered, this, &Dekstra::chooseAlgAAction);
	connect(ui.actionDek, &QAction::triggered, this, &Dekstra::chooseAlgDeckstraAction);
}

void Dekstra::createCells()
{
	for (int i = 0; i < 10; i++)
	{
		cells.append(QList<Cell*>());
		for (int j = 0; j < 13; j++)
		{
			Cell* c = new Cell();
			c->setRect(QRect(0, 0, Cell::sz, Cell::sz));
			c->setPos(15 + j * Cell::sz, 15 + i * Cell::sz);
			cells[i].append(c);
			field->addItem(c);
		}
	}

	cells[4][2]->setRouteStat(Cell::RouteStat::Start);
	cells[4][10]->setRouteStat(Cell::RouteStat::Finish);
}

void Dekstra::drawMarkup()
{
	for (int i = 0; i < 13; i++)
	{
		QGraphicsTextItem* txth = new QGraphicsTextItem(QString::number(i));
		field->addItem(txth);
		txth->setPos(QPoint(15 + i*Cell::sz + Cell::sz / 2, -4));
		if (i < 10)
		{
			QGraphicsTextItem* txtv = new QGraphicsTextItem(QString::number(i));
			field->addItem(txtv);
			txtv->setPos(QPoint(0, 10 + i * Cell::sz + Cell::sz / 2));
		}
	}

}


