#include "sourcecodebuilder.h"
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <iostream>
#include <QProcess>
#include "qregexp.h"
#include <QDir>
#include <QMessageBox>
QString SourceCodeBuilder::imports = QString("#include <iostream> \n")
        + QString("#include <vector> \n")
        + QString("#include <string> \n")
        + QString("using namespace std; \n");
SourceCodeBuilder::SourceCodeBuilder()
{
}
QString SourceCodeBuilder::saveSourceCode(QString code)
{
    QDir dir;
    dir.mkpath(QApplication::applicationDirPath()+QString("/sourcecode/"));
    QString location = QApplication::applicationDirPath() + QString("/sourcecode/sourcecode") + QString::number(BasePanel::uniqueId()) + QString(".cpp");
    QFile codeFile(location);
    if(codeFile.open(QIODevice::WriteOnly | QIODevice::Text ))
    {
        QTextStream writeToFile(&codeFile);
        writeToFile << code << endl;
        codeFile.close();
        return location;
    }
    return "";
}
bool SourceCodeBuilder::compile(QString filePath)
{
    QProcess *proc = new QProcess;
    QString result = QApplication::applicationDirPath() + QString("/sourcecode/result");
    QStringList args = prepareGccArgsList(filePath, result);
    proc->start("g++", args);
    proc->waitForFinished();
    QString errorString = proc->readAllStandardError();
    if(!errorString.isEmpty())
    {
        QMessageBox::warning(new QWidget(), "Compilation Error", errorString);
        return false;
    }
    proc->close();
    return true;
}
bool SourceCodeBuilder::compileAndRun(QString filePath)
{
    QProcess *compileProc = new QProcess;
    QProcess *runProc = new QProcess;
    QString result = QApplication::applicationDirPath() + QString("/sourcecode/result");
    QStringList args = prepareGccArgsList(filePath, result);
    compileProc->start("g++", args);
    compileProc->waitForFinished();
    QString errorString = compileProc->readAllStandardError();
    if(!errorString.isEmpty())
    {
        QMessageBox::warning(new QWidget(), "Compilation Error", errorString);
        return false;
    }
    compileProc->close();
    delete compileProc;
    runProc->startDetached("xterm "+result);
    delete runProc;
    return true;
}

QStringList SourceCodeBuilder::prepareGccArgsList(QString filePath, QString resultPath)
{
    QStringList args;
    args << "-std=c++11";
    args << "--static";
    args << "-O2";
    args << filePath;
    args << "-o";
    args << resultPath;
    return args;
}
QString SourceCodeBuilder::generateSourceCode(BasePanel* mainPanel, BasePanel* functionPanel, bool run)
{
    QString imports = prepareImports();
    QString variables = prepareVariables();
    QString functionsHeaders = functionPanel->getHeaders();
    QString functions = functionPanel->getSourceCode();
    QString mainPart = mainPanel->getSourceCode();
    QString code = imports+variables+functionsHeaders+functions+mainPart;
    QString filePath = this->saveSourceCode(code);
    if(run)
    {
        this->compileAndRun(filePath);
    }
    else
    {
        this->compile(filePath);
    }
    return code;
}
QString SourceCodeBuilder::prepareImports()
{
    return imports;
}
QString SourceCodeBuilder::prepareVariables()
{
    QString result;
    foreach(VariableModel var, BasePanel::variableModel.variables)
    {
        result.append(var.type);
        result.append(separator);
        result.append(var.name);
        if(var.value != "")
        {
            result.append(" = ");
            if(var.type.contains(QRegExp("^string\\s*$")))
            {
                result.append("\"");
                result.append(var.value);
                result.append("\"");
            }
            else
            {
                result.append(var.value);
            }
        }
        result.append(instructionEnd);
        result.append("\n");
    }
    return result;
}
