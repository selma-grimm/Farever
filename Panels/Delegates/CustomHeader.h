#ifndef CUSTOMHEADER_H
#define CUSTOMHEADER_H

#include <QHeaderView>

class CustomHeader : public QHeaderView
{
	Q_OBJECT
public:
	explicit CustomHeader(QAbstractItemModel* pModel, QWidget *parent = 0);
    QSize	sizeHint() const;
	
signals:
	
public slots:

protected:
	void paintEvent(QPaintEvent *);

private:
	QAbstractItemModel* m_pModel;
    QLinearGradient grad;
	
};

#endif // CUSTOMHEADER_H
