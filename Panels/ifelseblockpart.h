#ifndef IFELSEBLOCKPART_H
#define IFELSEBLOCKPART_H

#include "basepanel.h"

class IfElseBlockPart : public BasePanel
{
    Q_OBJECT
public:
    explicit IfElseBlockPart(bool isFullPanel, BasePanel *parent);
    QString getSourceCode();
    QString getXml(bool withDesc = true);
protected:
    virtual void mousePressEvent ( QMouseEvent * event );
private:
    QString prepareCondition();
signals:

public slots:

};

#endif // IFELSEBLOCKPART_H
