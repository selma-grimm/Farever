#include "../../Precompile.h"
#include "NameDelegate.h"
#include "BrowseModel.h"
#include "../../Colors.h"
#include "BrowseTable.h"

BrowseTable::BrowseTable(QWidget *parent) :
    QTreeView(parent)
  , m_pFS(NULL)  
{
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setTabKeyNavigation(false);
    setUniformRowHeights(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);

   // setMouseTracking(true);
    connect(this, SIGNAL(expanded(QModelIndex)), this, SLOT(onExpanded(QModelIndex)));
    connect(this, SIGNAL(collapsed(QModelIndex)), this, SLOT(onCollapsed(QModelIndex)));

    setStyleSheet(QString(
                    "QTreeView {"
                        "show-decoration-selected: 1; "
                        "background-color: %1; "
                        "border: 1px solid %2;"
                        "border-bottom: 10px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 %1, stop:1 %2); "
//                        "border-left: 5px solid qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 %1, stop:1 %2); "
//                        "border-right: 5px solid qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 %1, stop:1 %2); "
                    "}"

                    ).arg(GREY_DARK)
                     .arg(DARKEST));
}

void BrowseTable::keyPressEvent(QKeyEvent* event)
{
	//qDebug() << Q_FUNC_INFO;
	switch (event->key())
	{
	case Qt::Key_Enter:
	case 16777220:			// right enter
	{
		NameDelegate* delegate = dynamic_cast<NameDelegate*>(itemDelegateForColumn(0));

		//if ()

		if  ((delegate) && (!delegate->isEditing()))
			goToPath(m_pFS->filePath(currentIndex()));
		//else
		QTreeView::keyPressEvent(event);

		break;
	}
	case Qt::Key_Tab:
	case Qt::Key_Backtab:
	case Qt::Key_F5:
	{
		event->ignore();
		break;
	}
	case Qt::Key_F2:
	{
		m_editingIndex = currentIndex();
		QTreeView::keyPressEvent(event);
	}
	default:
		QTreeView::keyPressEvent(event);
	}
}

void BrowseTable::goToPath(const QString& sPath)
{   
	QModelIndex index = m_pFS->index(sPath);
	QFileInfo fi = m_pFS->fileInfo(index);
	if (fi.isDir())    	// expand or collapse dir
	{
		if (isExpanded(index))
		{
			collapse(index);
		}
		else
		{
			expand(index);
		}
	}
	else	//this is a file, run it
    {
		QString sRunPath = sPath;
		sRunPath.replace(QRegExp("/+"), QDir::separator());
		//FIXME: platform dependent!
		sRunPath = QString("explorer.exe \"%1\"").arg(sRunPath);

		QProcess* proc = new QProcess(this);
		proc->start(sRunPath);
	}

	viewport()->update();
}

void BrowseTable::selectFirst(const QString& sPath)
{
//	qDebug() << "select first";

//TODO: fix workaround
	QDir dir(sPath);

//NOTE: here must be used current (chosed or default) sort order global
	QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot,
										   QDir::Name | QDir::IgnoreCase | QDir::DirsFirst);

//	QStringList list2 = dir.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot,
//										   QDir::Name | QDir::IgnoreCase | QDir::DirsFirst);
	if (list.empty())
		return;

	QModelIndex firstIndex = m_pFS->index(list.first().absoluteFilePath());
	setCurrentIndex(firstIndex);

// this is not working!
//    QModelIndex rootIndex = m_pFS->index(newPath, 0);
//	QItemSelectionModel* pSelModel = selectionModel();
//    QModelIndex firstIndex = m_pFS->index(0,0, rootIndex);
//    setCurrentIndex(firstIndex);
//	pSelModel->select(firstIndex, QItemSelectionModel::Rows);
}

void BrowseTable::restorEditedSelection()
{
	QString s = m_pFS->fileName(m_editingIndex);
    setCurrentIndex(m_editingIndex);
}

void BrowseTable::onExpanded(const QModelIndex & index)
{
    QFileInfo fi = m_pFS->fileInfo(index);
    if (fi.isDir())
    {
        if (!m_expandStack.isEmpty())
        {
            QModelIndex& lastExpanded = m_expandStack.top();
            while (index.parent() != lastExpanded)
            {
                collapse(lastExpanded);
                if (m_expandStack.isEmpty())
                    break;
                lastExpanded = m_expandStack.top();
            }
        }

        m_pFS->setActiveIndex(index);
        selectFirst(m_pFS->filePath(index));
        m_expandStack.push(index);
    }
}

void BrowseTable::onCollapsed(const QModelIndex &index)
{
    setCurrentIndex(index);
    m_pFS->setActiveIndex(index.parent());
    m_expandStack.pop();
}

void BrowseTable::setModel(QAbstractItemModel* pModel)
{
    m_pFS = qobject_cast<BrowseModel*>(pModel);
    QTreeView::setModel(m_pFS);
    m_pFS->setView(this);

    m_pFS->setRootPath(QDir::rootPath());
}

void BrowseTable::resizeEvent(QResizeEvent * event)
{
    QTreeView::resizeEvent(event);
	int w1 = event->size().width()*0.4;
	int w2 = event->size().width()*0.2;

	setColumnWidth(0, w1);
	setColumnWidth(1, w2);
	setColumnWidth(2, w2);
	setColumnWidth(3, w2);


}

QModelIndexList BrowseTable::selectedIndexes()
{
    QModelIndexList filesList = QTreeView::selectedIndexes();
    QModelIndexList filteredList;
    foreach (const QModelIndex& index, filesList)
    {
        if (index.column() == 0)
            filteredList << index;
    }

    return filteredList;
}

void BrowseTable::setHeader(QHeaderView *header)
{
    QTreeView::setHeader(header);
    updateGeometries();
}

void BrowseTable::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
  //  painter->setBrush(QColor(GREY_DARK));
    const BrowseModel* model = static_cast<const BrowseModel*>(index.model());
    Q_ASSERT(model);
    if (index == model->view()->currentIndex())
        painter->fillRect(rect, QBrush(QColor(SELECTION)));
    else if (model->isActiveIndex(index.parent()))
        painter->fillRect(rect, QBrush(QColor(GREY_LIGHT)));
    else
        painter->fillRect(rect, QBrush(QColor(GREY_DARK)));
}

void BrowseTable::goToDisk(const QString& sPath)
{
    QModelIndex rootIndex = m_pFS->setRootPath(sPath);
	setRootIndex(rootIndex);
	selectFirst(sPath);
}

























