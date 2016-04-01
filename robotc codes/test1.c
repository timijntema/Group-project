#pragma config(Sensor, S1,     color_sensor,   sensorColorNxtRED)
#pragma config(Sensor, S2,     light_sensor,   sensorLightActive)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Motor,  motorA,          motor_right,   tmotorNXT, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motor_left,    tmotorNXT, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(NXT)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

long nLastXmitTimeStamp = nPgmTime;
long nDeltaTime         = 0;

const int kMaxSizeOfMessage = 30;//create a variable for the maximum message size
const int INBOX = 5;

void speed_adjust(int index, int until, int increment, int what_motor){
	/*
		what_motor = 0 == both
		what_motor = 1 == right increment
		what_motor = 2 == left increment
	*/
	if (what_motor == 0){
		for (int i = index; i >= until; i+=increment){
			setMultipleMotors(i, motorA, motorB);
			wait(0.1);//0.1
		}
	}
	else if (what_motor == 1){
		//adjust right motor
	}
	else if (what_motor == 2){
		//adjust left motor
	}
	//setMultipleMotors(0, motorA, motorB);
}

void check_bleutooth(string *s){
	/*
		This function makes a bleutooth connection and then waits for input from the connected phone
	*/
	TFileIOResult nBTCmdRdErrorStatus;
  int nSizeOfMessage;
  ubyte nRcvBuffer[kMaxSizeOfMessage];

	while(1){
		//wait on bleutooth
		 nSizeOfMessage = cCmdMessageGetSize(INBOX);

    if (nSizeOfMessage > kMaxSizeOfMessage){//make the message shorter if its to long
      nSizeOfMessage = kMaxSizeOfMessage;
    }

    if (nSizeOfMessage > 0){//if the message is not empty, put the received information in string s
    	nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, INBOX);
    	nRcvBuffer[nSizeOfMessage] = '\0';
    	stringFromChars(*s, (char *) nRcvBuffer);
    	displayCenteredBigTextLine(4, *s);
    	break;
    }

    wait1Msec(100);//no need to do a continues check every 100 miliseconds is enough
	}
}

void need_for_speed(void){
	//using float variable for the sensors to have the most 	accurate
	float color;
	float light;
	float sonar;
	// reading the sensor value
	light = SensorValue[S2];
	color = SensorValue[S1];
	sonar = SensorValue[S3];
	// displaying the values from above
	nxtDisplayTextLine(1, "color: %d", color);
	nxtDisplayTextLine(2, "light: %d", light);
	nxtDisplayTextLine(3, "sonar: %d", sonar );
	// if an object is less than 15 centimeters the top
	if(sonar <35) {
		//setMultipleMotors(0,motorA,motorB);
		speed_adjust(60, 0, -3, 0);
		string s = "";
		//check_bleutooth(&s);//laten omdraaien moet nog
		for (int i = 0; i < 10; i++){
			motor[motorA] = i;
			motor[motorB] = -i;//draait rechtsom
			wait(0.4);
		}
		while (SensorValue[S2] > 60);//motor b rechterkant// licht eerst
		for (int i = 10; i > 0; i--){
			motor[motorA] = i;
			motor[motorB] = -i;//draait rechtsom
			wait(0.4);
		}
	}
	//redirect the robot by using the light sensor
	else if (light < 65){
		float formule;
		float omrek;
		float maal = 0;

		omrek = 65-light;
		formule = (65+(omrek)*(1+(2/3)));
		nxtDisplayTextLine(4, "omrekrechts: %d", omrek );

		if (omrek< 10){
			maal =1.2;
		}
		else if(omrek>25){
			maal = 2 +((omrek-25)*0.1);
		}
		else {
			(maal = 1.2+(omrek-10)*0.055);
		}

		motor(motorA) = formule;//50+((60-light)*2.5)
		motor(motorB) =45-(omrek*maal);//35  //0
	}
	// redirecting the robot by using hte color sensor
	else if(color < 48) {//vorige waarde: 4
		// float variables for best accurate values
		float formule;
		float omrek;
		float maal =0;

		omrek = 48-color;
		formule = (65+(omrek)*(1+(2/3)));
		nxtDisplayTextLine(5, "omreklinks: %d", omrek );

		if (omrek< 10){
			maal = 1.2;
		}
		else if(omrek>25){
			maal = 2 + ((omrek - 25)*0.1);
		}
		else{
			maal=(1.2+(omrek-10)*0.055);
		}

		motor(motorA) = 45-(omrek*maal);//0
		motor(motorB) =formule ;//50+(50-color)*1+(2/3))
	}
	else {
		setMultipleMotors(65,motorA,motorB);//70 //100
	}
}

