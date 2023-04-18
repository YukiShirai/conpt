#include <vector>
#include <string>
#include <map>
#include <iostream>

// Forward declaration
class Frame {
public:
    std::string name;

    Frame(const std::string& _name) : name(_name) {}

    virtual ~Frame() {}
};

class FrameTree {
public:
    class Node {
    public:
        Frame* frame;
        Node* parent;
        std::vector<Node*> children;

        Node(Frame* _frame, Node* _parent = nullptr) : frame(_frame), parent(_parent) {}

        void addChild(Node* child) {
            children.push_back(child);
            child->parent = this;
        }
    };

    Node* root;
    std::map<std::string, Node*> frameMap;

    FrameTree(Frame* rootFrame) {
        root = new Node(rootFrame);
        frameMap[rootFrame->name] = root;
    }

    ~FrameTree() {
        // Free allocated memory for all nodes
        for (auto& pair : frameMap) {
            delete pair.second->frame;
            delete pair.second;
        }
    }

    void addFrame(Frame* parentFrame, Frame* childFrame) {
        if (frameMap.count(childFrame->name) > 0) {
            std::cerr << "Error: Frame with name '" << childFrame->name << "' already exists in the frame tree." << std::endl;
            return;
        }

        Node* parentNode = frameMap[parentFrame->name];
        Node* childNode = new Node(childFrame, parentNode);
        frameMap[childFrame->name] = childNode;
        parentNode->addChild(childNode);
    }

    Frame* getFrame(const std::string& frameName) const {
        if (frameMap.count(frameName) == 0) {
            std::cerr << "Error: Frame with name '" << frameName << "' does not exist in the frame tree." << std::endl;
            return nullptr;
        }
        return frameMap.at(frameName)->frame;
    }

    void print() const {
        printSubtree(root, 0);
    }

private:
    void printSubtree(Node* node, int depth) const {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }
        std::cout << node->frame->name << std::endl;
        for (auto child : node->children) {
            printSubtree(child, depth + 1);
        }
    }
};



class TransformFrame : public Frame {
public:
    double x, y, z;
    double roll, pitch, yaw;

    TransformFrame(const std::string& _name, double _x, double _y, double _z, double _roll, double _pitch, double _yaw) : 
        Frame(_name), x(_x), y(_y), z(_z), roll(_roll), pitch(_pitch), yaw(_yaw) {}

    virtual ~TransformFrame() {}
};

class JointFrame : public Frame {
public:
    double angle;

    JointFrame(const std::string& _name, double _angle) : Frame(_name), angle(_angle) {}

    virtual ~JointFrame() {}
};

int main() {
    TransformFrame base("base", 0, 0, 0, 0, 0, 0);
    TransformFrame arm("arm", 1, 0, 0, 0, 0, 0);
    JointFrame elbow("elbow", 0);
    TransformFrame hand("hand", 0, 1, 0, 0, 0, 0);

    // Create a frame tree with the base frame as the root
    FrameTree tree(&base);

    // Add the arm frame as a child of the base frame
    tree.addFrame(&base, &arm);

    // Add the elbow joint frame as a child of the arm frame
    tree.addFrame(&arm, &elbow);

    // Add the hand frame as a child of the elbow joint frame
    tree.addFrame(&elbow, &hand);

    // Print the entire frame tree
    tree.print();

    return 0;
}



// #include <iostream>
// #include <string>

// using namespace std;


// class Transform
// {
// private:
//     string fr;
// public:
//     Transform(string frame_);
//     ~Transform();
// };

// Transform::Transform(string frame_) : fr(frame_)
// {
//     cout << "frame is " << frame_ << endl;
// };

// Transform::~Transform()
// {
// };


// struct tf{
//     Transform root;

//     struct Node
//     {
        
//     };
    

// };


// Transform get_A_2_B(string a_, string b_){
//     Transform A2B{a_};
//     /*modify here*/
//     return A2B;
// }


// int main(){
//     Transform T("A");
//     return 0;
// }