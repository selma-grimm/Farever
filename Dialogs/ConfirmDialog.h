#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QWidget>

class ConfirmDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ConfirmDialog(QWidget *parent = 0);
    void showDialog(const QString& obj_name);

protected:
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *event);

signals:
    void confirm();
    void close();
    
public slots:


private:
    QLabel* label_;
    
};

#endif // CONFIRMDIALOG_H
