#include "../../Colors.h"
#include "BrowseModel.h"

#include "ViewDelegate.h"

ViewDelegate::ViewDelegate(QObject *parent) :
    QStyledItemDelegate(parent)  
{


}

void ViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QRect rect = option.rect;

        painter->setPen(QColor(Qt::black));

        if (option.state & QStyle::State_Selected)
        {
            painter->fillRect(rect, QBrush(QColor(SELECTION)));
        }
//        else if (option.state & QStyle::State_MouseOver)
//        {
//            painter->fillRect(rect, QBrush(Qt::green));
//        }
//        else if ((m_pItem != NULL) && (index.internalPointer() == m_pItem))
//        {
//            painter->fillRect(rect, QBrush(QColor("#0288c0")));
//            painter->setPen(QColor(Qt::white));
//        }
        else
        {
            const BrowseModel* model = static_cast<const BrowseModel*>(index.model());
            Q_ASSERT(model);
            if (model->isActiveIndex(index.parent()))
               painter->fillRect(rect, GREY_LIGHT);
            else
                painter->fillRect(rect, GREY_DARK);
            //painter->fillRect(rect, ((index.row() % 2) == 1) ? QColor(242, 245, 249) : QColor(Qt::white));
        }

   //     rect.adjust(7, 0, 2, 0);

        QTextOption textOption(option.displayAlignment);
        textOption.setTextDirection(option.direction);
        textOption.setWrapMode(QTextOption::NoWrap);

        painter->drawText(rect, index.data(Qt::DisplayRole).toString(), textOption);

        return;
    }

    QStyledItemDelegate::paint(painter, option, index);
}

