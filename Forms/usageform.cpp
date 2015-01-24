#include "usageform.h"
#include "ui_usageform.h"
#include "Constants.h"
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QComboBox>
#include <QGridLayout>

UsageForm::UsageForm(DynamicBlock *parentPanel, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UsageForm)
{
    this->connectedPanel = parentPanel;
    ui->setupUi(this);
    QGridLayout *layout = new QGridLayout;

    for(int i = 0; i<parentPanel->attributesModel.attributes.size(); i++)
    {
        AttributeModel attribute = parentPanel->attributesModel.attributes.at(i);
        layout->addWidget(new QLabel(attribute.name), i, 0, 1, 1);
        QLineEdit *edit = new QLineEdit();
        edits.append(edit);
        layout->addWidget(edit, i, 1, 1, 1);

        QComboBox *variableCombo = new QComboBox();
        variableCombo->addItem("None");
        combos.append(variableCombo);
        if(!attribute.variableType.isEmpty() && attribute.variableType.compare(NONE_ATTRIBUTES, Qt::CaseInsensitive) != 0)
        {
            QStringList items = getFittingVariables(attribute.variableType);
            variableCombo->addItems(items);
            layout->addWidget(variableCombo, i, 2, 1, 1);
        }
        layout->addWidget(new QLabel(attribute.description), i, 3, 1, 1);
    }
    QPushButton* button = new QPushButton("Ok");
    connect(button, SIGNAL(clicked()), this, SLOT(ok()));
    layout->addWidget(button);
    this->setLayout(layout);
}

QStringList UsageForm::getFittingVariables(QString type)
{
    QStringList result;
    for(VariableModel var : BasePanel::variableModel.variables)
    {
        if(var.type.compare(type) == 0 || type == ANY_ATTRIBUTES)
        {
            result.append(var.name);
        }
    }
    return result;
}

UsageForm::~UsageForm()
{
    delete ui;
}

void UsageForm::ok()
{
    for(int i = 0; i<edits.count(); i++)
    {
        QComboBox *combo = combos.at(i);
        if(combo->currentIndex() == 0)
        {
            QLineEdit *edit = edits.at(i);
            if(edit->text().isNull() || edit->text().isEmpty())
            {
                QMessageBox::warning(this, "Error", "You must fill values of all arguments!");
                return;
            }
            QString t = edit->text();
            this->connectedPanel->attributesModel.attributes[i].value = edit->text();
        }
        else
        {
            this->connectedPanel->attributesModel.attributes[i].value = combo->currentText();
        }
    }
    this->close();
}
