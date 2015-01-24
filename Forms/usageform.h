#ifndef USAGEFORM_H
#define USAGEFORM_H

#include "Panels/dynamicblock.h"
#include <QFrame>
#include <QList>
#include <QLineEdit>
#include <QComboBox>

namespace Ui {
class UsageForm;
}

class UsageForm : public QFrame
{
    Q_OBJECT

public:
    explicit UsageForm(DynamicBlock *parentPanel, QWidget *parent = NULL);
    ~UsageForm();
    DynamicBlock* connectedPanel;
    QList<QLineEdit*> edits;
    QList<QComboBox *> combos;
private:
    QStringList getFittingVariables(QString type);
    Ui::UsageForm *ui;
private slots:
    void ok();
};

#endif // USAGEFORM_H
