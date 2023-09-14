#pragma once

#define NORMAL 0
#define REVERSE 1

class PID {
private:
    float Kp = 0.0f;				// коэффициент P
    float Ki = 0.0f;				// коэффициент I
    float Kd = 0.0f;				// коэффициент D	
    float integral = 0.0f;		// интегральная сумма
    float dt_s = 0.02f;		// время итерации в с
    bool direction = 1;
    int min_out = 0, max_out = 120;
    float prevSensorSignal = 0.0f;
    float old_error = 0.0f;
public:
    PID() {};
    // kp, ki, kd, dt
    PID(float new_kp, float new_ki, float new_kd, float new_dt);
    void set_components(float new_kp, float new_ki, float new_kd);
    void set_direction(bool direction);
    void set_dt(float new_dt);
    void set_limits(int min_output, int max_output);
    void restart();
    float get_result(float setpoint, float signal);
};
