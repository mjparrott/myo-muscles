// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include "Exercises.h"
#include "UI.h"
#include "Mouse.h"
#include "DataCollector.h"

using namespace std;

// The only file that needs to be included to use the Myo C++ SDK is myo.hpp.
#include <myo/myo.hpp>

int main(int argc, char** argv)
{
    int calibrationCounter = 0;
    int calibrationPitch = 0;
    int calibrationYaw = 0;
    int calibrationRoll = 0;
    int lastYawPosition = 0;
    int lastYawDifference = 0;
    int lastPitchPosition = 0;
    int lastPitchDifference = 0 ;

    // We catch any exceptions that might occur below -- see the catch statement for more details.
    try {

    // First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
    // publishing your application. The Hub provides access to one or more Myos.
    myo::Hub hub("com.myo-muscles.myo-muscles");

    std::cout << "Attempting to find a Myo..." << std::endl;

    // Next, we attempt to find a Myo to use. If a Myo is already paired in Myo Connect, this will return that Myo
    // immediately.
    // waitForAnyMyo() takes a timeout value in milliseconds. In this case we will try to find a Myo for 10 seconds, and
    // if that fails, the function will return a null pointer.
    myo::Myo* myo = hub.waitForMyo(10000);

    // If waitForAnyMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
    if (!myo) {
        throw std::runtime_error("Unable to find a Myo!");
    }

    // We've found a Myo.
    std::cout << "Connected to a Myo armband!" << std::endl << std::endl;

    // Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
    DataCollector collector;

    // Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
    // Hub::run() to send events to all registered device listeners.
    hub.addListener(&collector);
	
	UI ui;
	Mouse mouse;

    // Finally we enter our main loop.
    while (1) {
        // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
        // In this case, we wish to update our display 20 times a second, so we run for 1000/20 milliseconds.
        hub.run(1000/20);
        // After processing events, we call the print() member function we defined above to print out the values we've
        // obtained from any events that have occurred.
        collector.print(myo);
		// Update graphics values
		collector.update();

        if(collector.currentExercise == 0){
            //std::cout << collector.calibrating << std::endl;
            std::cout << collector.currentExercise << std::endl;
            std::cout << collector.halfReps << std::endl;
            std::cout << lastYawDifference << std::endl;
            if (collector.calibrating) {
                if (calibrationCounter == 0) {
                    calibrationPitch = collector.pitch_w;
                    calibrationYaw = collector.yaw_w;
                    calibrationRoll = collector.roll_w;
                    calibrationCounter++;
                    std::cout<< "THE CALIBRATION TIMER IS AT: " + calibrationCounter;
                } else if (calibrationPitch == collector.pitch_w && calibrationCounter == 5) {
                    std::cout << "Calibration done. Begin workout." << std::endl;
                    myo->vibrate(myo::Myo::vibrationMedium);
                    collector.workoutStarted = true;
                    collector.calibrating = false;
                    calibrationCounter = 0;
                } else if (calibrationPitch == collector.pitch_w && calibrationCounter < 5) {
                    std::cout << "count : " << calibrationCounter << std::endl; 
                    calibrationCounter++;
                }
            } else if (collector.workoutStarted && (abs(collector.pitch_w - calibrationPitch) > 5 || abs(collector.roll_w - calibrationRoll) > 5)) {
                myo->vibrate(myo::Myo::vibrationShort);
                collector.showError = 20;
            }
                
            std::cout << "workoutStarted = " << collector.workoutStarted << ", lastYawPosition: " << lastYawPosition << ", lastYawDifference: " << lastYawDifference << endl;
            if (collector.workoutStarted && ((collector.yaw_w - lastYawPosition) * lastYawDifference) < 0 ) {
                collector.halfReps++;
                if (collector.halfReps == 16) {
                    collector.sets++;
                    if (collector.sets == 3) {
                        std::cout << "Workout done! Great job!" << std::endl;
                        collector.currentExercise++;
                        collector.workoutStarted = false;   
                        collector.sets = 0; 
                    } else {
                        std::cout << "8 reps done! On to set " << collector.sets + 1 << endl;
                    }
                    lastYawDifference = 0;
                    collector.halfReps = 0;
                }
            }
            lastYawDifference = collector.yaw_w - lastYawPosition != 0 ? (collector.yaw_w - lastYawPosition) : lastYawDifference;
            lastYawPosition = collector.yaw_w;
        }
        else if(collector.currentExercise == 1) {
            //Bench press
            std::cout << collector.calibrating << std::endl;
            std::cout << collector.currentExercise << std::endl;
            if (collector.calibrating) {
                if (calibrationCounter == 0) {
                    calibrationPitch = collector.pitch_w;
                    calibrationCounter++;
                    std::cout<< "THE CALIBRATION TIMER IS AT: " + calibrationCounter;
                } else if (calibrationPitch == collector.pitch_w && calibrationCounter == 5) {
                    std::cout << "Calibration done. Begin workout." << std::endl;
                    myo->vibrate(myo::Myo::vibrationMedium);
                    collector.workoutStarted = true;
                    collector.calibrating = false;
                    calibrationCounter = 0;
                } else if (calibrationPitch == collector.pitch_w && calibrationCounter < 5) {
                    std::cout << "count : " << calibrationCounter << std::endl; 
                    calibrationCounter++;
                }
            } else if (collector.workoutStarted && (abs(collector.pitch_w - calibrationPitch) > 5 || abs(collector.roll_w - calibrationRoll) > 5)) {
                myo->vibrate(myo::Myo::vibrationShort);
                collector.showError = 20;
			}
        }
        else if(collector.currentExercise == 2){
            std::cout << collector.calibrating << std::endl;
            std::cout << collector.currentExercise << std::endl;
            if (collector.calibrating) {
                if (calibrationCounter == 0) {
                    calibrationPitch = collector.pitch_w;
                    calibrationRoll = collector.roll_w;
                    calibrationYaw = collector.yaw_w;
                    calibrationCounter++;
                    std::cout<< "THE CALIBRATION TIMER IS AT: " + calibrationCounter;
                } else if (calibrationYaw == collector.yaw_w && calibrationCounter == 5) {
                    std::cout << "Calibration done. Begin workout." << std::endl;
                    myo->vibrate(myo::Myo::vibrationMedium);
                    collector.workoutStarted = true;
                    collector.calibrating = false;
                    calibrationCounter = 0;
                } else if (calibrationYaw == collector.yaw_w && calibrationCounter < 5) {
                    std::cout << "count : " << calibrationCounter << std::endl; 
                    calibrationCounter++;
                }
            } else if (collector.workoutStarted && (abs(collector.yaw_w - calibrationYaw) > 3 || abs(collector.roll_w - calibrationRoll) > 3)){
                myo->vibrate(myo::Myo::vibrationShort);
                collector.showError = 20;
            }

            if (collector.workoutStarted && ((collector.yaw_w - lastYawPosition) * lastYawDifference) < 0 ) {
                collector.halfReps++;
                if (collector.halfReps == 16) {
                    collector.sets++;
                    if (collector.sets == 3) {
                        std::cout << "Workout done! Great job!" << std::endl;
                        collector.currentExercise++;
                        collector.workoutStarted = false;   
                        collector.sets = 0; 
                    } else {
                        std::cout << "8 reps done! On to set " << collector.sets + 1 << endl;
                    }
                    lastYawDifference = 0;
                    collector.halfReps = 0;
                }
            }
            lastYawDifference = collector.yaw_w - lastYawPosition != 0 ? (collector.yaw_w - lastYawPosition) : lastYawDifference;
            lastYawPosition = collector.yaw_w;
        }
		ALLEGRO_EVENT ev;
		//mouse.getMouse(&ev);
		ui.draw(collector);

    }

    // If a standard exception occurred, we print out its message and exit.
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return 1;
    }
	
	return 0;
}
