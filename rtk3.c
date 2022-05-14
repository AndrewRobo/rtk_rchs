#pragma config(Sensor, S1,     ,               sensorLightActive)
#pragma config(Sensor, S4,     ,               sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#pragma DebuggerWindows("joystickSimple")
int err,
		u,
		sens1,
		sens2,
    grey=22,
    grey1=38,
    tim=0,
		vline=5,
		flag=0;

float k=1;

void linezig2()
{
		flag=0;
		sens1=SensorValue[S4];
		//sens2=SensorValue[S4];
   	err=sens1-grey1;
   	u=err*k;
		motor[motorD]=-vline-u;
		motor[motorA]=-vline+u;
		if(u > 30 && tim==0)
		{
			tim=nPgmTime;
		}
		else if(u<=30)
		{
			tim=nPgmTime;
		}
		else if(nPgmTime - tim >= 1000)
		{
			flag=0;
		}
		sleep(1);
}

void linezig1()
{
		flag=0;
		sens1=SensorValue[S1];
		//sens2=SensorValue[S4];
   	err=sens1-grey1;
   	u=err*k;
		motor[motorD]=-vline+u;
		motor[motorA]=-vline-u;
		if(u > 30 && tim==0)
		{
			tim=nPgmTime;
		}
		else if(u<=30)
		{
			tim=nPgmTime;
		}
		else if(nPgmTime - tim >= 1000)
		{
			flag=1;
		}
		sleep(1);
}



void down()
{
	nMotorEncoder[motorC]=0;
	while(nMotorEncoder[motorC] > -400)
{
	motor[motorC]=-20;
	sleep(1);
}
motor[motorC]=0;
}


void downline()
{
	nMotorEncoder[motorC]=0;
	while(nMotorEncoder[motorC] > -150)
{
	motor[motorC]=-20;
	sleep(1);
}
motor[motorC]=0;
}

void up()
{
	nMotorEncoder[motorC]=0;
	while(nMotorEncoder[motorC] < 400)
{
	motor[motorC]=20;
	sleep(1);
}
motor[motorC]=0;
}

void upline()
{
	nMotorEncoder[motorC]=0;
	while(nMotorEncoder[motorC] < 200)
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


  	motor[motorA]=-1;
  	motor[motorD]=-1;
  	sleep(700);
	motor[motorA]=0;
  motor[motorD]=0;
sleep(300);
  up();
  motor[motorA]=-5;
  motor[motorD]=-5;
  sleep(1300);
  motor[motorA]=0;
  motor[motorD]=0;
  sleep(1700);
  down();
  upline();
  }

void line()
{
		flag=0;
		sens1=SensorValue[S1];
		sens2=SensorValue[S4];
   	err=sens1-sens2;
   	u=err*k;
		motor[motorD]=-vline+u;
		motor[motorA]=-vline-u;
		sleep(1);
}

void lineforw()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(SensorValue[S2] <= grey+1 && SensorValue[S2] >= grey-1)
   {
     motor[motorA]=10;
     motor[motorD]=10;
   }
   else if(SensorValue[S2] < grey)
   {
     motor[motorA]=10;
     motor[motorD]=0;
   }
   else if(SensorValue[S2] > grey)
   {
     motor[motorA]=0;
     motor[motorD]=10;
   }
   sleep(1);}
}

void tocross()
{
	while(true){if(SensorValue[S1] < 27 && SensorValue[S4] < 27)break;
		line();
		sleep(1);
	}
	motor[motorA]=0;
	motor[motorD]=0;
	playTone(784, 50);
	motor[motorA]=0;
	motor[motorD]=0;
	nMotorEncoder[motorA]=0;
	motor[motorA]=5;
	motor[motorD]=5;
	sleep(500);
	motor[motorA]=0;
	motor[motorD]=0;
	downline();
}

task main()
{


	while (true)
	{
 	 getJoystickSettings(joystick);
 	 //if (SensorValue[S2] < 13) detected();
 	 if (abs(joystick.joy1_y1) < 5){motor[motorA]=0;}
 	 else {motor[motorA] = joystick.joy1_y1;}
 	 if(abs(joystick.joy1_y2) < 5){motor[motorD]=0;}
 	 else {motor[motorD] = joystick.joy1_y2;}
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
		if (joy1Btn(Btn10)==1)  //btn start
		{ down();
			while(joy1Btn(Btn9) != 1)
				{ getJoystickSettings(joystick);
					line();
					if(SensorValue[S3] < 5)   //s3
								{  detected(); /*tim=nPgmTime; while(nPgmTime-tim<=700)*/{line();}
									 tocross();   break;
       		}
				}
		}
		if(joy1Btn(Btn6) == 1)
		{
			lineforw();
		}
	displayCenteredBigTextLine(5, "%f", getBatteryVoltage());
 	 sleep(1);
	}
}