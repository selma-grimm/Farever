#ifndef NAMEDELEGATE_H
#define NAMEDELEGATE_H

#include "ViewDelegate.h"
#include <QObject>
//#include <QStyledItemDelegate>


class NameDelegate : public ViewDelegate
{
	Q_OBJECT

	mutable bool m_bEditing;
public:
	explicit NameDelegate(QObject *parent = 0);
	
	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;
	void	setEditorData(QWidget *editor, const QModelIndex &index) const;
	void	setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void	updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const;		

	bool	isEditing() { return m_bEditing; }

//protected
//	bool eventFilter(QObject* object, QEvent* event);

private slots:
	void commitAndCloseEditor();

signals:
	void delegateEditingFinished();	
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The NameEditor class
/////////////////////////////////////////////////////////////////////////////////////////

class NameEditor: public QLineEdit
{
	Q_OBJECT
public:
	NameEditor(QWidget *parent = 0): QLineEdit(parent) {}

protected:
	void keyPressEvent(QKeyEvent* event);

};

#endif // NAMEDELEGATE_H
