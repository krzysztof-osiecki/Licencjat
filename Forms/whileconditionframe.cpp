#include "whileconditionframe.h"
#include "ui_whileconditionframe.h"


WhileConditionFrame::WhileConditionFrame(BasePanel *parentPanel, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::WhileConditionFrame)
{
    ui->setupUi(this);
    QList<QString> items;
    foreach(VariableModel var, BasePanel::variableModel.variables)
    {
        if (var.type.contains(QRegularExpression("^[\\w\\s,]+<[\\w\\s,<>_]+>$"))){
            ui->comboBox->addItem(var.name+" - "+var.type);
        }
        else if(var.name.contains(QRegularExpression(("^[\\w_]+\\[[\\w_]*\\]$")))) {
            ui->comboBox->addItem(var.name+" - "+var.type);
        }
        else if(var.type.contains(QRegularExpression("^string\\s*$"))) {
            ui->comboBox->addItem(var.name+" - "+var.type);
        }
    }

    ui->comboBox->addItems(items);
    this->connectedPanel = parentPanel;
}

WhileConditionFrame::~WhileConditionFrame()
{
    delete ui;
}

void WhileConditionFrame::on_pushButton_4_clicked()
{
    this->close();
}

void WhileConditionFrame::on_pushButton_clicked()
{
    this->connectedPanel->condition = "while("+ui->lineEdit->text()+")";
    this->connectedPanel->setTitle(this->connectedPanel->condition);
    this->close();
}

void WhileConditionFrame::on_pushButton_2_clicked()
{
    QString variableUniqueId = QString::number(BasePanel::uniqueId());
    QString condition = "int zxcvbnm; int tmp"+variableUniqueId+";for(zxcvbnm = 0,tmp"+ variableUniqueId +"= 0; "
            + " zxcvbnm <"+QString::number(ui->spinBox->value())+"; "
            + " zxcvbnm++)";
    this->connectedPanel->setTitle("This loop will allways execute "+QString::number(ui->spinBox->value())+" times.\n"
                                   + "You can acces loop iterator by name: tmp"+ variableUniqueId);
    this->connectedPanel->condition = condition;
    this->close();
}

void WhileConditionFrame::on_pushButton_3_clicked()
{
    QString body;
    QString variableUniqueId = QString::number(BasePanel::uniqueId());
    QString selected = ui->comboBox->currentText();
    QString name = selected.mid(0, selected.indexOf("-")-1);
    if(selected.contains(QRegularExpression("string\\s*")))
    {
        body = "char & var"+variableUniqueId+": "+ name;
    }
    else if (selected.contains(QRegularExpression("[\\w\\s,]+<[\\w\\s,<>_]+>")))
    {
        QString variableType;
        variableType = selected.mid(selected.indexOf("<")+1, selected.lastIndexOf(">")-selected.indexOf("<")-1);
        body = variableType+" & var"+variableUniqueId+": "+name;
    }
    else if (selected.contains(QRegularExpression(("[\\w_]+\\[[\\w_]*\\]"))))
    {
        QString variableType;
        name = name.mid(0, name.indexOf("["));
        variableType = selected.mid(selected.indexOf("-")+1, selected.size()-selected.indexOf("-"));
        body = variableType+" & var"+variableUniqueId+": "+name;
    }

    QString condition = "for("+body+")";
    this->connectedPanel->setTitle("This loop iterates "+selected+".\n"
                                   + "You can acces loop iterator by name: var"+ variableUniqueId);
    this->connectedPanel->condition = condition;
    this->close();
    this->close();

}

