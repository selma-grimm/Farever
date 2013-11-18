#include "AbstractPanel.h"

AbstractPanel::AbstractPanel(STATE state, QWidget *parent) :
    QWidget(parent)
  , m_state(state)
{
}
