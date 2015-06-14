#include "variablesframe.h"
#include "ui_variablesframe.h"
#include "Variables/variablestablemodel.h"
#include "Panels/basepanel.h"
#include "Variables/variablemodel.h"
#include <QStandardItemModel>
#include <QMessageBox>

VariablesFrame::VariablesFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VariablesFrame)
{
    ui->setupUi(this);
    ui->tableView->setModel(&BasePanel::variableModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setWindowTitle("Variables");
}

VariablesFrame::~VariablesFrame()
{
    delete ui;
}

void VariablesFrame::on_pushButton_2_clicked()
{
    this->close();
}

void VariablesFrame::on_pushButton_clicked()
{
    if(ui->comboBox->currentText().isEmpty() || ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::warning(this, "Error!", "Type and name must be filled in.");
        return;
    }
    BasePanel::variableModel.append(VariableModel(ui->comboBox->currentText(), ui->lineEdit_2->text(), ui->lineEdit_3->text()));
    ui->comboBox->lineEdit()->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
}

void VariablesFrame::on_pushButton_3_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    QModelIndexList selectedRows = select->selectedRows();
    for(QModelIndex rowNumber : selectedRows)
    {
        BasePanel::variableModel.remove(rowNumber.row());
    }
}
