#include "settingsform.h"
#include "ui_settingsform.h"

Settingsform::Settingsform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settingsform)
{
    ui->setupUi(this);
    connect(ui->pushButton_back, SIGNAL(clicked(bool)), this->parent()->parent(), SLOT(GotoStartMenu()));
    connect(ui->pushbutton_info, SIGNAL(clicked(bool)), this, SLOT(pushbutton_info_clicked()));
}

void Settingsform::pushbutton_info_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Данное приложение разработано с использованием бесплатной лицензии Qt.");
    msgBox.setStyleSheet("QMessageBox, QLabel {background-color: 000000; color: ffffff;}");
    msgBox.exec();
}

Settingsform::~Settingsform()
{
    delete ui;
}
