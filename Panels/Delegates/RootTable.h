#ifndef ROOTTABLE_H
#define ROOTTABLE_H

#include <QTableView>

class RootTable : public QTableView
{
	Q_OBJECT
public:
	explicit RootTable(QWidget *parent = 0);
	
protected:
	void keyPressEvent(QKeyEvent* event);

signals:
	void goToDisk(const QString& sPath);
	
};

#endif // ROOTTABLE_H
