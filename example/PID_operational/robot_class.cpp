#include <vector>
#include <string>
#include <iostream>

enum class JointType {
  ROTARY,
  LINEAR
};

class Joint {
 public:
  Joint(std::string name, int index, JointType type)
      : name_(name), index_(index), type_(type) {}

  std::string name() const { return name_; }
  int index() const { return index_; }
  JointType type() const { return type_; }

  double torque() const { return torque_; }
  void set_torque(double torque) { torque_ = torque; }

  double velocity() const { return velocity_; }
  void set_velocity(double velocity) { velocity_ = velocity; }

  double position() const { return position_; }
  void set_position(double position) { position_ = position; }

 private:
  std::string name_;
  int index_;
  JointType type_;
  double torque_ = 0.0;
  double velocity_ = 0.0;
  double position_ = 0.0;
};

class RotaryJoint : public Joint {
 public:
  RotaryJoint(std::string name, int index)
      : Joint(name, index, JointType::ROTARY) {}

  // additional members specific to RotaryJoint
};

class LinearJoint : public Joint {
 public:
  LinearJoint(std::string name, int index)
      : Joint(name, index, JointType::LINEAR) {}

  // additional members specific to LinearJoint
};

class RobotArmModel {
 public:
  void add_joint(Joint* joint) { joints_.push_back(joint); }
  int num_joints() const { return joints_.size(); }
  Joint* joint(int i) { return joints_[i]; }

 private:
  std::vector<Joint*> joints_;
};