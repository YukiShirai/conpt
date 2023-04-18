/*
Goal: to manipulate objects. T
Conditions:
- diffferent objects (convex vs nonconvex)
- different motion planner (RRT vs optimization)

Strategy
- Object class
  - base_object class (e.g., coefficient of friction)
    Convex: 
    Nonconvex: 

- Create motion planner class
  - base_planner class (e.g., start / goal, runMotionPlan)
    RRT class
      - RRT implementation
    TO class
      - TO implementation

- Robot class
  - move arm
  - grasp function
  

*/

#include <iostream>
#include <vector>

using namespace std;

enum class ObjectType{
  CONVEX, 
  NONCONVEX
};

class object{
  
  private:
    double mu;
    double length;
    double width;
    double mass;
    ObjectType type;
    
  public:
    object(double mu_, double length_, double width_, double mass_, ObjectType type_) : mu(mu_), length(length_), width(width_), mass(mass_), type(type_)
    {
        cout << "object constructor" << endl;
    };
    virtual ~object(){};
    
  
};


class convexObject : public object{
  
  public:
    convexObject(double mu_, double length_, double width_, double mass_) : object(mu_, length_, width_, mass_, ObjectType::CONVEX){
      cout << "CONVEX object constructor" << endl;
    };
    ~convexObject(){};
  
};



class nonconvexObject : public object{
  
  public:
    nonconvexObject(double mu_, double length_, double width_, double mass_) : object(mu_, length_, width_, mass_, ObjectType::NONCONVEX){
      cout << "NONCONVEX object constructor" << endl;
    };
    ~nonconvexObject(){};
  
};


class planner{
  
  private: 
    std::vector<double> start;
    std::vector<double> goal;
  public:
    planner(std::vector<double> start_, std::vector<double> goal_) : start(start_), goal(goal_){};
    virtual ~planner(){};
    
    virtual void runMotionPlan() = 0;
    
    void getInfo(){
      cout << "start: ";
      
      std::vector<double>::iterator it;
      for(it = start.begin(); it!= start.end(); it++){
        cout << *it << endl;
      };
      
    };
    
  
};


class rrt : public planner{
  
  
  public:
  rrt(std::vector<double> start_, std::vector<double> goal_) : planner(start_, goal_){
    cout << "RRT is created" << endl;
  };
  ~rrt(){};
  
  void runMotionPlan(){
    cout << "RRT implementation" << endl;
  };
  
};






int main() {
  
  // ObjectType type = ObjectType::CONVEX;
	
  // object obj(0.3, 0.1, 0.2, 0.5, type);
  
  nonconvexObject obj(0.3, 0.1, 0.2, 0.5);
  
  std::vector<double> start;
  std::vector<double> goal;
  start.push_back(1);
  start.push_back(-10);
  goal.push_back(-2.7);
  rrt plan(start, goal);
  
  // plan.getInfo();
  
	return 0;
}
