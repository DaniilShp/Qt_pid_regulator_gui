#include "pidregulatorform.h"
#include "ui_pidregulatorform.h"
#include <iostream>

PidRegulatorForm::PidRegulatorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PidRegulatorForm)
{
    controller = new PID(0, 0, 0, DX);
    simulation = new SIMULATION(START_H, DX);
    ui->setupUi(this);
    ui->label_ball->setStyleSheet("QLabel {background-color: none;}");
    ui->pushButton_back->setIcon(QIcon::fromTheme("edit-undo"));
    ui->verticalSlider->setMaximum(10);
    ui->verticalSlider->setMinimum(1);
    ui->verticalSlider->setTickInterval(1);
    ui->verticalSlider->setSliderPosition(5);
    ui->horizontalSlider->setMaximum(120);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setTickInterval(1);
    ui->horizontalSlider->setSliderPosition(50);
    ui->verticalSlider_2->setMaximum(15);
    ui->verticalSlider_2->setMinimum(5);
    ui->verticalSlider_2->setTickInterval(1);
    ui->verticalSlider_2->setSliderPosition(10);
    connect(ui->pushButton_back, SIGNAL(clicked(bool)), this->parent()->parent(), SLOT(GotoStartMenu()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(pushbutton_clicked()));
    connect(ui->spinbox_p, SIGNAL(valueChanged(int)), this, SLOT(spinbox_p_value_changed()));
    connect(ui->spinbox_i, SIGNAL(valueChanged(int)), this, SLOT(spinbox_i_value_changed()));
    connect(ui->spinbox_d, SIGNAL(valueChanged(int)), this, SLOT(spinbox_d_value_changed()));
    connect(ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(verticalslider_position_changed()));
    connect(ui->verticalSlider_2 , SIGNAL(valueChanged(int)), this, SLOT(verticalslider_2_position_changed()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(horizontalslider_position_changed()));
    connect(ui->pushButton_show_analis_window, SIGNAL(clicked(bool)), this, SLOT(show_analis_window()));
    connect(ui->pushButton_switch, SIGNAL(clicked(bool)), this, SLOT(pushbutton_switch_clicked()));
    timer = new QTimer();
    timer->setInterval(25);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_tick()));
    ui->label_ball->setPixmap(QPixmap(":/ball.png"));
    ui->label_fan->setPixmap(QPixmap(":/fan.bmp"));
    ui->label_ball->setFixedSize(45, 45);
    ui->label_fan->setFixedSize(150,60);
    chart = new QChart();
    chart->setMargins(QMargins(0,0,0,0));
    chart->setBackgroundBrush(Qt::transparent);
    series = new QLineSeries();
    series->append(0, 0); series->append(1, 10); series->append(9, 4);
    series->setPen(QPen(Qt::green));
    chart->addSeries(series);
    chart->setTitle("height");
    chart->createDefaultAxes();
    chartView = new QChartView(chart, this);
    chartView->setGeometry(35,35,900,520);
    chartView->setContentsMargins(0, 0, 0, 0);
    chart->legend()->hide();
    chartView->setBackgroundBrush(Qt::darkGray);
}

PidRegulatorForm::~PidRegulatorForm()
{
    delete ui;
    delete timer;
    delete simulation, delete controller;
    delete series, delete chart, delete chartView;
    if (analis_window != nullptr) delete analis_window;
}

void PidRegulatorForm::get_k()
{
    k_P = ui->spinbox_p->text().toDouble() / 4;
    k_I = ui->spinbox_i->text().toDouble() / 100;
    k_D = ui->spinbox_d->text().toDouble() / 1000;
}

void PidRegulatorForm::pushbutton_clicked()
{
    if (!timer->isActive()) // timer->isActive()
    {
        ui->pushButton->setText("Stop");
        x = 0; sdx = 0;
        simulation->restart();
        series->clear();
        chart->axisX()->setRange(0, 10);
        get_k();
        controller->set_components(k_P, k_I, k_D);
        timer->start();
        ui->label_ball->setGeometry(ui->label_ball->x(), simulation->get_height(IN_PIXELS), 45, 45);
    }
    else
    {
        ui->pushButton->setText("START");
        timer->stop();
    }
}

