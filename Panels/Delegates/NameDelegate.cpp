#include "../../Precompile.h"

#include "NameDelegate.h"

NameDelegate::NameDelegate(QObject *parent) :
    ViewDelegate(parent)
      , m_bEditing(false)
{
	//qDebug() << "Item Delegate ctor";
}

QWidget* NameDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
//	qDebug() << Q_FUNC_INFO;
	NameEditor* m_pEditor = new NameEditor(parent);
	connect(m_pEditor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
	return m_pEditor;
}

void NameDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	//qDebug() << Q_FUNC_INFO;
	m_bEditing = true;
	QString sData = index.data().toString();
	QLineEdit* pEditor = qobject_cast<QLineEdit*>(editor);
	pEditor->setText(sData);
}

void NameDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	//qDebug() << Q_FUNC_INFO;
	QLineEdit* pEditor = qobject_cast<QLineEdit*>(editor);
	model->setData(index, QVariant::fromValue(pEditor->text()));
}

void NameDelegate::commitAndCloseEditor()
{
	//qDebug() << Q_FUNC_INFO;
	QLineEdit* pEditor = qobject_cast<QLineEdit*>(sender());
	emit commitData(pEditor);
	emit closeEditor(pEditor);
	emit delegateEditingFinished();
	m_bEditing = false;
}

void NameDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}


//bool NameDelegate::eventFilter(QObject *object, QEvent *event)
//{
//	QLineEdit* lineEdit = qobject_cast<QLineEdit*>(object);
//	QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);
//	if ((lineEdit) && (keyEvent))
//	{
//		// do not propagate Enter to cell
//		if ((keyEvent->key() == Qt::Key_Enter) || (keyEvent->key() == 16777220))
//			return true;

//	}
//	return QStyledItemDelegate::eventFilter(object, event);
//}


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void NameEditor::keyPressEvent(QKeyEvent* event)
{
	QLineEdit::keyPressEvent(event);
	if ((event->key() == Qt::Key_Enter) || (event->key() == 16777220))
	{
		event->accept();
		//qDebug() << "ho ho ho1";
	}
}








