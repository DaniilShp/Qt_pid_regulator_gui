#include "startmenu.h"
#include "ui_startmenu.h"

StartMenu::StartMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartMenu)
{
    ui->setupUi(this);
    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(on_pushButton_start_clicked()));
    connect(ui->pushButton_settings, SIGNAL(clicked()), this, SLOT(on_pushButton_settings_clicked()));
    connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(on_pushButton_quit_clicked()));
    pid_form = new PidRegulatorForm(this->parentWidget());
    pid_form->hide();
    settings_form = new Settingsform(this->parentWidget());
    settings_form->hide();
    QString imagePath = ":/pid.png";
    QString style = QString("background-image: url(%1)").arg(imagePath);
    this->parentWidget()->setStyleSheet(style);
}

StartMenu::~StartMenu()
{
    delete ui;
    delete pid_form;
}


void StartMenu::on_pushButton_start_clicked()
{
    this->hide();
    this->parentWidget()->setStyleSheet("background-image: none;");
    pid_form->show();
}

void StartMenu::on_pushButton_settings_clicked()
{
    this->hide();
    this->parentWidget()->setStyleSheet("background-image: none;");
    settings_form->show();
}

void StartMenu::on_pushButton_quit_clicked()
{
    this->parentWidget()->parentWidget()->close();
}

