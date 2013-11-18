#ifndef ABSTRACTPANEL_H
#define ABSTRACTPANEL_H

#include <QWidget>
#include "../Precompile.h"

enum STATE {LEFT = 0, RIGHT = 1};

class AbstractPanel : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractPanel(STATE state, QWidget *parent = 0);
    STATE state()   {return m_state;}

private:
    STATE m_state;

protected:    
    void state(STATE state)   {m_state = state;}

signals:
    
public slots:
    
};

#endif // ABSTRACTPANEL_H
