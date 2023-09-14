#ifndef ACCURACYFORM_H
#define ACCURACYFORM_H

#include "accuracy.h"

#include <QWidget>
#include <QtCharts>

namespace Ui {
class AccuracyForm;
}

class AccuracyForm : public QWidget, public Accuracy
{
    Q_OBJECT

public:
    explicit AccuracyForm(QWidget *parent = nullptr, float k_P = 0, float k_I = 0, float k_D = 0, float dx = 0.05f, float start_height = 5, float setpoint = 1);
    ~AccuracyForm();
    static void draw_diagram(AccuracyForm* ptr, int percents);
    static void all(AccuracyForm* ptr);

private:
    Ui::AccuracyForm *ui;
    QChart* pie_chart;
    QtCharts::QPieSeries* pie_series;
    QPieSlice *slice1, *slice2;
    QChartView* pie_chartview;

signals:
    void signal_for_bar(int);
    void signal_for_textedit(QString);
private slots:
    void button_analis_set_enabled();
    void update_bar(int);
    void update_textedit(QString);

};

#endif // ACCURACYFORM_H
