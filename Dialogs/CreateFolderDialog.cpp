#include "../Precompile.h"
#include "../Colors.h"

#include "CreateFolderDialog.h"

CreateFolderDialog::CreateFolderDialog(QWidget *parent) :
    QFrame(parent)
  , m_pNameEdit(new QLineEdit(this))
  , m_pLabel(new QLabel("Enter folder name:", this))
{
	setFixedHeight(100);

	QPushButton* pOkBut = new QPushButton("OK", this);
	QPushButton* pCancelBut = new QPushButton("Cancel", this);
	connect(pOkBut, SIGNAL(clicked()), SLOT(createFolder()));
	connect(pCancelBut, SIGNAL(clicked()), SIGNAL(Close()));
    pOkBut->setObjectName("ok_but");
    pCancelBut->setObjectName("cancel_but");
    pOkBut->setFixedSize(70, 26);
    pCancelBut->setFixedSize(70, 26);
    m_pLabel->setObjectName("question_label");

	pOkBut->setDefault(true);

	QGridLayout* pMainLayout = new QGridLayout(this);
	pMainLayout->addWidget(m_pLabel, 0, 0, 1, 2);
	pMainLayout->addWidget(m_pNameEdit, 1, 0, 1, 3);
	pMainLayout->addWidget(pOkBut, 2, 1);
	pMainLayout->addWidget(pCancelBut, 2, 2);

	QSpacerItem* pSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    pMainLayout->addItem(pSpacer, 2, 0);

}

void CreateFolderDialog::createFolder()
{
    if (!m_pNameEdit->text().isEmpty())
    {
        QDir dir(m_sCurrentPath);
        if (dir.exists(m_pNameEdit->text()))
            m_pLabel->setText("Folder with this name already exists within current location.");
        else if (dir.mkdir(m_pNameEdit->text()))
            emit Close();
        else
            m_pLabel->setText("Name is not valid. Creation failed.");
    }
}

void CreateFolderDialog::showEvent(QShowEvent * event)
{
	QFrame::showEvent(event);
	setFocus();
	m_pNameEdit->selectAll();
	m_pNameEdit->setFocus();
}

void CreateFolderDialog::keyPressEvent(QKeyEvent* event)
{
	QFrame::keyPressEvent(event);

	switch (event->key())
	{
	case Qt::Key_Enter:
	case 16777220:
		createFolder();
		break;
	case Qt::Key_Escape:
		emit Close();
		break;
	default:
		break;
	}
}

bool findMaxFolder(const QString& ls, const QString& rs)
{
	QRegExp rxEndDigit("(\\d+)$");
	int ln, rn;
	if (ls.indexOf(rxEndDigit) != -1)
		ln = rxEndDigit.cap(1).toInt();
	if (rs.indexOf(rxEndDigit) != -1)
		rn = rxEndDigit.cap(1).toInt();

    return ln > rn;
}


void CreateFolderDialog::showDialog(const QString& sPath)
{
	using namespace std;
	m_sCurrentPath = sPath;

//make serial numbers for suggested folder namesss
	QDir dir(m_sCurrentPath);
	QStringList filters;
	filters << "New folder*";
	QStringList names = dir.entryList(filters, QDir::Dirs | QDir::QDir::NoDotAndDotDot,  QDir::Name);
	if (names.isEmpty())
		m_pNameEdit->setText("New folder");
	else
	{
//TODO: use max algorithm
		std::partial_sort(names.begin(), names.begin()+1, names.end(), findMaxFolder);
		QString maxDir = names.first();

		QRegExp rxEndDigit("(\\d+)$");
		if ((maxDir.indexOf(rxEndDigit) != -1) && (rxEndDigit.captureCount() == 1))
		{
			int maxNumber = rxEndDigit.cap(1).toInt();
			m_pNameEdit->setText("New folder " + QString::number(++maxNumber));
		}
		else
			m_pNameEdit->setText("New folder 1");
	}
	show();
}






















