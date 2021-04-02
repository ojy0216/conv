#include <iostream>
#include <string>
#include "conv_3d.h"
using namespace std;

int main(int argc, char* argv[]){
    string currentDir = argv[0];
    while(currentDir.back() != '\\')
        currentDir.pop_back();

    Conv3D c1(currentDir, "conv1", 1, 6);

    c1.readInput(currentDir + "test_img_7.txt");

    c1.calc_3d();
    c1.printShape();

    Conv3D c2(currentDir, "conv2", c1.get3dOutput(), 16);

    c2.calc_3d(false);
    c2.printShape();
}