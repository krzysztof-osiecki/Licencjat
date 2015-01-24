#ifndef CUSTOMTOOLBARBUTTON_H
#define CUSTOMTOOLBARBUTTON_H

#include <a.out.h>
#include <vector>
#include <QPushButton>
#include "Toolbar/customtoolbar.h"

class CustomToolbarButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CustomToolbarButton(QWidget *parent = 0);
    enum CustomToolbar::CommandType commandType;
signals:

public slots:

};

#endif // CUSTOMTOOLBARBUTTON_H
