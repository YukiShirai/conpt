// g++ cpp_RRT.cpp -o t -I/usr/include/python3.8 -lpython3.8
#include <random>
#include <iostream>
#include <vector>
#include <tuple>
#include <math.h>
#include <limits>

#define PLOT

#ifdef PLOT
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
#endif

double MAX_ITERATION = 2000;
double MAX_DISTANCE = 2;
double GOAL;

// obstacles for RRT
std::vector<double> obsXmin{3, 11};
std::vector<double> obsYmin{3, 6};
std::vector<double> obsXmax{7, 18};
std::vector<double> obsYmax{10, 17};

//------------------------------------------------------------------------------

struct Node
{
    double posX;
    double posY;
    Node *prev;
    Node *next;
};

//------------------------------------------------------------------------------

class RRT
{

private:
    Node *start;
    Node *goal;
    std::vector<Node *> rrtNodes;

public:
    RRT(double startX, double startY, double goalX, double goalY)
    {

        Node *node = new Node;
        this->start = node;
        start->posX = startX;
        start->posY = startY;
        start->prev = nullptr;
        rrtNodes.push_back(node);

        node = new Node;
        this->goal = node;
        goal->posX = goalX;
        goal->posY = goalY;
        goal->prev = nullptr;
        goal->next = nullptr;
    }

    //------------------------------------------------------------------------------

#ifdef PLOT

    // void prdoubleGoalPath(Node *path_node)
    void printGoalPath(std::tuple<std::vector<double>, std::vector<double>> path)
    {
        std::vector<double> xX = std::get<0>(path);
        std::vector<double> yY = std::get<1>(path);

        // obstacles for visualisation
        std::vector<int> obsX1{3, 7, 7, 3, 3};
        std::vector<int> obsY1{3, 3, 10, 10, 3};

        std::vector<int> obsX2{11, 18, 18, 11, 11};
        std::vector<int> obsY2{6, 6, 17, 17, 6};

        plt::figure_size(600, 600);
        plt::plot(obsX1, obsY1, "darkblue");
        plt::plot(obsX2, obsY2, "darkblue");
        plt::plot(xX, yY, "r--");
        plt::xlabel("xx");
        plt::ylabel("yy");
        plt::xlim(-1, 21);
        plt::ylim(-1, 21);

        plt::show();
    }

    //------------------------------------------------------------------------------

    void plotRRT()
    {

        std::vector<double> xX;
        std::vector<double> yY;

        for (auto &ii : rrtNodes)
        {

            xX.push_back(ii->posX);
            yY.push_back(ii->posY);
        }

        plt::figure_size(600, 600);
        plt::plot(xX, yY);
        plt::xlabel("xx");
        plt::ylabel("yy");
        plt::xlim(0, 20);
        plt::ylim(0, 20);

        plt::show();
    }
#endif

    //------------------------------------------------------------------------------

    //   https://en.wikipedia.org/wiki/Line_(geometry)
    //   https://en.wikipedia.org/wiki/doubleersection_(Euclidean_geometry)

    bool checkObstacles(double x1, double y1, double x2, double y2, std::tuple<std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>> obs)
    {
        bool decision;
        std::cout << x1 << " : " << y1 << " : " << x2 << " : " << y2 << std::endl;

        std::vector<double> minX = std::get<0>(obs);
        std::vector<double> minY = std::get<1>(obs);
        std::vector<double> maxX = std::get<2>(obs);
        std::vector<double> maxY = std::get<3>(obs);

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
    }

    //------------------------------------------------------------------------------

    Node *checkNearestNode(Node *new_node)
    {

        std::vector<double> tempX;
        std::vector<double> tempY;

        Node *near_node = new Node;
        double minDistance = std::numeric_limits<double>::max();
        double corrX = 0.0;
        double corrY = 0.0;
        bool check_obstacle;

        for (auto &ii : rrtNodes) // just getting reference 
        {

            double distance = std::sqrt(std::pow((new_node->posX - ii->posX), 2) + std::pow((new_node->posY - ii->posY), 2));
            if (distance < minDistance)
            {

                minDistance = distance;
                near_node = ii;
            }
        }

        double dx = new_node->posX - near_node->posX;
        double dy = new_node->posY - near_node->posY;
        double angle = std::atan2(dy, dx) * 180 / M_PI;

        if (minDistance > MAX_DISTANCE)
        {

            corrX = std::abs(near_node->posX + std::cos(angle) * MAX_DISTANCE);
            corrY = std::abs(near_node->posY + std::sin(angle) * MAX_DISTANCE);
        }

        if (minDistance <= MAX_DISTANCE)
        {

            corrX = new_node->posX;
            corrY = new_node->posY;
        }
        if (rrtNodes.size() > 0)
        {
            check_obstacle = checkObstacles(near_node->posX, near_node->posY, corrX, corrY, std::make_tuple(obsXmin, obsYmin, obsXmax, obsYmax));
        }

        new_node->posX = corrX;
        new_node->posY = corrY;

        near_node->next = new_node;
        new_node->prev = near_node;

        if (rrtNodes.size() == 0)
        {

            new_node->prev = start;
        }

        if (check_obstacle == 0)
        {
            rrtNodes.push_back(new_node);
        }

        if (((double)new_node->posX == (double)this->goal->posX) && ((double)new_node->posY == (double)this->goal->posY))
        {

            std::cout << "The GOAL achive && GOLD path is ..." << std::endl;

            GOAL = 1;

            while (new_node->prev != nullptr)

            {
                std::cout << new_node->posX << " :?: " << new_node->posY << std::endl;
                new_node = new_node->prev;
                tempX.push_back(new_node->posX);
                tempY.push_back(new_node->posY);
            }

            printGoalPath(std::make_tuple(tempX, tempY));
        }

        return new_node;
    }

    //------------------------------------------------------------------------------

    double lookForPath()
    {

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist100(0, 20);

        for (double i = 0; i < MAX_ITERATION; i++)
        {
            Node *random_node = new Node;
            Node *last_node = new Node;

            double randX = dist100(rng);
            double randY = dist100(rng);
            random_node->posX = randX;
            random_node->posY = randY;

            last_node = checkNearestNode(random_node);

            if (GOAL == 1)
            {
                goal->prev = last_node;
                std::cout << last_node->posX << " :: " << last_node->posY << std::endl;

                return -1;
            }
        }
        return 1;
    }

    //------------------------------------------------------------------------------

    void printRRT(RRT &rrt)
    {
        Node *node = rrt.start;
        std::cout << node->posX << " : " << node->posY << std::endl;
        node = rrt.goal;
        std::cout << node->posX << " : " << node->posY << std::endl;
    }
};

//------------------------------------------------------------------------------

int main()
{

    RRT rrt(1, 1, 10, 15);
    // rrt.printRRT(rrt);
    double checkpath = rrt.lookForPath();
#ifdef PLOT
    rrt.plotRRT();
#endif
}