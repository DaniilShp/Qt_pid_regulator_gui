#include "accuracy.h"

#include "simulation.h"
#include "PID.h"

#include <QThread>
#include <iostream>

Accuracy::Accuracy(float _k_P, float _k_I, float _k_D, float _dx, float _start_height, float _setpoint)
{
    start_height = _start_height;
    setpoint = _setpoint;
    k_P = _k_P; k_I = _k_I; k_D = _k_D; dx = _dx;
}

void Accuracy::refresh_params(float _k_P, float _k_I, float _k_D, float _dx, float _start_height, float _setpoint)
{
    k_P = _k_P; k_I = _k_I; k_D = _k_D; dx = _dx;
    start_height = _start_height;
    setpoint = _setpoint;
}

int Accuracy::run()
{
    int rotation_speed;
    PID test_controller(k_P, k_I, k_D, DX);
    SIMULATION simulation(start_height, DX);
    int i = 0; float x = 0.0f;
    for(x = 0; x < 4.0f; x+=DX)
    {
        simulation(0, !WITH_CORRECTION);	//следующее состояние системы без учета воздействия импеллера
        rotation_speed = test_controller.get_result(simulation.convert_height(setpoint), simulation.get_height(IN_PIXELS)); //расчет управляющего значения
        simulation(rotation_speed, WITH_CORRECTION); //состояние системы с учетом воздействия импеллера
        if (x > 1.0f)
        {
            if (simulation.get_height(!IN_PIXELS) < setpoint+0.1f && simulation.get_height(!IN_PIXELS) > setpoint-0.1f)
                i++; //count points in confidence interval
        }
        //draw image
        if (simulation.get_height(IN_PIXELS) > (PXLS_START_H - 0.0 * PXLS_IN_MTR+1))
        {
            //std::cout << "P: " << k_P << " I: " << k_I << " D: " << k_D << " crashed" << std::endl;
            return 0;
        }
    }
    //std::cout << "P: " << k_P << " I: " << k_I << " D: " << k_D << " average y " << static_cast<float>(sumy / i) << " points in good interval " << i << std::endl;
    return i;
}

int Accuracy::all(Accuracy* ptr)
{
    int max = 0;
    int kp, ki, kd;
    for(int p = 0; p < 100; p++)
    {
            for(int d = 0; d < 100; d+=1)
            {
            Accuracy obj(static_cast<float>(p)/4, 0.0f, static_cast<float>(d)/1000, DX, ptr->start_height, ptr->setpoint);
                int points = obj.run();
                if (points>max) {
                    max = points;
                    kp = p; ki=0;kd=d;
                }
            }
    }
    std::cout << "finished\n";
    std::cout << max << " " << kp << " " << ki << " " << kd << " " << ptr->start_height << " " << ptr->setpoint << std::endl;
    Accuracy obj(static_cast<float>(ptr->k_P)/4, static_cast<float>(ptr->k_I)/100, static_cast<float>(ptr->k_D)/1000, ptr->dx, ptr->start_height, ptr->setpoint);
    return 0;
}
