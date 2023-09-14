#ifndef STARTMENU_H
#define STARTMENU_H

#include "pidregulatorform.h"
#include "settingsform.h"

#include <QWidget>

namespace Ui {
class StartMenu;
}

class StartMenu : public QWidget
{
    Q_OBJECT

public:
    PidRegulatorForm* pid_form;
    Settingsform* settings_form;
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

private:
    Ui::StartMenu *ui;

private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_settings_clicked();
    void on_pushButton_quit_clicked();
};

#endif // STARTMENU_H
