#include "includesframe.h"
#include "ui_includesframe.h"
#include "Serialization/sourcecodebuilder.h"

IncludesFrame::IncludesFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::IncludesFrame)
{
    ui->setupUi(this);
    ui->textEdit->setText(SourceCodeBuilder::imports);
    this->setWindowTitle("Includes");
}

IncludesFrame::~IncludesFrame()
{
    delete ui;
}

void IncludesFrame::on_pushButton_clicked()
{
    SourceCodeBuilder::imports = ui->textEdit->toPlainText();
    this->close();
}
