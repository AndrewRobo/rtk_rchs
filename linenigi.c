
task main()
{

	int err, u, sens1, sens2;
	float k=20;
	int diff=SensorValue[S1]-SensorValue[S4];
	sleep(5000);
	while(true)
	{
		sens1=SensorValue[S1];
		sens2=SensorValue[S4];
   	err=sens1-sens2;
   	u=err*k;
		motor[motorD]=-100+u;
		motor[motorA]=-100-u;
  	sleep(1);
	}
























	}
