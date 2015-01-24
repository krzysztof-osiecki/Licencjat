#include "ifconditionframe.h"
#include "ui_ifconditionframe.h"
#include "Panels/basepanel.h"

IfConditionFrame::IfConditionFrame(BasePanel *parentPanel, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::IfConditionFrame)
{
    ui->setupUi(this);
    this->connectedPanel = parentPanel;
    ui->lineEdit->setText(this->connectedPanel->condition);
}

IfConditionFrame::~IfConditionFrame()
{
    delete ui;
}

void IfConditionFrame::on_pushButton_2_clicked()
{
    this->close();
}

void IfConditionFrame::on_pushButton_clicked()
{
    this->connectedPanel->condition = ui->lineEdit->text();
    this->connectedPanel->setTitle("if("+ this->connectedPanel->condition+")");
    this->close();
}
