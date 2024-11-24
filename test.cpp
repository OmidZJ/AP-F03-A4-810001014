#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string inputLine;
    cout << "Enter one or two integers (e.g., '10 20') or just one integer:" << endl;
    getline(cin, inputLine);

    int value1, value2 = 100; // Default value for the second integer

    stringstream ss(inputLine);
    ss >> value1; // Read the first integer
    ss >> value2; // Try to read the second integer, if available

    cout << "Value 1: " << value1 << endl;
    cout << "Value 2: " << value2 << endl;

    return 0;
}
