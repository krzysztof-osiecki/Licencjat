#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Panels/basepanel.h"
#include "Serialization/xmlparser.h"
#include "Serialization/sourcecodebuilder.h"
#include "Forms/variablesframe.h"
#include "Forms/includesframe.h"
#include <QMouseEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExport_Full_Program_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("Files (*.xml)"));
    if(!fileName.isNull() && !fileName.isEmpty())
    {
        XmlParser parser;
        parser.ParseAndSaveXml(BasePanel::mainPanel, BasePanel::functionPanel, this->checkFileName(fileName));
    }
}

void MainWindow::on_actionImport_Full_Program_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.xml)"));
    QFile codeFile(fileName);
    if(codeFile.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        QString xml = codeFile.readAll();
        XmlParser parser;
        parser.CreatePanelStructureFromXml(xml);
        codeFile.close();
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionContact_triggered()
{
    QMessageBox::about(0, "Contact", "krzysztof@live.fr");
}

void MainWindow::on_actionCompile_and_Run_triggered()
{
    SourceCodeBuilder *codeBuilder = new SourceCodeBuilder;
    codeBuilder->generateSourceCode(BasePanel::mainPanel, BasePanel::functionPanel, true);
    delete codeBuilder;
}

void MainWindow::on_actionCompile_triggered()
{
    SourceCodeBuilder *codeBuilder = new SourceCodeBuilder;
    codeBuilder->generateSourceCode(BasePanel::mainPanel, BasePanel::functionPanel, false);
    delete codeBuilder;
}

void MainWindow::on_actionIncludes_triggered()
{
    IncludesFrame* frame = new IncludesFrame;
    frame->setAttribute(Qt::WA_DeleteOnClose);
    frame->show();
}

void MainWindow::on_actionVariables_triggered()
{
    VariablesFrame* frame = new VariablesFrame;
    frame->setAttribute(Qt::WA_DeleteOnClose);
    frame->show();
}

QString MainWindow::checkFileName(QString name)
{
    return name.contains(".xml") ? name : name+".xml";
}
