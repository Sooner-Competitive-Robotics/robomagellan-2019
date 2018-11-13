#ifndef IMU_H
#define IMU_H

//https://github.com/adafruit/Adafruit_BNO055
#include <IMU_BNO055.h>


//Code for using the BN055 GPS
/* This class doesn't automatically pull new data from sensor 
   for get X,Y,Z to ensure they are synced. To read the current 
   data into what XYZ pull from call read*/
class IMU {
public:
	void begin();
	bool connected();

	bool calibrated();

	float getOrientX();
	float getOrientY();
	float getOrientZ();
	float getAccelX();
	float getAccelY();
	float getAccelZ();

	void update();
private:
	IMU_BNO055 bno;
	scr_sensors_event_t orientation; //the current orinetation
	scr_sensors_event_t acceleration; //the current acceleration
	scr_sensors_event_t prev_acceleration; //the acceleration one time step back

	void calibrate();
};
#endif
