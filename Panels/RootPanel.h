#ifndef ROOTBROWSEPANEL_H
#define ROOTBROWSEPANEL_H

#include "../Precompile.h"
#include "AbstractPanel.h"

class RootTable;

class RootPanel : public AbstractPanel
{
    Q_OBJECT
public:
    static RootPanel* getInst(STATE state, QWidget *parent);
    static void freeInst();
    void showA(STATE s);

private:
    RootPanel(STATE state, QWidget *parent);

    static RootPanel* m_pRootBrowsePanel;
    void hideA();

    RootTable* m_pTable;
    QFileSystemModel m_model;
    int m_rightPosX;
    int m_posY;

private slots:
    void goToDisk(const QString& sPath);

signals:
    void goToDisk(const QString& sPath, STATE state);

protected:
    void keyPressEvent(QKeyEvent* event);


};



//class RootTable : public QTableView
//{
//    Q_OBJECT
//public:
//    explicit RootTable(QWidget *parent);
//  //  void goToPath(const QString& sPath);

//protected:
//    void keyPressEvent(QKeyEvent* event);

//signals:
//    void goToDisk(const QString& sPath);

//};


#endif // ROOTBROWSEPANEL_H