//a block of discontinued code kept because it was working but not smoothly
/*void need_for_speed(int begin_value_s1, int begin_value_s2){
	float color;
	float  light;
	int sonar;

	light = SensorValue[S2];
	color = SensorValue[S1];
	sonar = SensorValue[S3];
	nxtDisplayTextLine(1, "color: %d", color);
	nxtDisplayTextLine(2, "light: %d", light);
	nxtDisplayTextLine(3, "sonar: %d", sonar );

	if(sonar <15) {
		setMultipleMotors(0,motorA,motorB);
		string s = "";
		check_bleutooth(&s);
	}
	else if (light < 60){
		motor(motorA) = (60+((60-light)*2));//50+((60-light)*2.5)
		motor(motorB) = 0;//35  //0
	}
	else if(color < 45) {//vorige waarde: 4
		motor(motorA) = 0;//0
		motor(motorB) = (50+(50-color)*(1+(2/3)));//50+(50-color)*1+(2/3))
	}
	else {
		setMultipleMotors(80,motorA,motorB);//70 //100
	}
}*/



int bleutooth_control(void){
	/*
		This code is for taking over the robot completely using bleutooth to make sure you can stop de robot in case its needed.
		pressing the middle button ("FIRE") on the phone stops the robot due to it not being included in the code here for another function.
	*/
	TFileIOResult nBTCmdRdErrorStatus;
  int nSizeOfMessage;
  ubyte nRcvBuffer[kMaxSizeOfMessage];
  int stopcode = 0;

  nSizeOfMessage = cCmdMessageGetSize(INBOX);

	if (nSizeOfMessage > kMaxSizeOfMessage){
      nSizeOfMessage = kMaxSizeOfMessage;
 	}

	if (nSizeOfMessage > 0){//Only if an actual message is being received the bleutooth take over system should activate
    	nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, INBOX);
    	nRcvBuffer[nSizeOfMessage] = '\0';

    	string s = "";
    	stringFromChars(s, (char *) nRcvBuffer);
    	displayCenteredBigTextLine(4, s);

    	while (s != "A"){//if A is pressed the robot will resume its duty the normal way
    		nSizeOfMessage = cCmdMessageGetSize(INBOX);//misschien onderaan
    		if (nSizeOfMessage > kMaxSizeOfMessage){
      		nSizeOfMessage = kMaxSizeOfMessage;
 				}
 				if (nSizeOfMessage > 0){
		    	nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, INBOX);
		    	nRcvBuffer[nSizeOfMessage] = '\0';

		    	s = "";
		    	stringFromChars(s, (char *) nRcvBuffer);
		    	displayCenteredBigTextLine(4, s);
		  	}
				//The next 4 if statements are for controlling the robot manually
    		if(s == "LEFT"){//if bleutooth input is left turn left
    			motor(motorA) = 0;
    			motor(motorB) = 30;
    		}
    		else if(s == "RIGHT"){//if bleutooth input is right turn right
    			motor(motorA) = 30;
    			motor(motorB) = 0;
    		}
    		else if (s == "UP"){//if bleutooth input is up drive forward
    			setMultipleMotors(50, motorB, motorA);
    		}
    		else if (s == "DOWN"){//if bleutooth input is down drive backwards
    			setMultipleMotors(-50, motorB, motorA);
    		}
    		/*else {//hier
    			setMultipleMotors(0, motorA, motorB);
    		}*/
    		if (s == "C"){//if the C button is pressed the loop stops and the stopcode == 1 to stop de code if neccesairy
    			stopcode = 1;
    			break;
    		}
    	}
   }
   return stopcode;//either 1 or 0 depending on the "C" button being pressed or not
}

//discontinued working code that we keep to make sure we can go back to it if needed. A newer version exists.
/*
void junction(){

	string s = "";
	if (SensorValue[S1] < 38 && SensorValue[S2] < 50){
		setMultipleMotors(90, motorA, motorB);f
		wait1Msec(40);
		setMultipleMotors(0, motorA, motorB);
		check_bleutooth(&s);
		if(s == "LEFT"){
			motor(motorA) = 0;
  		motor(motorB) = 40;
  		while(1){
  			if (SensorValue[S1] < 40){//color
  				setMultipleMotors(0, motorA, motorB);
  				break;
  			}
  		}
  	}
  	else if(s == "RIGHT"){
  		motor(motorA) = 40;
  		motor(motorB) = 0;
  		while(1){
  			if (SensorValue[S2] < 60){//light
  				setMultipleMotors(0, motorA, motorB);
  				break;
  			}
  		}
  	}
  	else if(s == "UP"){
    	setMultipleMotors(40, motorA,motorB);
    	wait10Msec(10);
		}
	}
}
*/

