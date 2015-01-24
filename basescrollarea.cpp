#include "basescrollarea.h"
#include "Panels/basepanel.h"

BaseScrollArea::BaseScrollArea(QWidget *parent) : QScrollArea(parent)
{
}

void BaseScrollArea::mousePressEvent( QMouseEvent * event )
{
    this->ExecuteClick(event);
}

void BaseScrollArea::ExecuteClick( QMouseEvent * event)
{
  if(this->type == MAIN)
  {
      BasePanel::mainPanel->mousePressEvent(event);
      return;
  }
  if(this->type == FUNCTION)
  {
      BasePanel::functionPanel->mousePressEvent(event);
      return;
  }
}
