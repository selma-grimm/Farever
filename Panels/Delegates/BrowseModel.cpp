#include "../../Utils.h"
#include "BrowseModel.h"

BrowseModel::BrowseModel(QObject *parent) :
    QFileSystemModel(parent)
{
    setReadOnly(false);
    setFilter(QDir::AllDirs | QDir::AllEntries | QDir::NoDotDot);
}

bool BrowseModel::setData(const QModelIndex & idx, const QVariant & value, int role)
{
    QString sNewName = filePath(idx);
    if (Utils::getAfterLastSlash(sNewName) == ".")
        return false;

    Utils::cutAfterLastSlash(sNewName);
    sNewName += QDir::separator() + value.toString();

    if (!index(sNewName).isValid())
        return QFileSystemModel::setData(idx, value, role);
    else
        return false;
}

bool BrowseModel::isActiveIndex(const QModelIndex &idx) const
{
    return (m_activeIndex.isValid() && (idx == m_activeIndex));
}

void BrowseModel::setActiveIndex(const QModelIndex &idx)
{
    m_activeIndex = idx;
}

BrowseTable *BrowseModel::view() const
{
    return m_pView;
}

void BrowseModel::setView(BrowseTable *pView)
{
    m_pView = pView;
}



