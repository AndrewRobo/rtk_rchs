#pragma config(Sensor, S1,     ,               sensorLightActive)
#pragma config(Sensor, S3,     ,               sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     ,               sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#pragma DebuggerWindows("joystickSimple")
int err, u, sens1, sens2;
	float k=20;



void down()
{
	nMotorEncoder[motorC]=0;
	while(nMotorEncoder[motorC] > -420)
{
	motor[motorC]=-20;
	sleep(1);
}
motor[motorC]=0;
}

void up()
{
	nMotorEncoder[motorC]=0;
	while(nMotorEncoder[motorC] < 420)
{
	motor[motorC]=20;
	sleep(1);
}
motor[motorC]=0;
}




void detected()
{
	motor[motorA]=0;
  motor[motorD]=0;

 nMotorEncoder[motorA]=0;

 while(nMotorEncoder[motorA] > -200)
  {
  	motor[motorA]=-20;
  	motor[motorD]=-20;
  	sleep(1);
  }

	motor[motorA]=0;
  motor[motorD]=0;

  up();
  }



void line()
{
		sens1=SensorValue[S1];
		sens2=SensorValue[S4];
   	err=sens1-sens2;
   	u=err*k;
		motor[motorD]=-70+u;
		motor[motorA]=-70-u;

  	sleep(1);

}



task main()
{


	while (true)
	{
 	 getJoystickSettings(joystick);
 	 //if (SensorValue[S2] < 13) detected();
 	 motor[motorA] = joystick.joy1_y1;
 	 motor[motorD] = joystick.joy1_y2;
	//if(joy1Btn(Btn5) == 1)
 	 if(joy1Btn(Btn4) == 1)
 	 {
 	   up();
 	 }
 	 else if(joy1Btn(Btn2) == 1)
 	 {
 	   down();
 	 }
 	 else {motor[motorC]=0;}
	/*if(joy1Btn(Btn2) == 1)
 	 {
 	  k=-1;
 	 }
 	 else if(joy1Btn(Btn3) == 1)
 	 {
 	   k=1;
 	 }*/
		if (joy1Btn(Btn10)==1)  //btn start
		{
			while(joy1Btn(Btn9) != 1)
				{ getJoystickSettings(joystick);
					line();
					if(SensorValue[S3] < 4)
								{  detected();
									break;
             		}
				}
		}
	displayCenteredBigTextLine(5, "%f", getBatteryVoltage());
 	 sleep(1);
	}
}
