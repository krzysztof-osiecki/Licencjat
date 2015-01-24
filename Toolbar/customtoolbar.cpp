#include "customtoolbar.h"
#include "Toolbar/customtoolbarbutton.h"
#include "Serialization/sourcecodebuilder.h"
#include "Forms/variablesframe.h"
#include "Forms/includesframe.h"
#include "Serialization/xmlparser.h"
#include "Panels/basepanel.h"
#include <QFileDialog>
#include <QFile>
#include <QDesktopWidget>
#include <QGroupBox>
#include <QMessageBox>
#include <QGridLayout>
#include <QTextStream>

CustomToolbar::CommandType CustomToolbar::selectedCommand = CustomToolbar::NONE;

CustomToolbar::CustomToolbar(QWidget *parent) : QGroupBox(parent)
{
    this->setTitle("Predefined Blocks");
    this->setLayout(new BasePanelLayout());
    this->layout()->setAlignment(Qt::AlignTop);
    this->layout()->setSpacing(30);
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    this->layout()->addWidget(line);
    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());

    QString napis = "Loop";
    CustomToolbarButton *whileButton = new CustomToolbarButton;
    whileButton->commandType = CustomToolbar::WHILE;
    whileButton->setText(napis);

    napis = "If";
    CustomToolbarButton *ifButton = new CustomToolbarButton;
    ifButton->commandType = CustomToolbar::IF;
    ifButton->setText(napis);

    napis = "Delete";
    CustomToolbarButton *deleteButton = new CustomToolbarButton;
    deleteButton->commandType = CustomToolbar::DELETE;
    deleteButton->setText(napis);

    napis = "If-Else";
    CustomToolbarButton *ifElseButton = new CustomToolbarButton;
    ifElseButton->commandType = CustomToolbar::IFELSE;
    ifElseButton->setText(napis);

    napis = "Function";
    CustomToolbarButton *functionButton = new CustomToolbarButton;
    functionButton->commandType = CustomToolbar::FUNCTION;
    functionButton->setText(napis);

    napis = "None";
    CustomToolbarButton *noneButton = new CustomToolbarButton;
    noneButton ->commandType = CustomToolbar::NONE;
    noneButton ->setText(napis);

    napis = "Text";
    CustomToolbarButton *textButton = new CustomToolbarButton;
    textButton->commandType = CustomToolbar::TEXT;
    textButton->setText(napis);

    napis = "Container";
    CustomToolbarButton *containerButton = new CustomToolbarButton;
    containerButton->commandType = CustomToolbar::CONTAINER;
    containerButton->setText(napis);

    connect(whileButton, SIGNAL(clicked()), this, SLOT(handleWhileButton()));
    connect(ifButton, SIGNAL(clicked()), this, SLOT(handleIfButton()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(handleDeleteButton()));
    connect(ifElseButton, SIGNAL(clicked()), this, SLOT(handleIfElseButton()));
    connect(functionButton, SIGNAL(clicked()), this, SLOT(handleFunctionButton()));
    connect(noneButton, SIGNAL(clicked()), this, SLOT(handleNoneButton()));
    connect(textButton, SIGNAL(clicked()), this, SLOT(handleTextButton()));
    connect(containerButton, SIGNAL(clicked()), this, SLOT(handleContainerButton()));

    this->layout()->addWidget(whileButton);
    this->layout()->addWidget(ifButton);
    this->layout()->addWidget(ifElseButton);
    this->layout()->addWidget(functionButton);
    this->layout()->addWidget(textButton);
    this->layout()->addWidget(containerButton);
    this->layout()->addWidget(noneButton);
    this->layout()->addWidget(deleteButton);

    this->setMaximumWidth(mainScreenSize.width()/9);
}

void CustomToolbar::handleIfButton()
{
    CustomToolbar::selectedCommand = CustomToolbar::IF;
}

void CustomToolbar::handleWhileButton()
{
    CustomToolbar::selectedCommand = CustomToolbar::WHILE;
}

void CustomToolbar::handleDeleteButton()
{
    CustomToolbar::selectedCommand = CustomToolbar::DELETE;
}

void CustomToolbar::handleIfElseButton()
{
    CustomToolbar::selectedCommand = CustomToolbar::IFELSE;
}

void CustomToolbar::handleFunctionButton()
{
    CustomToolbar::selectedCommand = CustomToolbar::FUNCTION;
}

void CustomToolbar::handleNoneButton()
{
    CustomToolbar::selectedCommand = CustomToolbar::NONE;
}

void CustomToolbar::handleTextButton()
{
    CustomToolbar::selectedCommand = CustomToolbar::TEXT;
}

void CustomToolbar::handleContainerButton()
{
    CustomToolbar::selectedCommand = CustomToolbar::CONTAINER;
}
