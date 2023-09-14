#include "PID.h"

PID::PID(float new_kp, float new_ki, float new_kd, float new_dt_s)
{
    dt_s = new_dt_s;
    set_components(new_kp, new_ki, new_kd);
    restart();
}

void PID::set_components(float new_kp, float new_ki, float new_kd)
{
    Kp = new_kp;
    Ki = new_ki;
    Kd = new_kd;
    restart();
}
// направление регулировани€: NORMAL (0) или REVERSE (1)
void PID::set_direction(bool new_direction)
{
    direction = new_direction;
}

// установка времени квантовани€
void PID::set_dt(float new_dt) {
    dt_s = new_dt;
}
// лимит выходной величины
void PID::set_limits(int min_output, int max_output) {
    min_out = min_output;
    max_out = max_output;
}

void PID::restart()
{
    integral = 0;
    prevSensorSignal = 0;
    old_error = 0;
}

float PID::get_result(float setpoint, float sensor_signal) {
    float output;
    float error = setpoint - sensor_signal;			// ошибка регулировани€
    float delta_error = old_error - error;
    float delta_signal = prevSensorSignal - sensor_signal;	// изменение входного сигнала за dt
    prevSensorSignal = sensor_signal;							// запомнили предыдущее
    if (direction) {							// смена направлени€
        error = -error;
        delta_signal = -delta_signal;
        delta_error = -delta_error;
    }
    output = error * Kp; 			// пропорциональа€ составл€юща€
    output += delta_error * Kd / dt_s;			// дифференциальна€ составл€юща€
    old_error = error;
    integral += error * Ki * dt_s;				// обычное суммирование инт. суммы

    output += integral;									// интегральна€ составл€юща€
    if (output > max_out)		                        // ограничиваем выход
        output = max_out;
    if (output < min_out)
        output = min_out;

    return output;
}