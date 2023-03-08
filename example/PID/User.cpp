#include "User.h"
#include <iostream>

using namespace std;

// implementation of member function and variable
struct User::Impl
{   
    string name;
    int salary = -2;
    Impl(string name) : name(move(name)){};
    ~Impl(){};

    void welcomeMessage(){
        cout << "Welcome, " << name << endl;
    }

};


User::User(string name): pimpl(new Impl(move(name))){
    pimpl->welcomeMessage();
}

User::~User(){

};



// Copy constructor

User::User(const User& other):pimpl(new Impl(*other.pimpl)){

}


User& User::operator=(User rhs){

    swap(pimpl, rhs.pimpl);
    return *this;
}



int User::getSalary()
{
    return pimpl->salary;
}
 
void User::setSalary(int salary)
{
    pimpl->salary = salary;
    cout << "Salary set to ..."
         << salary << endl;
}

