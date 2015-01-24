#include "dynamictoolbar.h"
#include "customtoolbarbutton.h"
#include "Serialization/xmlparser.h"
#include <QGroupBox>
#include <QDir>
#include <QApplication>

int DynamicToolbar::selectedIndex = -1;
QStringList DynamicToolbar::labels;
QStringList DynamicToolbar::xmls;

DynamicToolbar::DynamicToolbar(QWidget *parent) : QGroupBox(parent)
{
    this->setTitle("Dynamic components");
    this->setLayout(new BasePanelLayout());
    this->loadComponents();
}

void DynamicToolbar::clearToolbar()
{
    labels.clear();
    xmls.clear();
    QLayoutItem *child;
    while ((child = this->layout()->takeAt(0)) != 0) {
        QWidget* stepchild;
        stepchild=child->widget();
        delete stepchild;
        delete child;
    }
}

void DynamicToolbar::loadComponents()
{
    this->clearToolbar();
    this->layout()->setAlignment(Qt::AlignTop);
    this->layout()->setSpacing(30);

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    this->layout()->addWidget(line);

    CustomToolbarButton *button = new CustomToolbarButton;
    button->setText("Reload Components");
    connect(button, SIGNAL(clicked()), this, SLOT(loadComponents()));
    this->layout()->addWidget(button);

    QFrame* line2 = new QFrame();
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    this->layout()->addWidget(line2);

    QDir dir;
    dir.setPath(QApplication::applicationDirPath()+"/components");
    QStringList filters;
    filters << "*.cmp" << "*.xml" << "*.txt";
    dir.setNameFilters(filters);
    QStringList componentFiles = dir.entryList();
    for(QString fileName : componentFiles)
    {
        QFile codeFile(dir.path()+"/"+fileName);
        if(codeFile.open(QIODevice::ReadOnly | QIODevice::Text ))
        {
            QString xml = codeFile.readAll();
            labels.append(fileName);
            xmls.append(xml);
            codeFile.close();
        }
    }

    for(int i = 0; i<labels.size(); i++)
    {
        CustomToolbarButton *button = new CustomToolbarButton;
        button->setText(labels.at(i));

        connect(button, SIGNAL(clicked()), this, SLOT(handleButton()));

        this->layout()->addWidget(button);
    }
}

void DynamicToolbar::handleButton()
{
    CustomToolbar::selectedCommand = CustomToolbar::DYNAMIC;
    CustomToolbarButton* button = (CustomToolbarButton*) this->sender();
    DynamicToolbar::selectedIndex = labels.indexOf(button->text());
}
