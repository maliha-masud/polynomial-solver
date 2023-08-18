//i202606_Main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "i202606_Classes.cpp"
using namespace std;

int main()
{
    Polynomial obj1, obj2, obj3;

    cout << "Create Your First Polynomial: " << endl;
    obj1.Input();
    cout << "Output of Your Polynomial in Desired Format: ";
    obj1.Output();
    cout << endl;

    cout << "Create Your Second Polynomial: " << endl;
    obj2.Input();
    cout << "Output of Your Polynomial in Desired Format: ";
    obj2.Output();
    cout << endl;

    //Overloaded +
    cout << "Adding Your Two Polynomials gives the result:  ";
    obj1 + obj2;
    //obj3 = obj1 + obj2;
    //obj3.Output();

    //Overloaded *
    cout << "Multiplying Your Two Polynomials gives the result:  ";
    obj1* obj2;
    //obj3 = obj1 * obj2;
    //obj3.Output();
    cout << endl;

    //Evaluate function
    int n;
    cout << "Evaluate your two polynomials with any real number: ";
    cin >> n;
    cout << "First: ";
    cout << obj1.Evaluate(n) << endl;
    cout << "Second: ";
    cout << obj2.Evaluate(n) << endl;

    /*obj1.~Polynomial();
    obj2.~Polynomial();
    obj3.~Polynomial();*/

    return 0;
}