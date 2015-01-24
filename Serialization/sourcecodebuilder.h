#ifndef SOURCECODEBUILDER_H
#define SOURCECODEBUILDER_H
#include <QString>
#include <QObject>
#include "Panels/basepanel.h"
#include <QProcess>

class SourceCodeBuilder : QObject
{
        Q_OBJECT
public:
    explicit SourceCodeBuilder();
    QString generateSourceCode(BasePanel* mainPanel, BasePanel* functionPanels, bool run);
    QString saveSourceCode(QString code);
    bool compileAndRun(QString filePath);
    bool compile(QString filePath);
    static QString imports;
private:
    QString separator = " ";
    QString instructionEnd = ";";
    QStringList prepareGccArgsList(QString filePath, QString resultPath);
    QString prepareImports();
    QString prepareVariables();
signals:

public slots:
};

#endif // SOURCECODEBUILDER_H
