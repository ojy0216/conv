#ifndef __POOL_3D_H__
#define __POOL_3D_H__

#include "pool.h"
#include <vector>
#include <list>
using namespace std;

class Pool3D : public Pool{
    vector<vector<vector<double>>> input_3d;
    vector<vector<vector<double>>> output_3d;

    int channel;
public:
    Pool3D(vector<vector<vector<double>>> v);
    bool avg_pool3D(int kernelSize);
    bool avg_pool3D(list<int> kernelSize);

    vector<vector<vector<double>>> get3dOutput();

    void printShape();
};

#endif