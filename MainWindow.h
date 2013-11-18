#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Precompile.h"

#include <QMainWindow>

#include "Panels/AbstractPanel.h"
#include "Panels/BrowsePanel.h"
#include "Panels/RootPanel.h"
#include "FileManager.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	void initPanel(AbstractPanel* panel);

    AbstractPanel* m_pPanel1;
    AbstractPanel* m_pPanel2;
	RootPanel* m_pRootPanel;
	FileManager* m_pManager;

	BrowsePanel* m_pDialogCaller;

private slots:
	void showCFDialog();
    void showRemoveDialog();
	void deleteDialog();

    void remove();

protected:
    void	keyPressEvent(QKeyEvent* event);

};

#endif // MAINWINDOW_H
