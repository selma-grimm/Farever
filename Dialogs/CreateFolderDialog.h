#ifndef CREATEFOLDERDIALOG_H
#define CREATEFOLDERDIALOG_H

#include <QFrame>

class QPushButton;
class QLineEdit;
class QLabel;

class CreateFolderDialog : public QFrame
{
    Q_OBJECT

	QLineEdit* m_pNameEdit;
	QLabel* m_pLabel;
	QString m_sCurrentPath;


//    QPushButton* m_pOkBut;
//    QPushButton* m_pCancelBut;

public:
    explicit CreateFolderDialog(QWidget *parent = 0);
	void showDialog(const QString& sPath);

protected:
	void keyPressEvent(QKeyEvent* event);
	void showEvent(QShowEvent * event);
    
signals:	
	void Close();


private slots:
    void createFolder();


};

// оставлю себе на память
//struct GetDirNumber: std::unary_function<QString, int>
//{
//	int operator()(const QString& sDir)
//	{
//		QRegExp rxEndDigit("(\\d)+$");
//		if ((sDir.indexOf(rxEndDigit) != -1) && (rxEndDigit.captureCount() == 1))
//			return rxEndDigit.cap(1).toInt();
//		else
//			return 0;
//	}
//};

//struct sortFolderNumbers: public std::binary_function<QString, QString, bool>
//{
//	bool operator()(const QString& ls, const QString& rs)
//	{
//		QRegExp rxEndDigit("(\\d)+$");
//		int ln, rn;
//		if (ls.indexOf(rxEndDigit) != -1)
//			ln = rxEndDigit.cap(1).toInt();
//		if (rs.indexOf(rxEndDigit) != -1)
//			rn = rxEndDigit.cap(1).toInt();

//		return ln < rn;
//	}
//};

#endif // CREATEFOLDERDIALOG_H
