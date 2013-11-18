
#include "Dialogs/CreateFolderDialog.h"
#include "Dialogs/ConfirmDialog.h"
#include "Colors.h"
#include "ui_MainWindow.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_pRootPanel(RootPanel::getInst(LEFT, this))
{
	ui->setupUi(this);

	m_pPanel1 = new BrowsePanel(LEFT, this);
	m_pPanel2 = new BrowsePanel(RIGHT, this);

	m_pPanel1->setObjectName("panel1");
	m_pPanel2->setObjectName("panel2");

	ui->leftLayout->addWidget(m_pPanel1);
	ui->rightLayout->addWidget(m_pPanel2);

	m_pManager = new FileManager(dynamic_cast<BrowsePanel*>(m_pPanel1),
								 dynamic_cast<BrowsePanel*>(m_pPanel2));

	initPanel(m_pPanel1);
	initPanel(m_pPanel2);

    setWindowState(Qt::WindowMaximized);
  //  setFixedSize(1000, 600);

	QString bigStyleSheet = "QWidget#centralWidget"
	"{"
		"background-color: %1;"
	"}"
    "QLabel#f2HelpLabel, #f5HelpLabel, #f6HelpLabel, #f7HelpLabel, #f8HelpLabel, "
    "QPushButton#ok_but, #cancel_but"
	"{"
        "background-color: "
        "qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, "
        "stop:0 %1, stop:0.5 %2, stop:1 %1);"
        "color: %3;"
		"border: 0px solid transparent;"
	"}"
    "QLabel#question_label"
    "{"
        "color: white;"
    "}"
//    "QPushButton#ok_but, #cancel_but"
//    "{"
//        "background-color: "
//        "qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, "
//        "stop:0 %1, stop:0.5 %2, stop:1 %1);"
//        "color: %3;"
//        "border: 0px solid transparent;"
//    "}"
	;

	using namespace Colors;
	bigStyleSheet = bigStyleSheet.arg(DARKEST)
            .arg(GREY_DARK)
           // .arg(GREY_LIGHT)
			.arg(FONT_BRIGHT);



	setStyleSheet(bigStyleSheet);
}

void MainWindow::initPanel(AbstractPanel *panel)
{	
	connect(m_pRootPanel,
			SIGNAL(goToDisk(QString,STATE)),
			panel,
			SLOT(goToDisk(QString,STATE)));
	connect(panel,
			SIGNAL(copy()),
			m_pManager,
			SLOT(copy()));
//    connect(panel,
//            SIGNAL(remove()),
//            m_pManager,
//            SLOT(remove()));
    connect(panel,
            SIGNAL(remove()),
            SLOT(showRemoveDialog()));
	connect(panel,
			SIGNAL(move()),
			m_pManager,
			SLOT(move()));
    connect(panel,
            SIGNAL(createFolder()),            
			SLOT(showCFDialog()));


}

MainWindow::~MainWindow()
{
	delete ui;
	delete m_pManager;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    QWidget::keyPressEvent(event);

	switch (event->key())
	{
	case Qt::Key_F1:
	{
        if (event->modifiers() == Qt::AltModifier)
            m_pRootPanel->showA(LEFT);

        break;
	}
    case Qt::Key_F2:
    {
        if (event->modifiers() == Qt::AltModifier)        
            m_pRootPanel->showA(RIGHT);
        break;
    }
    default:
        break;

	}
}

void MainWindow::showCFDialog()
{
	CreateFolderDialog* pCFDialog = new CreateFolderDialog(this);

    m_pDialogCaller = static_cast<BrowsePanel*>(sender());
	if (m_pDialogCaller->state() == LEFT)
		ui->leftLayout->insertWidget(0, pCFDialog);
	else
		ui->rightLayout->insertWidget(0, pCFDialog);

	connect(pCFDialog,
			SIGNAL(Close()),
			SLOT(deleteDialog()));

    pCFDialog->showDialog(m_pDialogCaller->getCurrentPath());
}

void MainWindow::showRemoveDialog()
{
    ConfirmDialog* remove_dialog = new ConfirmDialog(this);

    m_pDialogCaller = static_cast<BrowsePanel*>(sender());
    if (m_pDialogCaller->state() == LEFT)
        ui->leftLayout->insertWidget(0, remove_dialog);
    else
        ui->rightLayout->insertWidget(0, remove_dialog);

    connect(remove_dialog,
            SIGNAL(close()),
            SLOT(deleteDialog()));
    connect(remove_dialog,
            SIGNAL(confirm()),
            SLOT(remove()));

    remove_dialog->showDialog("Are you shure you whant to remove this?");
}


void MainWindow::deleteDialog()
{
	delete sender();
	//TODO: fix workaround
	m_pDialogCaller->setFocus(Qt::MouseFocusReason);

}

void MainWindow::remove()
{
    m_pManager->remove(m_pDialogCaller);
}














