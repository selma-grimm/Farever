#include "Delegates/RootTable.h"
#include "RootPanel.h"

RootPanel* RootPanel::m_pRootBrowsePanel = NULL;

RootPanel::RootPanel(STATE state, QWidget *parent)
	:AbstractPanel(state, parent)
    , m_pTable(new RootTable(this))
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_pTable);
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);

    m_model.setFilter(QDir::AllEntries | QDir::NoDot /*| QDir::Dirs | QDir::Files*/);
    m_pTable->setModel(&m_model);

	QVariant root = m_model.myComputer();
	QModelIndex rootIndex = m_model.setRootPath(root.toString());

    m_pTable->setRootIndex(rootIndex);
    connect(m_pTable,
            SIGNAL(goToDisk(QString)),
            SLOT(goToDisk(QString)));
    m_pTable->hideColumn(1);
    m_pTable->hideColumn(2);
    m_pTable->hideColumn(3);    

    QRect dr = QApplication::desktop()->screenGeometry();
    int w = dr.width()*0.1;
    int h = dr.height()*0.6;
    m_posY = dr.height()*0.1;
    m_rightPosX = dr.width()-w;
    setFixedSize(w,h);

    m_pTable->setColumnWidth(0,width());
    hide();

}

RootPanel* RootPanel::getInst(STATE state, QWidget *parent)
{
    if (!m_pRootBrowsePanel)
        m_pRootBrowsePanel = new RootPanel(state, parent);

    return m_pRootBrowsePanel;
}

void RootPanel::freeInst()
{
    delete m_pRootBrowsePanel;
}

void RootPanel::showA(STATE s)
{
    if (s == LEFT)
        move(0, m_posY);
    else
        move(m_rightPosX, m_posY);

    state(s);
    show();
    raise();   

    QItemSelectionModel* pSelModel = m_pTable->selectionModel();
    QModelIndex firstIndex = m_model.index(0,0);
    pSelModel->clearSelection();
    pSelModel->select(firstIndex, QItemSelectionModel::Select);
    m_pTable->setCurrentIndex(firstIndex);
    m_pTable->setFocus(Qt::MouseFocusReason);

}

void RootPanel::hideA()
{
    hide();    
}

void RootPanel::goToDisk(const QString& sPath)
{
    hideA();
    emit goToDisk(sPath, state());
}

void RootPanel::keyPressEvent(QKeyEvent* event)
{
    QWidget::keyPressEvent(event);
    if (event->key() == Qt::Key_Escape)
        hideA();
}

//RootTable::RootTable(QWidget *parent) :
//    QTableView(parent)
//{
//    //resizeColumnsToContents();
//    setSelectionBehavior(QAbstractItemView::SelectRows);
//    setSelectionMode(QAbstractItemView::ExtendedSelection);
//    verticalHeader()->hide();
//    horizontalHeader()->hide();
//}

//void RootTable::keyPressEvent(QKeyEvent* event)
//{
//    QAbstractItemView::keyPressEvent(event);
//    if ((event->key() == Qt::Key_Enter) || (event->key() == 16777220))
//    {
//        QFileSystemModel* pFS = qobject_cast<QFileSystemModel*>(model());
//        emit goToDisk(pFS->filePath(currentIndex()));
//    }

////    else if ((event->key() == Qt::Key_Tab) || (event->key() == Qt::Key_Backtab))
////        event->ignore();
////    else


//}

////void RootTable::goToPath(const QString& sPath)
////{
////    QFileSystemModel* pFS = qobject_cast<QFileSystemModel*>(model());
////    QModelIndex rootIndex = pFS->setRootPath(sPath);
////    setRootIndex(rootIndex);

//////    selectRow(0);
////    viewport()->update();

////}