void PidRegulatorForm::timer_tick()
{
    x += DX;
    (*simulation)(0, !WITH_CORRECTION);	//следующее состояние системы без учета воздействия импеллера
    if (on) rotation_speed = controller->get_result(simulation->convert_height(setpoint), simulation->get_height(IN_PIXELS)); //расчет управляющего значения
    (*simulation)(rotation_speed, WITH_CORRECTION); //состояние системы с учетом воздействия импеллера
    ui->horizontalSlider->setValue(rotation_speed);
    //сдвиг графика
    if ((sdx += DX) > 9)
    {
        chart->axisX()->setRange(x-9, x+1);
        series->remove(0);
    }
    series->append(x, simulation->get_height(!IN_PIXELS)); //рисуем график
    //draw image
    if (simulation->get_height(IN_PIXELS) > (PXLS_START_H - 0.0 * PXLS_IN_MTR))
    {
        ui->label_ball->setGeometry(ui->label_ball->x(), PXLS_START_H, 45, 45);
        timer->stop();
        ui->pushButton->setText("START");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание!"); msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("столкновение с поверхностью.");
        msgBox.setStyleSheet("QMessageBox, QLabel {background-color: 000000; color: ffffff;}");
        msgBox.exec();
    }
    else
        ui->label_ball->setGeometry(ui->label_ball->x(), simulation->get_height(IN_PIXELS), 45, 45);
}

void PidRegulatorForm::spinbox_p_value_changed()
{
    k_P = ui->spinbox_p->text().toDouble() / 4;
    controller->set_components(k_P, k_I, k_D);
}

void PidRegulatorForm::spinbox_i_value_changed()
{
    k_I = ui->spinbox_i->text().toDouble() / 100;
    controller->set_components(k_P, k_I, k_D);
}

void PidRegulatorForm::spinbox_d_value_changed()
{
    k_D = ui->spinbox_d->text().toDouble() / 1000;
    controller->set_components(k_P, k_I, k_D);
}

void PidRegulatorForm::verticalslider_position_changed()
{
    simulation->set_start_height(static_cast<float>(ui->verticalSlider->value()));
    ui->label_start_height->setText(QString::number(ui->verticalSlider->value()));
}

void PidRegulatorForm::verticalslider_2_position_changed()
{
    float value = static_cast<float>(ui->verticalSlider_2->value()) / 10.0f;
    //round
    ui->label_setpoint->setText(QString::number(value));
    setpoint = value;
}

void PidRegulatorForm::horizontalslider_position_changed()
{

    rotation_speed = ui->horizontalSlider->value();
    if (ui->label_rotation_speed->text() != QString::number(rotation_speed))
        ui->label_rotation_speed->setText(QString::number(rotation_speed));
}

void PidRegulatorForm::show_analis_window()
{
    if (analis_window == nullptr )
    {
        get_k();
        analis_window = new AccuracyForm(this, k_P, k_I, k_D, DX);
        analis_window->setGeometry(45,45,900,520);
        analis_window->show();
        chart->hide();
    }
    else
    {
        if(analis_window->isVisible())
        {
            analis_window->hide();
            chart->show();
        }
        else {
            analis_window->show();
            chart->hide();
        }
    }
}

void PidRegulatorForm::start_accuracy_analis()
{
    float start_height = static_cast<float>(ui->verticalSlider->value());
    analis_window->refresh_params(k_P, k_I, k_D, DX, start_height, setpoint); //актуализируем данные
    QThread* thread;
    analis_window->setGeometry(45,45,900,520);
    thread = QThread::create(&AccuracyForm::all, analis_window);
    connect(thread, SIGNAL(finished()), thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), analis_window, SLOT(button_analis_set_enabled()));
    connect(thread, SIGNAL(finished()), analis_window, SLOT(button_analis_set_enabled()));
    thread->start();
}

void PidRegulatorForm::pushbutton_switch_clicked()
{
    if (on)
    {
        on = false;
        ui->pushButton_switch->setStyleSheet("image: url(:/off.png); border-radius: 15px;");
        series->setPen(QPen(Qt::red));
    }
    else
    {
        on = true;
        ui->pushButton_switch->setStyleSheet("image: url(:/on.png); border-radius: 15px;");
        series->setPen(QPen(Qt::green));
    }
}

