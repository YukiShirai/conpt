#pragma once

#include <memory>
#include <string>

using namespace std;

class User
{
private:
    /* data */
    class Impl;

    // for template, we use <> to parameterize 
    // unique_ptr is the only pointer to points the object
    unique_ptr<Impl> pimpl;

public:
    // constructor and destructor
    User(string name);
    ~User();

    // copy constructor
    User(const User &other);
    // operator
    User &operator=(User rhs);
    // getter
    int getSalary();
    // setter
    void setSalary(int salary);
};
