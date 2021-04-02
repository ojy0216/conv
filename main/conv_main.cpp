#include <iostream>
#include <string>
#include <vector>
#include "conv.h"
using namespace std;

int main(){
    const string input_file = "C:\\Users\\JY\\Desktop\\input_np.txt";
    const string kernel_file = "C:\\Users\\JY\\Desktop\\kernel_np.txt";

    Conv c;

    c.readInput(input_file);
    c.readKernel(kernel_file);

    c.setPad({1, 2});

    cout << boolalpha << c.calc() << endl;
    c.printInput();
    c.printKernel();
    c.printOutput(); 
}