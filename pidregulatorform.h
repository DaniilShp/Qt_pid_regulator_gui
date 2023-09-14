#ifndef PIDREGULATORFORM_H
#define PIDREGULATORFORM_H

#include "accuracyform.h"
#include "PID.h"
#include "simulation.h"

#include <QWidget>
#include <Qtimer>
#include <QtCharts>
#include <QRandomGenerator>
#include <QThread>

namespace Ui {
class PidRegulatorForm;
}

class PidRegulatorForm : public QWidget
{
    Q_OBJECT

public:
    explicit PidRegulatorForm(QWidget *parent = nullptr);
    ~PidRegulatorForm();
    void get_k();
    void timer_tick1();

private:
    //variables//
    double k_P, k_I, k_D; // pid settings
    double x = 0, dx = DX, sdx = 0, setpoint = 1;
    int rotation_speed;
    bool on = true;
    PID* controller;
    SIMULATION* simulation;
    //
    Ui::PidRegulatorForm *ui;
    QTimer* timer;
    QChart* chart;
    QLineSeries* series;
    QChartView* chartView;
    AccuracyForm* analis_window = nullptr;

private slots:
    void pushbutton_clicked();
    void timer_tick();
    void spinbox_p_value_changed();
    void spinbox_i_value_changed();
    void spinbox_d_value_changed();
    void verticalslider_position_changed();
    void horizontalslider_position_changed();
    void verticalslider_2_position_changed();
    void show_analis_window();
    void start_accuracy_analis();
    void pushbutton_switch_clicked();

};

#endif // PIDREGULATORFORM_H
