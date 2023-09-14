#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    work_area = new QWidget(this);
    work_area->setGeometry(0, 0, 1280, 720);
    work_area->setFixedSize(1280, 720);
    menu = new StartMenu(work_area);
    work_area->show();
}

MainWindow::~MainWindow()
{
    delete menu;
    delete work_area;
    delete ui;
}

void MainWindow::GotoStartMenu()
{
    QWidget *senderObj;
    if (sender()->parent()->objectName() == menu->pid_form->objectName()) {
        senderObj = menu->pid_form;
    } else {
        senderObj = menu->settings_form;
    }
    senderObj->hide();
    QString imagePath = ":/pid.png";
    QString style = QString("background-image: url(%1)").arg(imagePath);
    this->work_area->setStyleSheet(style);
    menu->show();
}
