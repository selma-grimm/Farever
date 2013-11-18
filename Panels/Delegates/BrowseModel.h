#ifndef BROWSEMODEL_H
#define BROWSEMODEL_H

#include <QFileSystemModel>

class BrowseTable;

class BrowseModel : public QFileSystemModel
{
	Q_OBJECT
public:
	explicit BrowseModel(QObject *parent = 0);
	bool setData(const QModelIndex & idx, const QVariant & value, int role = Qt::EditRole);
    bool isActiveIndex(const QModelIndex & idx) const;
    void setActiveIndex(const QModelIndex & idx);
	
    BrowseTable *view() const;
    void setView(BrowseTable *view);

signals:

public slots:

private:
    QModelIndex m_activeIndex;
    BrowseTable* m_pView;
};

#endif // BROWSEMODEL_H
