#ifndef MOTION_LOOP_H
#define MOTION_LOOP_H

#include "MotionSetup.h"

//General state constants
#define IDLE 0

//Servo state constants
#define SERVO_UPDATE 1
#define SERVO_MOVE 2

//State tracking variables
int servoState = IDLE;

//General Timing variables
unsigned long currentTime;

//Drivetrain timing variables
unsigned long lastDrivetrainUpdate;

//Servo timing variables
unsigned long servoTime = 0;
unsigned long lastServoUpdate = 0;

//Declare system loops
void drivetrainLoop(float power);
void servoLoop(float servoAngle);

void motionLoop()
{
    /* TIME UPADTE */
    currentTime = millis();

    //Check if we're near the next cone
	if (curData.nearCone)
	{
		/* DRIVETRAIN UPADTE */
		drivetrainLoop(DEFAULT_POWER / 2);

			if (curData.canSeeCone)
			{
				//We can see the cone
				if (curData.opencv_error > (0 + OPENCV_ALLOWED_ERROR))
				{
					//I'm not sure what data opencv_error contains but this should probably be not 10 and some sort of open cv calculation
					servoLoop(-10);
				}
				else if (curData.opencv_error < (0 - OPENCV_ALLOWED_ERROR))
				{
					servoLoop(10);
				}
				else
				{
					servoLoop(0);
				}
			}
			else
			{
				//We have passed the cone and should turn around, Justin has a more complicated
				// algorithmic idea for this, until then hopefully 
				// turning 45 degrees we can see the cone again in a cycle or two
				servoLoop(45);
			}
	}
    else
    {
        /* DRIVETRAIN UPADTE */
        drivetrainLoop(DEFAULT_POWER);

        float diff = curData.curHeading - curData.destHeading;

        float LHT = (diff) < 0 ? diff + 360 : diff; //Degrees required to move to heading turning left


        /* SERVO UPDATE */
        if (LHT < (-LHT + 360) - DEGREES_OFF_ALLOWED)        // Faster to head left
        {
            servoLoop(-10);
        }
        else if (LHT > (-LHT + 360) - DEGREES_OFF_ALLOWED)   // Faster to head right
        {
            servoLoop(10);
        }
        else                                        // On target
        {
            servoLoop(0);
        }
    }
}

/**********************
    SYSTEM LOOPS
**********************/
void drivetrainLoop(float power)
{
    if (curData.curHeading == 0 && curData.destHeading == 0)
    {
        drivetrain.setPower(0);
        drivetrain.setTurn(0);
        return;
    }

    drivetrain.setPower(power);
}

void servoLoop(float servoAngle)
{
    switch (servoState)
    {
    case IDLE:
        //Keep current position
        drivetrain.holdTurnPosition();

        //Check to see if the servo needs to move
        if (abs(drivetrain.getTurnAngle() - servoAngle) > TURN_TOLERANCE)
        {
            servoState = SERVO_UPDATE;
        }

        break;

    case SERVO_UPDATE:
    case SERVO_MOVE:
        //Start the timer for servo timeouts.
        if (servoState == SERVO_UPDATE)
        {
            servoTime = millis();
            servoState = SERVO_MOVE;
        }

        //Set the servo turn angle
        drivetrain.setTurn(servoAngle);

        //Turn off the servo after an amount of time has passed
        if ((millis() - servoTime) > SERVO_MOVE_TIMEOUT || abs(drivetrain.getTurnAngle() - servoAngle) <= TURN_TOLERANCE)
        {
            servoState = IDLE;
            drivetrain.holdTurnPosition();
        }

        break;

    default:
        servoState = IDLE;
        break;
    }
}


#endif