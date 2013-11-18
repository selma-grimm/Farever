#ifndef VIEWDELEGATE_H
#define VIEWDELEGATE_H

#include <QStyledItemDelegate>

class ViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ViewDelegate(QObject *parent = 0);

    virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    
signals:
    
public slots:

private:

    
};

#endif // VIEWDELEGATE_H
