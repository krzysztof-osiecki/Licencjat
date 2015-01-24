#ifndef FUNCTIONPANEL_H
#define FUNCTIONPANEL_H

#include "basepanel.h"
#include "QGroupBox"

class FunctionPanel : public BasePanel
{
    Q_OBJECT
public:
    explicit FunctionPanel(bool isFullPanel, BasePanel *parent);
    QString getHeaders();
    QString getSourceCode();
    QString getXml(bool withDesc = true);
protected:
    virtual void mousePressEvent ( QMouseEvent * event );
signals:

public slots:

};

#endif // FUNCTIONPANEL_H
