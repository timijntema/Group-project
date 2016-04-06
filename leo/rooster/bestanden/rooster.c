
#include "bluetooth.c"
#include "roosterfuncties.c"
#pragma config(Sensor, S1,     color_sensor,   sensorColorNxtRED)
#pragma config(Sensor, S2,     light_sensor,   sensorLightActive)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Motor,  motorA,          motor_right,   tmotorNXT, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motor_left,    tmotorNXT, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(NXT)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//long nLastXmitTimeStamp = nPgmTime;
//long nDeltaTime = 0;

//const int kMaxSizeOfMessage = 30; //create a variable for the maximum message size
//const int INBOX = 5;

//variables for setting the minimum and maximum values of the light sensor and colorsensor
int maxcolor = 57;
int mincolor = 25;
int maxlight = 76;
int minlight = 40;

void speed_adjust(int index, int until, int increment) {
    /*
            This function is used for slowing down the motor slowly instead of stopping immediatly
     */
    for (int i = index; i >= until; i += increment) {
        setMultipleMotors(i, motorA, motorB);
        wait(0.09);
    }
}

task music() {
    //plays music while robot is in motion
    playSoundFile("Supermario.rmd");
    wait1Msec(10000);
}

void linefollow(void) {
    //using float variable for the sensors to have the most accurate
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
    nxtDisplayTextLine(3, "sonar: %d", sonar);

    // if an object is closer then 30 centimeters do the folowing
    if (sonar < 30) {
        speed_adjust(60, 0, -4); //slow down

        for (int i = 0; i < 10;) {//slowly start turning
            motor[motorA] = i;
            motor[motorB] = -i;
            wait(0.4);
            i++;
        }

        while (1) {//wait until you see the line
            if (SensorValue[S2] < 60) {
                for (int i = 10; i < 0;) {//slow down the turning speed
                    motor[motorA] = i;
                    motor[motorB] = -i;
                    wait(0.4);
                    i += 2;
                }
                break;
            }
        }
    }        //redirect the robot by using the light sensor
    else if (light < (maxlight - 5)) {
        // float variable for the formule math
        float formule;
        float omrek;
        float formule2;
        //omrek is used to can use the formules in every surroundings

        omrek = light - minlight;
        // show the result of the omrek on line 4
        nxtDisplayTextLine(4, "lomrek : %f", omrek);
        // if omrek is lower then 5 use 100 and 1 for a real sharp turn
        if (omrek < 5) {
            formule = 100;
            formule2 = 1;
        }// if the omrek is between 5 and 10 use a formule that gives a heavier control
        else if (omrek < 10) {
            formule = -0.4 * omrek + 100;
            formule2 = -1.428 * omrek + 50;
        }// the standaard formule for following the line
        else {
            formule = -0.9 * omrek + 100;
            formule2 = -1.428 * omrek + 50;
        }

        startTask(music); //starts the music
        // give the motor a and b the result of the formules
        motor(motorA) = formule; //50+((60-light)*2.5)
        motor(motorB) = formule2; //35  //0
    }        // redirecting the robot by using hte color sensor
    else if (color < (maxcolor - 5)) {//vorige waarde: 4
        // float variables for best accurate values
        float formule;
        float omrek;
        float formule2;
        //omrek is used to can use the formules in every surroundings
        omrek = color - mincolor;
        // show the result of the omrek on line 5
        nxtDisplayTextLine(5, "comrek : %d", omrek);
        // if omrek is lower then 5 use 100 and 1 for a real sharp turn
        if (omrek < 5) {
            formule = 100;
            formule2 = 1;
        }// if the omrek is between 5 and 10 use a formule that gives a heavier control
        else if (omrek < 10) {
            formule = -0.4 * omrek + 100;
            formule2 = -1.428 * omrek + 50;
        }// the standaard formule for following the line
        else {
            formule = -0.9 * omrek + 100;
            formule2 = -1.428 * omrek + 50;
        }

        startTask(music); //starts the music
        // give the motor a and b the result of the formules
        motor(motorA) = formule2; //0
        motor(motorB) = formule; //50+(50-color)*1+(2/3))
    } else {
        //if their isn't steering nessasary then both motors gets 50 as speed
        setMultipleMotors(50, motorA, motorB); //70 //100
    }
}

void junction(string *junction_string) {
    /*
            This code stops the robot at an intersection to make sure you can chose for it to go straight left or right.
            In case the direction is already chosen it just goes to the already chosen direction
     */

    if (SensorValue[S1] < (mincolor + 10) && SensorValue[S2] < (minlight + 10)) {//the minimul light value + 10 for the correct moment to stop at a line
        setMultipleMotors(50, motorA, motorB); //Drive the cart forward a little for 50 miliseconds. This way it ends up more straight on the line after turning
        wait1Msec(50);
        stopTask(music); //stops the music
        clearSounds(); //clears the sound buffer
        setMultipleMotors(0, motorA, motorB); //stop the robot
        wait(0.02);

        while (1) {
            if (*junction_string == "LEFT") {//if the input is "LEFT" turn left until you read the black line color and then continue your normal duty
                motor(motorA) = 0;
                motor(motorB) = 40;
                *junction_string = "";
                while (1) {
                    if (SensorValue[S1] < 40) {//color sensor check
                        wait1Msec(5);
                        setMultipleMotors(0, motorA, motorB);
                        break;
                    }
                }
                break;
            } else if (*junction_string == "RIGHT") {//the same only then for turning right
                motor(motorA) = 40;
                motor(motorB) = 0;
                *junction_string = "";
                while (1) {
                    if (SensorValue[S2] < 65) {//light sensor check
                        wait1Msec(5);
                        setMultipleMotors(0, motorA, motorB);
                        break;
                    }
                }
                break;
            }                //if up just stop the loop to exit
            else if (*junction_string == "UP") {
                setMultipleMotors(50, motorA, motorB);
                wait(0.2);
                break;
            }
            else if (*junction_string == "") {//When no input stop the robot
            	setMultipleMotors(0, motorA, motorB);
            	while(1){
              	//check_bluetooth(junction_string);
               	wait1Msec(100); //no need to do a continues check every 100 miliseconds is enough
                if (*junction_string != ""){
                	break;
                }
              }
            }
        }
    }
}

task main() {
    /*
            The main function contains just an infinite while loop that continues to call all the functions before mentioned. In the called
            functions we check for specific things like the line curving or a bleutooth input.
     */
    int stopcode2 = 0; //for stopping the while loop in case of a remote code shutdown

    startTask(music); //start the music in a seperate thread

    string s = ""; //create a string

    while (1) {
        //check_bluetooth(&s);
        if (s == "B") {//bluetooth override
            setMultipleMotors(0, motorA, motorB);
            stopcode2 = bluetooth_control(&s); //check for bleutooth input. This is the version of bleutooth input that takes over the robot
        }
        junction(&s); //check for an intersection
        linefollow(); //check if the line is curving and if not then just drive
        if (stopcode2 == 1) {//if "C" is pressed in the bleutooth_control function then stop the code completely
            return;
        }
    }
}
