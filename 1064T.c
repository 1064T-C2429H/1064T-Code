#pragma config(Sensor, dgtl1,  ledTank,        sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  ledArcade,      sensorLEDtoVCC)
#pragma config(Motor,  port1,           leftFront,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightFront,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightBack,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           YRightLift,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RightLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           YLeftLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LeftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           ClawLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          ClawRight,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

void pre_auton(){
}

void driveTank(int joyLeft, int joyRight){ // drive Tank code
	motor[leftFront] = vexRT[Ch3];
	motor[rightFront] = vexRT[Ch2];
	motor[leftBack] = vexRT[Ch3];
	motor[rightBack] = vexRT[Ch2];
}

void driveArcade(int joy){
	motor[leftFront] = joy;
	motor[rightFront] = joy;
	motor[leftBack] = joy;
	motor[rightBack] = joy;
}

void driveForward(float time){ //TODO: PID LOOP
	motor[leftFront] = 127;
	motor[rightFront] = 127;
	motor[leftBack] = 127;
	motor[rightBack] = 127;
	wait1Msec(time);
	motor[leftFront] = 0;
	motor[rightFront] = 0;
	motor[leftBack] = 0;
	motor[rightBack] = 0;
}

void driveBackward(float time){ //TODO: PID LOOP
	motor[leftFront] = -127;
	motor[rightFront] = -127;
	motor[leftBack] = -127;
	motor[rightBack] = -127;
	wait1Msec(time);
	motor[leftFront] = 0;
	motor[rightFront] = 0;
	motor[leftBack] = 0;
	motor[rightBack] = 0;
}

void lift(int power){
	motor[YRightLift] = power;
	motor[RightLift] = power;
	motor[YLeftLift] = -power;
	motor[LeftLift] = -power;
}

void claw(int power){
	motor[ClawLeft] = power;
	motor[ClawRight] = power;
}

void lcdDisplay(){

}

task autonomous(){
}

task usercontrol(){
	bool useTank = true;

	if(!useTank){
		turnLEDOn(dgtl2);
		turnLEDOff(dgtl1);
	}else{
		turnLEDOn(dgtl1);
		turnLEDOff(dgtl2);
	}

	while(true){
		lcdDisplay();
		
		if(vexRT[Btn7U]){
			if(useTank){
				useTank = false;
				turnLEDOn(dgtl2);
				turnLEDOff(dgtl1);
			}else{
				useTank = true;
				turnLEDOn(dgtl1);
				turnLEDOff(dgtl2);
			}
			wait1Msec(50);
		}

		if(vexRT[Btn6U]){ // Lift up
			lift(127);
		}else if(vexRT[Btn5U]){// Lift down
			lift(-127);
		}else{
			lift(0);
		}

		if(vexRT[Btn6D]){ // Open claw
			claw(127);
		}else if(vexRT[Btn5D]){ // Close claw
			claw(-127);
		}else{
			claw(0);
		}

		if(useTank){
			int joyRight = vexRT[Ch2];
			int joyLeft = vexRT[Ch3];
			driveTank(joyLeft, joyRight);
		}else{
			int joy_x = vexRT[Ch1];
			int joy_y = vexRT[Ch2];
      		int joy_threashold = 5;
			motor[leftFront] = joy_y + joy_x;
			motor[leftBack] = joy_y + joy_x;
			motor[rightFront] = joy_y - joy_x;
			motor[rightBack] = joy_y - joy_x;
		}
	}
}
