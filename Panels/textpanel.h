#ifndef TEXTPANEL_H
#define TEXTPANEL_H

#include "basepanel.h"
#include "textblock.h"

class TextPanel : public BasePanel
{
    Q_OBJECT
public:
    explicit TextPanel(bool isFullPanel, BasePanel *parent);
    QString getSourceCode();
    QString getXml(bool withDesc = true);
    TextBlock* GetTextBlock();
    void contextMenuEvent( QContextMenuEvent *event );
protected:
    virtual void mousePressEvent ( QMouseEvent * event );
private:
    TextBlock* textBlock;
signals:

public slots:

};

#endif // TEXTPANEL_H
