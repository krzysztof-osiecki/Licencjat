#include "mainwindow.h"
#include "basepanellayout.h"
#include "Panels/functionpanel.h"
#include "Panels/basepanel.h"
#include "Toolbar/customtoolbar.h"
#include "Toolbar/dynamictoolbar.h"
#include "Forms/variablesframe.h"
#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QScrollArea>
#include <QDesktopWidget>
#include <QTabWidget>
#include "QMenuBar"
#include "basescrollarea.h"

QString styleSheet = "style.qss";

int main(int argc, char *argv[])
{
    //initialization
    QApplication a(argc, argv);
    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    QWidget *mainWidget = new QWidget;
    QGridLayout *grid = new QGridLayout;

    //set up left side toolbar
    CustomToolbar *toolbar = new CustomToolbar;
    grid->addWidget(toolbar, 0, 0, -1, 1);

    //set up dynamic components toolbaar
    DynamicToolbar *dynamicToolbar = new DynamicToolbar;
    grid->addWidget(dynamicToolbar, 0, 1, -1, 1);

    //add tab widget to grid
    QTabWidget *tabWidget = new QTabWidget;
    grid->addWidget(tabWidget, 0, 2 , -1, 1);

    //set up main function panel
    BasePanel* panel = new BasePanel(true, 0);
    BasePanel::mainPanel = panel;
    BaseScrollArea *scroll = new BaseScrollArea;
    scroll->type = BaseScrollArea::MAIN;
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setWidget(panel);
    scroll->setAlignment(Qt::AlignHCenter);
    tabWidget->addTab(scroll, "Main Panel");

    //set up other functions panel
    FunctionPanel* functionsPanel = new FunctionPanel(true, 0);
    BasePanel::functionPanel = functionsPanel;
    BaseScrollArea *functionScroll = new BaseScrollArea;
    functionScroll->type = BaseScrollArea::FUNCTION;
    functionScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    functionScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    functionScroll->setWidget(functionsPanel);
    functionScroll->setAlignment(Qt::AlignHCenter);
    tabWidget->addTab(functionScroll, "Functions Panel");

    //set size of grid columns
    grid->setColumnMinimumWidth(0,mainScreenSize.width()/9);
    grid->setColumnMinimumWidth(1,mainScreenSize.width()/9);
    grid->setColumnMinimumWidth(2,6.6*mainScreenSize.width()/9);


    //apply stylesheet
    QFile styleFile(styleSheet);
    if(styleFile.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        qApp->setStyleSheet(styleFile.readAll());
    }

    //set main widget
    mainWidget->setLayout(grid);
    w.setCentralWidget(mainWidget);
    w.show();
    return a.exec();
}