void junction(string* junction_string){
	/*
		This code stops the robot at an intersection to make sure you can chose for it to go straight left or right.
	*/
	//string s = "";
	if (SensorValue[S1] < 38 && SensorValue[S2] < 50){
		setMultipleMotors(90, motorA, motorB);//Drive the cart forward a little for 40 miliseconds. This way it ends up more straight on the line after turning
		wait1Msec(40);
		setMultipleMotors(0, motorA, motorB);//stop the robot
		//check_bleutooth(&s);//wait for bleutooth input

		if(*junction_string == "LEFT"){//if the input is "LEFT" turn left until you read the black line color and then continue your normal duty
			motor(motorA) = 0;
			motor(motorB) = 40;
			*junction_string = "";
			while(1){
				if (SensorValue[S1] < 40){//color sensor check
					setMultipleMotors(0, motorA, motorB);
					break;
				}
			}
		}
		else if(*junction_string == "RIGHT"){//the same only then for turning right
			motor(motorA) = 40;
			motor(motorB) = 0;
			*junction_string = "";
			while(1){
				if (SensorValue[S2] < 60){//light sensor check
					setMultipleMotors(0, motorA, motorB);
					break;
				}
			}
		}
		//For going forward no if statement is needed because the robot wil just continue driving after te bleutooth input
		/*else if(s == "UP"){
		}*/
	}
}

task music(){
	/*
		The folowing function plays a number of tones to create some sound that lets people know there is a electric car coming.
		Due to electric cars being very quiet this is needed to prevent accidents.
	*/
	playTone(695, 14);
	playTone(695, 14);
	playTone(695, 14);
	playTone(929, 83);
	playTone(1401, 83);
	playTone(1251, 14);
	playTone(1188, 14);
	playTone(1054, 14);
	playTone(1841, 83);
	playTone(1401, 41);
	playTone(1251, 14);
	playTone(1188, 14);
	playTone(1054, 14);
	playTone(1841, 83);
	playTone(1401, 41);
	playTone(1251, 14);
	playTone(1188, 14);
	playTone(1251, 14);
	playTone(1054, 55);
	wait1Msec(280);
	playTone(695, 14);
	playTone(695, 14);
	playTone(695, 14);
	playTone(929, 83);
	playTone(1401, 83);
	playTone(1251, 14);
	playTone(1188, 14);
	playTone(1054, 14);
	playTone(1841, 83);
	playTone(1401, 41);
	playTone(1251, 14);
	playTone(1188, 14);
	playTone(1054, 14);
	playTone(1841, 83);
	playTone(1401, 41);
	playTone(1251, 14);
	playTone(1188, 14);
	playTone(1054, 55);
}

task main()
{
	/*
		The main function contains just an infinite while loop that continues to call all the functions before mentioned. In the called
		functions we check for specific things like the line curving or a bleutooth input.
	*/

	//read the beginvalues of the light sensors
	/*int begin_value_s1 = SensorValue[S1];
	int begin_value_s2 = SensorValue[S2];*/

	//delayed startup nog maken
	/*for (int i = 0; i< 100; i+=5){
		setMultipleMotors(i, motorA, motorB);
		wait(0.1);
	}*/

	int stopcode2 = 0;//for stopping the while loop in case of a remote code shutdown

	startTask (music);//start music as a different task to make sure it runs at the same time as the main task

	string s = "";
	TFileIOResult nBTCmdRdErrorStatus;
  int nSizeOfMessage;
  ubyte nRcvBuffer[kMaxSizeOfMessage];

	while(1){
		//wait on bleutooth
		 nSizeOfMessage = cCmdMessageGetSize(INBOX);

    if (nSizeOfMessage > kMaxSizeOfMessage){//make the message shorter if its to long
      nSizeOfMessage = kMaxSizeOfMessage;
    }

    if (nSizeOfMessage > 0){//if the message is not empty, put the received information in string s
    	nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, INBOX);
    	nRcvBuffer[nSizeOfMessage] = '\0';
    	stringFromChars(s, (char *) nRcvBuffer);
    	displayCenteredBigTextLine(4, s);
    }
    if (s == "B"){
    	setMultipleMotors(0, motorA, motorB);
			stopcode2 = bleutooth_control();//check for bleutooth input. This is the version of bleutooth input that takes over the robot
		}
		junction(&s);//check for an intersection
		need_for_speed();//check if the line is curving and if not then just drive
		if(stopcode2 == 1){//if "C" is pressed in the bleutooth_control function then stop the code completely
			return;
		}
	}
}
