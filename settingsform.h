#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Settingsform;
}

class Settingsform : public QWidget
{
    Q_OBJECT

public:
    explicit Settingsform(QWidget *parent = nullptr);
    ~Settingsform();

private:
    Ui::Settingsform *ui;

private slots:
    void pushbutton_info_clicked();
};

#endif // SETTINGSFORM_H
