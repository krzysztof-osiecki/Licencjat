#include "renameframe.h"
#include "ui_renameframe.h"

RenameFrame::RenameFrame(BasePanel *parentPanel, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RenameFrame)
{
    ui->setupUi(this);
    this->connectedPanel = parentPanel;
    ui->lineEdit->setText(this->connectedPanel->title);
    ui->textEdit->setText(this->connectedPanel->description);
}

RenameFrame::~RenameFrame()
{
    delete ui;
}

void RenameFrame::on_pushButton_clicked()
{
    this->connectedPanel->title = ui->lineEdit->text();
    this->connectedPanel->description = ui->textEdit->toPlainText();
    this->connectedPanel->executeTitleAndDescChange();
    this->close();
}
