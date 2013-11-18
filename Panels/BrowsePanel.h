#ifndef BROWSEPANEL_H
#define BROWSEPANEL_H

#include <QTableView>
#include "Delegates/BrowseTable.h"
#include "AbstractPanel.h"

class BrowseModel;

class BrowsePanel : public AbstractPanel
{
	Q_OBJECT
public:
	explicit BrowsePanel(STATE state, QWidget *parent = 0);
	~BrowsePanel();

protected:
	BrowseTable* m_pTable;
	BrowseModel* m_pModel;

	void	keyPressEvent(QKeyEvent* event);    
signals:
	void copy();
	void remove();
	void move();
	void createFolder();

public:    
	QModelIndexList getSelectedIndexes()
	{
		return m_pTable->selectedIndexes();
	}

	QString	getSelectedPath();
	QString	getCurrentPath();

    // returns true if index is dir
	QPair<bool, QString> getAbsPath(const QModelIndex& index);
    
public slots:
	void goToDisk(const QString& sPath, STATE s);
};

#endif // BROWSEPANEL_H
