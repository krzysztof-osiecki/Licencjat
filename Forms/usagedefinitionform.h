#ifndef USAGEDEFINITIONFORM_H
#define USAGEDEFINITIONFORM_H

#include "Panels/basepanel.h"
#include "Variables/attributestablemodel.h"
#include <QFrame>

namespace Ui {
class UsageDefinitionForm;
}

class UsageDefinitionForm : public QFrame
{
    Q_OBJECT

public:
    explicit UsageDefinitionForm(BasePanel *parentPanel, QWidget *parent = NULL);
    ~UsageDefinitionForm();
    BasePanel* connectedPanel;
    AttributesTableModel attributesModel;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::UsageDefinitionForm *ui;
};

#endif // USAGEDEFINITIONFORM_H
