#include <iostream>
#include "exept.h"
#include <string>
using namespace std;


Rectangle::Rectangle(int w, int h) {
    try {
        if (w < 0 || h < 0) {
            throw string("Rectangle dimensions must be non-negative");
        }

        // Assign the values if they are non-negative
        width = w;
        height = h;
    } catch (const string &e) {

       cout << "Error in Rectangle constructor: " << e <<endl;


    }

}