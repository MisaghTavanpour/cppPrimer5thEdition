#include <iostream>
#include <string>


using std::cout;
using std::endl;
using std::string;

int main() {
    int grade = 70;
    string finalgrade;
    finalgrade = (grade > 90) ? "high pass"
                    : (grade < 60) ? "fail" 
                        : (grade < 76) ? "low pass" : "pass" ;
    cout << finalgrade << endl;

    if (grade > 90) {
        finalgrade = "high pass";
    } else if (grade > 75) {
        finalgrade = "pass";
    } else if (grade > 59) {
        finalgrade =  "low pass";
    } else {
        finalgrade = "fail";
    }
    cout << finalgrade << endl;

    return 0;
}
