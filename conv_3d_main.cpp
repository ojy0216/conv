#include <iostream>
#include <string>
#include "conv_3d.h"
using namespace std;

int main(){
    Conv3D c1("conv1", 1, 6);

    c1.readInput("C:\\Users\\JY\\Desktop\\test_img_7.txt");

    c1.calc_3d();
    c1.printShape();

    Conv3D c2(c1.get3dOutput(), "conv2", 16);

    c2.calc_3d(false);
    c2.printShape();
}