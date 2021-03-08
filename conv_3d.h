#ifndef __CONV_3D_H__
#define __CONV_3D_H__

#include "conv.h"
#include <vector>
#include <string>
using namespace std;

class Conv3D : public Conv{
    vector<vector<vector<double>>> input_3d;
    vector<vector<vector<double>>> output_3d;
    vector<double> bias_3d;

    string weight_dir;
    string conv_name;
    int c_in, c_out;

public:
    Conv3D(string curDir, vector<vector<vector<double>>> v, string name, int c_out);
    Conv3D(string curDir, string name, int c_in, int c_out);

    void readBias(const string dir);

    bool calc_3d(bool front = true, bool verbose = false);

    vector<vector<vector<double>>> get3dOutput();

    void printShape();
};

#endif