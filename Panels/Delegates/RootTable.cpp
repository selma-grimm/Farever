#include "RootTable.h"

RootTable::RootTable(QWidget *parent) :
	QTableView(parent)
{
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	verticalHeader()->hide();
	horizontalHeader()->hide();
}

void RootTable::keyPressEvent(QKeyEvent* event)
{
	QAbstractItemView::keyPressEvent(event);
	if ((event->key() == Qt::Key_Enter) || (event->key() == 16777220))
	{
		QFileSystemModel* pFS = qobject_cast<QFileSystemModel*>(model());
		emit goToDisk(pFS->filePath(currentIndex()));
	}

//    else if ((event->key() == Qt::Key_Tab) || (event->key() == Qt::Key_Backtab))
//        event->ignore();
//    else


}
