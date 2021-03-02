#include <iostream>
#include <string>
#include <vector>
#include "fc.h"
using namespace std;

int main(){
    const string input_file = "C:\\Users\\JY\\Desktop\\input_np.txt";
    const string weight_file = "C:\\Users\\JY\\Desktop\\weight_np.txt";
    const string bias_file = "C:\\Users\\JY\\Desktop\\bias_np.txt";

    FC fc;

    fc.readInput(input_file);
    fc.readWeight(weight_file);
    fc.readBias(bias_file);

    fc.calc();

    fc.printInput();
    fc.printWeight();
    fc.printBias();
    fc.printOutput();
}