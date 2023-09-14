#ifndef ACCURACY_H
#define ACCURACY_H

#include <QPoint>

class Accuracy
{
protected:
    float dx;
    float k_P, k_I, k_D;
    float start_height, setpoint;
public:
    Accuracy(float k_P, float k_I, float k_D, float dx, float start_height, float setpoint);
    int run();
    static int all(Accuracy*);
    void refresh_params(float k_P, float k_I, float k_D, float dx, float start_height, float setpoint);
};

#endif // ACCURACY_H
