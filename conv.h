#ifndef __CONV_H__
#define __CONV_H__

#include <vector>
#include <list>
#include <string>
using namespace std;

class Conv{
    vector<vector<double>> input;
    vector<vector<double>> input_calc;
    vector<vector<double>> kernel;
    vector<vector<double>> output;

    int i_h, i_w;
    int k_h, k_w;
    int o_h, o_w;

    int stride_h, stride_w;
    int pad_h, pad_w;

public:
    Conv(vector<vector<double>> v);
    Conv(){};

    vector<vector<double>> read(const string dir);
    void readInput(const string dir);
    void readKernel(const string dir);

    void print(vector<vector<double>> v);
    void printInput();
    void printKernel();
    void printOutput();

    vector<vector<double>> getOutput();

    void pad();

    bool calcOutputSize();

    bool calc(list<int> stride = {1, 1}, list<int> padding = {0, 0}, double bias = 0.);
    bool calc(int stride, int padding, double bias = 0.);
    bool calc(int stride, list<int> padding, double bias = 0.);
    bool calc(list<int> stride, int padding, double bias = 0.);
};

#endif