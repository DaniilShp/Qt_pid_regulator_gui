#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "startmenu.h"
#include "pidregulatorform.h"

#include <QMainWindow>
#include <QWidget>
#include <QMdiArea>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget* work_area;
    StartMenu* menu;
    //PidRegulatorForm* pid_form;

private slots:
    void GotoStartMenu();
};
#endif // MAINWINDOW_H
