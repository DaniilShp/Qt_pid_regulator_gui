#pragma once
#define START_H 5
#define DX 0.05f
#define FAN_MAX_EFFICIENCY_H 0.5f
#define FAN_NO_EFFICIENCY_H 2.5f
#define PXLS_IN_MTR 175
#define G 10
#define PXLS_START_H 445
#define HOWER_P 10
#define IN_PIXELS true
#define WITH_CORRECTION true

class SIMULATION
{
private:
	float dx;
	float start_speed;
	float speed;
	float height;
	float start_height;
	int min_power = 0, max_power = 110;
	float fan_effeciency();
public:
	SIMULATION(float start_height, float dx);
	float set_start_height(float start_height);
	float get_height(bool in_pixels);
	float operator() (int power, bool with_correction);
	void restart();
	float convert_height(float height_in_meters);
};

