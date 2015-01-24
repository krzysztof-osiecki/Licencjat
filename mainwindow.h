#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QString checkFileName(QString name);

private slots:

    void on_actionExport_Full_Program_triggered();

    void on_actionImport_Full_Program_triggered();

    void on_actionExit_triggered();

    void on_actionContact_triggered();

    void on_actionCompile_and_Run_triggered();

    void on_actionCompile_triggered();

    void on_actionIncludes_triggered();

    void on_actionVariables_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
