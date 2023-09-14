#include "simulation.h"

float SIMULATION::fan_effeciency()
{
	float koef = 0;//коэффициент действия вентилятора в зависимости от расстояния до объекта
	//высота 0.5 - 2.5 метра
	if ((height > (PXLS_START_H - FAN_NO_EFFICIENCY_H * PXLS_IN_MTR)) && (height < (PXLS_START_H - FAN_MAX_EFFICIENCY_H * PXLS_IN_MTR))) 
		koef = (height - PXLS_START_H + FAN_NO_EFFICIENCY_H * PXLS_IN_MTR) / PXLS_IN_MTR / (FAN_NO_EFFICIENCY_H - FAN_MAX_EFFICIENCY_H);
	if (height > (PXLS_START_H - FAN_MAX_EFFICIENCY_H * PXLS_IN_MTR)) //высота меньше 0.5м
		koef = 1.0f;
	return koef;
}

SIMULATION::SIMULATION(float new_start_height, float new_dx)
{
	dx = new_dx;
	speed = start_speed = 0;
	height = start_height = convert_height(new_start_height);

}

float SIMULATION::set_start_height(float new_start_height)
{
	start_height = convert_height(new_start_height);
	return start_height;
}

float SIMULATION::convert_height(float height_in_meters)
{
	float height_in_pxls = PXLS_START_H - height_in_meters * PXLS_IN_MTR;
	return height_in_pxls;
}

float SIMULATION::operator()(int power, bool _with_correction)
{
	if (!_with_correction) {
		start_speed += G * PXLS_IN_MTR * dx;
		height += (start_speed + G * PXLS_IN_MTR * dx / 2) * dx;
	}
	else {
		float correction = fan_effeciency() * G * PXLS_IN_MTR * power / HOWER_P * dx;
		start_speed -= correction;
		height -= (correction + correction * dx / 2) * dx;
	}
	return height;
}

float SIMULATION::get_height(bool _in_pixels)
{
	if (_in_pixels)
		return height;
	return (PXLS_START_H-height)/ PXLS_IN_MTR;
}

void SIMULATION::restart()
{
	speed = start_speed = 0;
	height = start_height;
}
