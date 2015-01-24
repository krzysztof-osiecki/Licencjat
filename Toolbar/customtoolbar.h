#ifndef CUSTOMTOOLBAR_H
#define CUSTOMTOOLBAR_H

#include <QToolBar>
#include <vector>
#include <QGroupBox>
#include <QFrame>
#include "Toolbar/customtoolbar.h"

class CustomToolbar : public QGroupBox
{
    Q_OBJECT
public:
    explicit CustomToolbar(QWidget *parent = 0);
    enum CommandType {IF, WHILE, DELETE, NONE, IFELSE, ELSE, FUNCTION, FUNCTION_PANEL, TEXT, DYNAMIC, CONTAINER};
    static CommandType selectedCommand;
signals:

public slots:
 void handleIfButton();
 void handleWhileButton();
 void handleDeleteButton();
 void handleIfElseButton();
 void handleFunctionButton();
 void handleNoneButton();
 void handleTextButton();
 void handleContainerButton();
};

#endif // CUSTOMTOOLBAR_H
