// C++ TODO
// robor arm
/*
- error handling 
*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

// I can first design joint type with this way
enum class JointType
{
    ROTARY,
    LINEAR
};

class Joint
{
    // put common functions and private variables in this function
private:
    string name;
    int index;
    JointType type;
    double torque{0};
    double velocity{0};
    double position{0};

public:
    Joint(string name_, int index_, JointType type_);
    virtual ~Joint();
    // setup getter:
    string getName() { return name; };
    int getIndex() { return index; };
    JointType getType() { return type; };
    double getTorque() { return torque; };
    double getVelocity() { return velocity; };
    double getPosition() { return position; };

    // setup setter
    void setTorque(double torque_)
    {
        torque = torque_;
    };

    void setVelocity(double velocity_)
    {
        velocity = velocity_;
    };

    void setPosition(double position_)
    {
        position = position_;
    };
};

Joint::Joint(string name_, int index_, JointType type_) : name(name_), index(index_), type(type_){
                                                                                          // cout << "Hello FuckAlex!! I'm " << name << ", " << "where the index is " << index << " and JointType is " << type<< endl;
                                                                                      };

Joint::~Joint(){};

class RotaryJoint : public Joint
{
    // use this class to define specific functions for rotary joint
public:
    RotaryJoint(string name_, int index_);
    ~RotaryJoint();
};

RotaryJoint::RotaryJoint(string name_, int index_)
    : Joint(name_, index_, JointType::ROTARY){
      };

RotaryJoint::~RotaryJoint(){

};

class RobotArmModel
{
private:
    std::vector<Joint *> joints;

public:
    RobotArmModel(){};
    ~RobotArmModel(){};

    void add_joints(Joint *joint)
    {
        joints.push_back(joint);
    };

    Joint *getJoint(int i)
    {
        return joints[i];
    };

    int num_joints()
    {
        return joints.size();
    };
};

int main()
{
    Joint q1("Joint1", 0, JointType::ROTARY);
    Joint q2("Joint2", 1, JointType::ROTARY);
    Joint q3("Joint3", 2, JointType::LINEAR);
    Joint q4("Joint3", 3, JointType::LINEAR);

    RobotArmModel scaler;
    scaler.add_joints(&q1);
    scaler.add_joints(&q2);
    scaler.add_joints(&q3);
    scaler.add_joints(&q4);

    for (int i = 0; i < scaler.num_joints(); i++)
    {
        scaler.getJoint(i)->setTorque(i);
    }

    for (int i = 0; i < scaler.num_joints(); i++)
    {
        cout << scaler.getJoint(i)->getName() << endl;
    }

    return 0;
};