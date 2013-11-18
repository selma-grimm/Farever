#include "../Precompile.h"

#include "Delegates/BrowseModel.h"
#include "Delegates/NameDelegate.h"
#include "Delegates/ViewDelegate.h"
#include "Delegates/CustomHeader.h"
#include "BrowsePanel.h"

BrowsePanel::BrowsePanel(STATE state, QWidget *parent):
    AbstractPanel(state, parent)
    , m_pTable(new BrowseTable(this))    
{
	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(m_pTable);
	mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);

	m_pModel = new BrowseModel(this);
	m_pTable->setModel(m_pModel);
	CustomHeader* header = new CustomHeader(m_pModel, m_pTable);
	m_pTable->setHeader(header);

    NameDelegate* nameDelegate = new NameDelegate();
    m_pTable->setItemDelegateForColumn(0, nameDelegate);
    m_pTable->setItemDelegateForColumn(1, new ViewDelegate());
    m_pTable->setItemDelegateForColumn(2, new ViewDelegate());
    m_pTable->setItemDelegateForColumn(3, new ViewDelegate());

	connect(nameDelegate,
		SIGNAL(delegateEditingFinished()),
		m_pTable,
		SLOT(restorEditedSelection()));

	connect(m_pModel,
		SIGNAL(rowsRemoved(QModelIndex, int, int)),
		m_pTable,
		SLOT(rowsRemoved(QModelIndex, int, int)));

	setFocusPolicy(Qt::TabFocus);
	setFocusProxy(m_pTable);

    m_pTable->goToPath(QDir::rootPath());
}

BrowsePanel::~BrowsePanel()
{
    delete m_pTable;
    m_pTable = NULL;
    delete m_pModel;
    m_pModel = NULL;
}

void BrowsePanel::goToDisk(const QString& sPath, STATE s)
{
    if (s == state())
    {
        m_pTable->goToDisk(sPath);
        m_pTable->setFocus();
    }
}

void BrowsePanel::keyPressEvent(QKeyEvent* event)
{
	QWidget::keyPressEvent(event);

	switch (event->key())
	{
	case Qt::Key_F5:
	{
		emit copy();
		break;
	}
	case Qt::Key_F6:
	{
		emit move();
		break;
	}
	case Qt::Key_F7:
	{
		emit createFolder();
		break;
	}
	case Qt::Key_F8:
	{
		emit remove();
		break;
	}
	}
}

QPair<bool, QString> BrowsePanel::getAbsPath(const QModelIndex& index)
{
    QPair<bool, QString> result;
    QFileInfo fi = m_pModel->fileInfo(index);

    if (fi.isDir())    
        result.first = true;
    else
        result.first = false;       
    result.second = fi.absoluteFilePath();

    return result;
}

QString	BrowsePanel::getSelectedPath()
{
	QModelIndexList indexList = m_pTable->selectedIndexes();
	if (!indexList.isEmpty())
		return m_pModel->filePath(indexList.first());
	else
		return m_pModel->rootPath();
}

QString	BrowsePanel::getCurrentPath()
{
	QModelIndexList indexList = m_pTable->selectedIndexes();
	if (!indexList.isEmpty())
	{
		QString sCurrentPath = m_pModel->filePath(indexList.first());

		if (sCurrentPath.contains(QRegExp("(/|\\\\)\\.$")))
		{
			// if "dot" dir was selected, not need to cd up
			sCurrentPath.remove(QRegExp("(/|\\\\)\\.$"));
		}
		else
		{
			QDir dir(sCurrentPath);
			dir.cdUp();
			sCurrentPath = dir.absolutePath();
		}

		return sCurrentPath;
	}
	else
		return m_pModel->rootPath();
}






















