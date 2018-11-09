#include "GPSModule.h"
#include "GPSQueue.h"
#include "IMU.h"
#include "LocalizationSetup.h"

void setup() {
    localizationSetup();
}

void intellectualWait(unsigned long ms) {
    unsigned long startTime = millis();
    while (millis() - startTime < ms) {
        gps.update();
        imu0.update();
    }
}

void loop() {

  if (imu0.calibrated()) {

    Serial.print("Distance, Heading: ");
    Serial.print(queue.getDistToCur());
    Serial.print(", ");
    Serial.println(queue.getCurHeading());

    Serial.print("Orient x, y, z: ");
    Serial.print(imu0.getOrientX());
    Serial.print(", ");
    Serial.print(imu0.getOrientY());
    Serial.print(", ");
    Serial.println(imu0.getOrientZ());

    imu::Vector<3> accel = imu0.getAccel();

    Serial.print("Accel x, y, z: ");
    Serial.print(accel.x());
    Serial.print(", ");
    Serial.print(accel.y());
    Serial.print(", ");
    Serial.println(accel.z());
  }
    
    intellectualWait(500);
}
