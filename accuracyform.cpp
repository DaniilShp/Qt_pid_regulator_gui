#include "accuracyform.h"
#include "ui_accuracyform.h"
#include <iostream>

AccuracyForm::AccuracyForm(QWidget *parent, float k_P, float k_I, float k_D, float dx, float start_height, float setpoint) :
    QWidget(parent),
    Accuracy(k_P, k_I, k_D, dx, start_height, setpoint),
    ui(new Ui::AccuracyForm)
{
    ui->setupUi(this);
    connect(ui->pushbutton_analis, SIGNAL(clicked(bool)), parent, SLOT(start_accuracy_analis()));
    connect(this, SIGNAL(signal_for_bar(int)), this, SLOT(update_bar(int)));
    connect(this, SIGNAL(signal_for_textedit(QString)), this, SLOT(update_textedit(QString)));
    pie_series = new QPieSeries();
    slice1 = new QPieSlice("accuracy", 0);
    slice2 = new QPieSlice("", 100);
    slice1->setColor(Qt::red);
    slice2->setColor(Qt::darkRed);
    slice1->setLabelColor(Qt::black);
    slice1->setLabel("accuracy is 0%");
    QFont font; font.setPointSize(9);
    slice1->setLabelFont(font);
    slice1->setLabelVisible(true);
    pie_series->append(slice1);
    pie_series->append(slice2);
    pie_chart = new QChart();
    pie_chart->addSeries(pie_series);
    pie_chart->setBackgroundBrush(Qt::transparent);
    pie_chartview = new QChartView(pie_chart, this);
    pie_chartview->setGeometry(105, 65, 600, 300);
    pie_chartview->setBackgroundBrush(Qt::darkGray);
    pie_chart->legend()->setVisible(false);
    pie_chartview->show();
    ui->progressBar->setAlignment(Qt::AlignCenter);
    ui->textEdit->setText("В этом окне можно узнать качество настройки и получить информацию о других вариантах настройки");
}

void AccuracyForm::button_analis_set_enabled()
{
    if(ui->pushbutton_analis->isVisible())
        ui->pushbutton_analis->setVisible(false);
    else
        ui->pushbutton_analis->setVisible(true);
}

AccuracyForm::~AccuracyForm()
{
    delete ui;
}

void AccuracyForm::update_bar(int value)
{
    ui->progressBar->setValue(value);
}

void AccuracyForm::update_textedit(QString info)
{
    ui->textEdit->append(info);
    QScrollBar* scrollbar = ui->textEdit->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void AccuracyForm::draw_diagram(AccuracyForm* ptr, int percents)
{
    if (percents < 12) {
        QFont font; font.setPointSize(9);
        ptr->slice1->setLabelFont(font);
    } else {
        QFont font; font.setPointSize(11);
        ptr->slice1->setLabelFont(font);
    }
    ptr->slice1->setLabel(QString("accuracy is ") + QString::number(percents) + QString("%"));
    ptr->slice1->setValue(percents);
    ptr->slice2->setValue(100-percents);
}

void AccuracyForm::all(AccuracyForm* ptr)
{
    QString message;
    message += QString("\nanalis started\n");
    int max = 0;
    int kp, ki, kd;
    for(int p = 0; p < 100; p++)
    {
            for(int d = 0; d < 1000; d+=1)
            {
                Accuracy obj(static_cast<float>(p)/4, 0.0f, static_cast<float>(d)/1000, ptr->dx, ptr->start_height, ptr->setpoint);
                emit ptr->signal_for_bar(p+1);
                int points = obj.run();
                if (points>max) {
                    max = points;
                    kp = p; ki=0;kd=d;
            }
        }
    }
    message += QString("max / kp / ki / kd / start height / setpoint\n");
    message+=QString::number(max) + " " + QString::number(kp) + " " + QString::number(ki) + " " + QString::number(kd) + " " + QString::number(ptr->start_height) + " " + QString::number(ptr->setpoint) + QString(" accurcy is 100%")+"\n";
    Accuracy obj(ptr->k_P, ptr->k_I, ptr->k_D, ptr->dx, ptr->start_height, ptr->setpoint);
    int points = obj.run();
    int accuracy_in_percents;
    accuracy_in_percents = qRound((static_cast<float>(points) / max * 100));
    message+=QString("your settings accuracy in % is: ") + QString::number(accuracy_in_percents);
    message+=QString("\nfinished!");
    emit ptr->signal_for_textedit(message);
    ptr->draw_diagram(ptr, accuracy_in_percents);
    return ;
}
