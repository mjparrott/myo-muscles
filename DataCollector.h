#ifndef __DATACOLLECTOR_H__
#define __DATACOLLECTOR_H__

#include <myo/myo.hpp>

// Classes that inherit from myo::DeviceListener can be used to receive events from Myo devices. DeviceListener
// provides several virtual functions for handling different kinds of events. If you do not override an event, the
// default behaviour is to do nothing.
class DataCollector : public myo::DeviceListener {
public:
    // Classes that inherit from myo::DeviceListener can be used to receive events from Myo devices. DeviceListener
	// provides several virtual functions for handling different kinds of events. If you do not override an event, the
	// default behavior is to do nothing.
	DataCollector()
	: onArm(false), roll_w(0), pitch_w(0), yaw_w(0), currentPose(), workoutStarted(false), calibrating(false)
		, reps(0), sets(0), xAccel(0), yAccel(0), zAccel(0), currentExercise(0)
	{
	}

    // onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
    void onUnpair(myo::Myo* myo, uint64_t timestamp);

    // onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
    // as a unit quaternion.
    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat);

    void onAccelerometerData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& accel);

    // onPose() is called whenever the Myo detects that the person wearing it has changed their pose, for example,
    // making a fist, or not making a fist anymore.
    void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);

    // onArmRecognized() is called whenever Myo has recognized a setup gesture after someone has put it on their
    // arm. This lets Myo know which arm it's on and which way it's facing.
    void onArmRecognized(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection);

    // onArmLost() is called whenever Myo has detected that it was moved from a stable position on a person's arm after
    // it recognized the arm. Typically this happens when someone takes Myo off of their arm, but it can also happen
    // when Myo is moved around on the arm.
    void onArmLost(myo::Myo* myo, uint64_t timestamp);

    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.

    // We define this function to print the current values that were updated by the on...() functions above.
    void print(myo::Myo* myo);

    // These values are set by onArmRecognized() and onArmLost() above.
    bool onArm;
    myo::Arm whichArm;

    // These values are set by onOrientationData() and onPose() above.
    int roll_w, pitch_w, yaw_w;
    myo::Pose currentPose;

    bool workoutStarted, calibrating;
    int reps, sets;
    float xAccel, yAccel, zAccel;
	int currentExercise;
};

#endif