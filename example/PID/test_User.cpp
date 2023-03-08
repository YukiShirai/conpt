#include <iostream>
#include <chrono>    
#include <thread>
#include <vector>
#include "User.cpp"
#include <string>

using namespace std;

int main(){
    string name{"Yuki"};
    cout << "hello" << endl;
    User Yuki = User(name);

    cout << Yuki.getSalary() << endl;
    Yuki.setSalary(10);
    cout << Yuki.getSalary() << endl;

    User Koki = Yuki;
    cout << Koki.getSalary() << endl;
    Koki.setSalary(20);
    cout << Koki.getSalary() << endl;
    cout << Yuki.getSalary() << endl;

    


    return 0;
}