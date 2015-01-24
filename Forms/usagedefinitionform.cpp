#include "usagedefinitionform.h"
#include "ui_usagedefinitionform.h"

UsageDefinitionForm::UsageDefinitionForm(BasePanel *parentPanel, QWidget *parent ) :
    QFrame(parent),
    ui(new Ui::UsageDefinitionForm)
{
    this->connectedPanel = parentPanel;
    ui->setupUi(this);
    ui->tableView->setModel(&this->attributesModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

UsageDefinitionForm::~UsageDefinitionForm()
{
    delete ui;
}

void UsageDefinitionForm::on_pushButton_clicked()
{
    this->attributesModel.append(AttributeModel(ui->lineEdit->text(), ui->textEdit->toPlainText(), ui->lineEdit_2->text(), ui->comboBox->currentText()));
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->textEdit->setText("");
    ui->comboBox->setCurrentIndex(0);
}

void UsageDefinitionForm::on_pushButton_2_clicked()
{
    this->connectedPanel->componentName = ui->lineEdit_3->text();
    this->connectedPanel->description = ui->textEdit_2->toPlainText();
    this->connectedPanel->usageFormXml = this->attributesModel.getXml();
    this->connectedPanel->saveAsComponent();
    this->close();
}

void UsageDefinitionForm::on_pushButton_3_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    QModelIndexList selectedRows = select->selectedRows();
    for(QModelIndex rowNumber : selectedRows)
    {
        this->attributesModel.remove(rowNumber.row());
    }
}
