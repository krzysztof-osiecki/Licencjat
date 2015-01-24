#include "newfunctionform.h"
#include "ui_newfunctionform.h"

NewFunctionForm::NewFunctionForm(FunctionBlock* parentPanel,  QWidget *parent) :
    QFrame(parent),
    ui(new Ui::NewFunctionForm)
{
    this->parentPanel=parentPanel;
    ui->setupUi(this);
    ui->tableView->setModel(&parentPanel->parametersModel);
    ui->comboBox->setCurrentText(this->parentPanel->type);
    ui->lineEdit_2->setText(this->parentPanel->name);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

NewFunctionForm::~NewFunctionForm()
{
    delete ui;
}

void NewFunctionForm::on_pushButton_clicked()
{
    this->parentPanel->type = ui->comboBox->currentText();
    this->parentPanel->name = ui->lineEdit_2->text();
    this->parentPanel->setTitle(ui->comboBox->currentText()+" "+ui->lineEdit_2->text());
}

void NewFunctionForm::on_pushButton_2_clicked()
{
    this->parentPanel->parametersModel.append(VariableModel(ui->comboBox_2->currentText(), ui->lineEdit_4->text()));
}

void NewFunctionForm::on_pushButton_3_clicked()
{
    this->close();
}

void NewFunctionForm::on_pushButton_4_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    QModelIndexList selectedRows = select->selectedRows();
    for(QModelIndex rowNumber : selectedRows)
    {
        this->parentPanel->parametersModel.remove(rowNumber.row());
    }
}
