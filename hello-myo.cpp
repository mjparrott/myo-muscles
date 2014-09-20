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
    int lastYawPosition = 0;
    int refPosition;

    // We catch any exceptions that might occur below -- see the catch statement for more details.
    try {

    // First, we create a Hub with our application identifier. Be sure not to use the com.example namespace when
    // publishing your application. The Hub provides access to one or more Myos.
    myo::Hub hub("com.example.hello-myo");

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

        if(collector.currentExercise == 0 || collector.currentExercise == 1){
             std::cout << collector.calibrating << std::endl;
             std::cout << collector.currentExercise << std::endl;
            if (collector.calibrating) {
                if (calibrationCounter == 0) {
                    calibrationPitch = collector.pitch_w;
                    calibrationYaw = collector.yaw_w;
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
            } else if (collector.workoutStarted && (collector.pitch_w - calibrationPitch) > 0.8) {
                myo->vibrate(myo::Myo::vibrationShort);
				ui.drawText(ui.headerFont, al_map_rgb(255, 0, 0), 10.0, 100.0, 0, "ERROR");
			}
            if(collector.workoutStarted && lastYawPosition - calibrationYaw){

            }
        }
        else if(collector.currentExercise == 2 || collector.currentExercise == 3 || collector.currentExercise == 4){
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
            } else if (collector.workoutStarted && (collector.pitch_w > calibrationPitch + 0.8 || collector.pitch_w < calibrationPitch - 0.8))
                myo->vibrate(myo::Myo::vibrationShort);
        }
        else if(collector.currentExercise == 5 || collector.currentExercise == 6 || collector.currentExercise == 7){
            //SHOULDERS
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
}
