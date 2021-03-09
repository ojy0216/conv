#include "conv_3d.h"
#include "fc.h"
#include "pool_3d.h"
#include "util.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

void makeImage(string fileName){
    ifstream infile(fileName);

    if(!infile.is_open()){
        cout << "[Error] File open error : " << fileName << endl;
        return;
    }
    
    DV_2D imgData;

    while(!infile.eof()){
        string s, tok;
        vector<double> tmp_row;

        getline(infile, s);
        if(s.empty())
            break;

        istringstream ss(s);
        while(getline(ss, tok, ' ')){
            istringstream os(tok);
            double d;
            os >> d;
            tmp_row.emplace_back(d);
        }
        imgData.emplace_back(tmp_row);
    }
    infile.close();

    string imageName;
    for(string::reverse_iterator it = fileName.rbegin() + 4; it != fileName.rend(); it++){
        imageName.insert(imageName.begin(), *it);
        if(*it == '.')
            break;
    }

    imageName.append(".pgm");

    ofstream img(imageName);
    img << "P2" << endl;
    img << 28 << " " << 28 << endl;
    img << "255" << endl;

    for(auto y = 0; y < 28; y++){
        for(auto x = 0; x < 28; x++)
            img << imgData[y][x] * 255 << " "; 
        img << endl;
    }

    img.close();

    char *sysCall = new char(imageName.size() + 1);

    int i = 0;
    for(; i < imageName.size(); i++)
        sysCall[i] = imageName[i];
    sysCall[i] = '\0';

    system(sysCall); 
}

int main(int argc, char* argv[]){
    if(argc < 2)
        return EXIT_FAILURE;

    string currentDir = argv[0];
    string targetFile = argv[1];

    while(currentDir.back() != '\\')
        currentDir.pop_back();

    Util u;

    // Conv1
    Conv3D c1(currentDir, "conv1", 1, 6);
    c1.readInput(targetFile);
    c1.setPad(2);
    c1.calc_3d(true);
    auto c1_result = c1.get3dOutput();
    cout << "Conv1 complete!\n";

    Pool3D p1(c1_result);
    p1.avg_pool3D(2);
    c1_result = p1.get3dOutput();

    u.v_tanh(c1_result);
    cout << "Pool1 Complete!\n";

    // Conv2
    Conv3D c2(currentDir, "conv2", c1_result, 16);
    c2.calc_3d();
    auto c2_result = c2.get3dOutput();
    cout << "Conv2 Complete!\n";

    Pool3D p2(c2_result);
    p2.avg_pool3D(2);
    c2_result = p2.get3dOutput();

    u.v_tanh(c2_result);
    cout << "Pool2 Complete!\n";

    // Flatten
    auto f_c2_result = u.flatten(c2_result);

    // FC1
    FC fc1(currentDir, "fc1", f_c2_result);
    fc1.calc();
    auto fc1_result = fc1.getOutput();

    u.v_tanh(fc1_result);
    cout << "FC1 Complete!\n";

    // FC2
    FC fc2(currentDir, "fc2", fc1_result);
    fc2.calc();
    auto fc2_result = fc2.getOutput();

    u.v_tanh(fc2_result);
    cout << "FC2 Complete!\n";

    // FC_OUT
    FC fc3(currentDir, "fc3", fc2_result);
    fc3.calc();
    auto fc3_result = fc3.getOutput();

    u.v_tanh(fc3_result);
    cout << "FC_OUT Complete!\n";

    // result
    cout << "-----Result-----\n";
    int i = 0;
    for(auto y : fc3_result){
        for(auto x : y)
            cout << "[" << i++ << "] : " << x << endl;
    }

    auto prediction = max_element(fc3_result[0].begin(), fc3_result[0].end()) - fc3_result[0].begin();
    cout << "Prediction : " << prediction;

    makeImage(targetFile);
}