#include "../../Precompile.h"
#include "../../Colors.h"
#include "CustomHeader.h"

CustomHeader::CustomHeader(QAbstractItemModel *pModel, QWidget *parent) :
	QHeaderView(Qt::Horizontal, parent)
      , m_pModel(pModel)
{
    setFixedHeight(26);

    grad = QLinearGradient(0., 0., 0., 1.);
    grad.setCoordinateMode(QGradient::StretchToDeviceMode);

    grad.setColorAt(0., QColor(DARKEST));
    grad.setColorAt(0.5, QColor(GREY_DARK));
    grad.setColorAt(1.0, QColor(DARKEST));
}

QSize CustomHeader::sizeHint() const
{
    return QHeaderView::sizeHint().expandedTo(size());
}

void CustomHeader::paintEvent(QPaintEvent*)
{
	using namespace Colors;
	QPainter painter(viewport());
	painter.setPen(FONT_BRIGHT);
    painter.fillRect(rect(), QColor(DARKEST));

	int x = 0;
	for (int i = 0; i < count(); i++)
	{
		QPainterPath path;
        int ss;
        if (i == count()-1)
            ss = sectionSize(i);
        else
            ss = sectionSize(i) - 2;
        QRect sectionRect(x, 2, ss, height() - 4);
        path.addRect(sectionRect/*, 3, 3*/);
        painter.fillPath(path, grad /*QColor(GREY_DARK)*/);
		x += sectionSize(i);

		Q_ASSERT(m_pModel);
		QString sectionText(m_pModel->headerData(i, orientation()).toString());
		painter.drawText(sectionRect, sectionText, Qt::AlignHCenter | Qt::AlignVCenter);
	}
}
