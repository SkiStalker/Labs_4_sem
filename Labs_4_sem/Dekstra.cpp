#include "Dekstra.h"

Dekstra::Dekstra(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initField();
	drawFiled();
}

Dekstra::~Dekstra()
{
}

void Dekstra::drawFiled()
{
	for(int i = 0; i < field->sceneRect().height() / Cell::sz - 1; i++)
		for (int j = 0; j < field->sceneRect().width() / Cell::sz - 1; j++)
		{
			Cell* c = new Cell();
			c->setRect(QRect(1 + j * Cell::sz, 2 + i * Cell::sz, Cell::sz, Cell::sz));
			cells.append(c);
			field->addItem(c);
		}
	field->update();
}

void Dekstra::initField()
{
	field = new QGraphicsScene();
	field->setSceneRect(QRect(0, 0, ui.graphicsView->rect().width(), ui.graphicsView->rect().height()));
	
	ui.graphicsView->setScene(field);
}


