#ifndef __CONV_H__
#define __CONV_H__

#include <vector>
#include <list>
#include <string>
using namespace std;

class Conv{
protected:
    vector<vector<double>> input;
    vector<vector<double>> input_calc;
    vector<vector<double>> kernel;
    vector<vector<double>> output;

    int i_h, i_w;
    int k_h, k_w;
    int o_h, o_w;

    int stride_h = 1, stride_w = 1;
    int pad_h = 0, pad_w = 0;

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

    bool calc(double bias = 0.);

    void setStride(int stride);
    void setStride(list<int> stride);

    void setPad(int pad);
    void setPad(list<int> pad);
};

#endif