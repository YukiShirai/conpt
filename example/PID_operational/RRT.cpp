// This RRT code is originally from here with my modifications: https://github.com/markusbuchholz/Path_Planning_RRT_algorithm
/*

Goal:
- design a path from point A to B with obstacles.

RRT:
1. Sample a node in configuration space
2. Check if the node is in collision-free or not.
    - If not, go to #1.
3. Find the nearest node in the tree from the sampled node
4. Extend the tree from the nearest node to the sampled node
5. Check if the path is in collision free
6. go back to #1 until the nearest node to the goal is within the threshold.


Tasks:
1. Setup the class to define the node
2. Setup the RRT class to do the above steps
3. Save data
4. Setup main function
5. Visualization of the tree and the path

*/
// ----------------------------------------------------------------------
// include library
#include <iostream>
#include <random>
#include <vector>
#include <tuple>

using namespace std;

// ----------------------------------------------------------------------
// // define macro
int MAX_ITERATION = 2000;
double MAX_DISTANCE = 2.0;
double GOAL;

// obstacles
std::vector<double> obsXmin{3, 11};
std::vector<double> obsYmin{3, 6};
std::vector<double> obsXmax{7, 18};
std::vector<double> obsYmax{10, 17};

// ----------------------------------------------------------------------
// setup node
struct Node
{
    double posX;
    double posY;
    // doubly linked list
    Node *prev;
    Node *next;
};

// ----------------------------------------------------------------------
// RRT class

class RRT
{
private:
    Node *start;
    Node *goal;
    // setup tree
    std::vector<Node *> rrtNodes;

public:
    RRT(double startX, double startY, double goalX, double goalY);

    bool checkObstacles(double x1, double y1, double x2, double y2, std::tuple<std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>> obs);
    Node *checkNearestNode(Node *new_node);
    bool lookForPath();
};

// ----------------------------------------------------------------------
// RRT implementation
RRT::RRT(double startX, double startY, double goalX, double goalY)
{
    // Node *node = new Node;
    start = new Node;
    start->posX = startX;
    start->posY = startY;
    start->prev = nullptr;
    start->next = nullptr;
    rrtNodes.push_back(start);

    goal = new Node;
    goal->posX = goalX;
    goal->posY = goalY;
    goal->prev = nullptr;
    goal->next = nullptr;
};

bool RRT::checkObstacles(double x1, double y1, double x2, double y2, std::tuple<std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>> obs)
{
    // x1, y1: nearest node in the tree
    // x2, y2: new sampled node

    bool decision{true};

    std::vector<double> minX = std::get<0>(obs);
    std::vector<double> minY = std::get<1>(obs);
    std::vector<double> maxX = std::get<2>(obs);
    std::vector<double> maxY = std::get<3>(obs);

    int num_obs = minX.size();
    double m = (y2 - y1) / (x2 - x1);

    // check if the given pos is inside the region of obstacle:

    // when collision is completely free
    for (int i = 0; i < minX.size(); i++)
    {

        // Completely outside.
        if ((x1 <= minX[i] && x2 <= minX[i]) || (y1 <= minY[i] && y2 <= minY[i]) || (x1 >= maxX[i] && x2 >= maxX[i]) || (y1 >= maxY[i] && y2 >= maxY[i]))
            decision = false;
    }
    for (int i = 0; i < minX.size(); i++)
    {

        double m = (y2 - y1) / (x2 - x1);

        double y = m * (minX[i] - x1) + y1;
        if (y > minY[i] && y < maxY[i])
            decision = true;

        y = m * (maxX[i] - x1) + y1;
        if (y > minY[i] && y < maxY[i])
            decision = true;

        double x = (minY[i] - y1) / m + x1;
        if (x > minX[i] && x < maxX[i])
            decision = true;

        x = (maxY[i] - y1) / m + x1;
        if (x > minX[i] && x < maxX[i])
            decision = true;
    }

    return decision;
};

Node* RRT::checkNearestNode(Node *new_node){

    std::vector<double> tempX;
    std::vector<double> tempY;

    Node *near_node = new Node;

    double minDistance = std::numeric_limits<double>::max();
    double corrX = 0;
    double corrY = 0;
    bool check_obstacle;

    for (auto ii : rrtNodes)
    {
        double distance = std::sqrt(std::pow(new_node->posX - ii->posX, 2) + std::pow(new_node->posY - ii->posY, 2));
    };
    




};

bool RRT::lookForPath(){
    bool find{false};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist100(0, 20);


    // std::random_device dev;
    // std::mt19937 rng(dev());


    for (size_t i = 0; i < MAX_ITERATION; i++)
    {
        Node *random_node = new Node;
        Node *last_node = new Node;

        random_node->posX = dist100(rng);
        random_node->posY = dist100(rng);

        last_node = checkNearestNode(random_node);


                    if (GOAL == 1)
            {
                goal->prev = last_node;
                std::cout << last_node->posX << " :: " << last_node->posY << std::endl;

                return false;
            }
        return true;

    };
    




    return find;
};

// ----------------------------------------------------------------------
// main function
int main()
{
    int a = 10;

    int* i = &a;
    // RRT rrt(1, 1, 10, 15);
    cout << *i << endl;

    return 0;
}
