#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <myo/myo.hpp>
#include "DataCollector.h"
#include "Main.h"

void DataCollector::onUnpair(myo::Myo* myo, uint64_t timestamp)
{
	// We've lost a Myo.
	// Let's clean up some leftover state.
	roll_w = 0;
	pitch_w = 0;
	yaw_w = 0;
	onArm = false;
}

void DataCollector::onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
{
	using std::atan2;
	using std::asin;
	using std::sqrt;

	// Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
	float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
					   1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
	float pitch = asin(2.0f * (quat.w() * quat.y() - quat.z() * quat.x()));
	float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
					1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));

	// Convert the floating point angles in radians to a scale from 0 to 20.
	roll_w = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 100);
	pitch_w = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 100);
	yaw_w = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 100);
}

void DataCollector::onAccelerometerData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& accel) 
{
	xAccel = accel.x();
	yAccel = accel.y();
	zAccel = accel.z();
}

void DataCollector::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
{
	currentPose = pose;

	if (pose == myo::Pose::fist && calibrating != true) {
		//User first uses fist, begin calibrating
		std::cout << "Being calibration";
		std::cout << "CALIBRATION STARTED";
		calibrating = true;
	} else if (pose == myo::Pose::fingersSpread && workoutStarted) {
		//User finger spread, bench press done
		std::cout << "Ending workout" << std::endl;
		workoutStarted = false;
		myo->vibrate(myo::Myo::vibrationMedium);
		calibrating = false;
		sets++;
		if(sets == 3){
			sets = 0;
			nextExercise();
		}
		halfReps = 0;
	} else if (pose == myo::Pose::waveOut && !workoutStarted) {
		nextExercise();
		sets = 0;
	}
}

void DataCollector::onArmRecognized(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection)
{
	onArm = true;
	whichArm = arm;
}

void DataCollector::onArmLost(myo::Myo* myo, uint64_t timestamp)
{
	onArm = false;
}

void DataCollector::print(myo::Myo* myo)
{
	// Clear the current line
	std::cout << '\r';

	// Print out the orientation. Orientation data is always available, even if no arm is currently recognized.
	/*std::cout << '[' << std::string(roll_w, '*') << std::string(18 - roll_w, ' ') << ']'
			  << '[' << std::string(pitch_w, '*') << std::string(18 - pitch_w, ' ') << ']'
			  << '[' << std::string(yaw_w, '*') << std::string(18 - yaw_w, ' ') << ']';*/
	std::cout << "roll: " << roll_w << ", pitch: " << pitch_w << ", yaw: " << yaw_w;
	//<< ", x: " << xAccel << ", y: " << yAccel << ", z: " << zAccel;

	if (onArm) {
		// Print out the currently recognized pose and which arm Myo is being worn on.

		// Pose::toString() provides the human-readable name of a pose. We can also output a Pose directly to an
		// output stream (e.g. std::cout << currentPose;). In this case we want to get the pose name's length so
		// that we can fill the rest of the field with spaces below, so we obtain it as a string using toString().
		std::string poseString = currentPose.toString();

		std::cout << '[' << (whichArm == myo::armLeft ? "L" : "R") << ']'
				  << '[' << poseString << std::string(14 - poseString.size(), ' ') << ']';
	} else {
		// Print out a placeholder for the arm and pose when Myo doesn't currently know which arm it's on.
		std::cout << "[?]" << '[' << std::string(14, ' ') << ']' << std::endl;
	}

	std::cout << std::flush;
}

void DataCollector::update()
{
	if(showError > 0) {
		showError--;
	}
}

void DataCollector::nextExercise()
{
	if (currentExercise + 1 == EXERCISE_COUNT) {
		currentExercise = 0;
	} else {
		currentExercise++;
	}
}