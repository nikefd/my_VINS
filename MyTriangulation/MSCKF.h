//
//  MSCKF.h
//  MyTriangulation
//
//  Created by Yang Shuo on 18/3/15.
//  Copyright (c) 2015 Yang Shuo. All rights reserved.
//

#ifndef __MyTriangulation__MSCKF__
#define __MyTriangulation__MSCKF__

#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>
#include <vector>
#include <numeric>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

class MSCKF {
    /* states */
    VectorXf nominalState;  // dimension 4 + 3 + 3 + 3 + 3 = 16
    VectorXf errorState;    // dimension 3 + 3 + 3 + 3 + 3 = 15
    VectorXf extrinsicP;    // p_bc, dimension 3
    VectorXf fullState;      // dimension 15+3+10m

    /* covariance */
    MatrixXf errorCovariance;
    MatrixXf phi;
    
    /* noise matrix */
    MatrixXf Nc;
    
    
    float current_time;
    
    /* IMU measurements */
    Vector3f prev_w, curr_w;
    Vector3f prev_a, curr_a;
    
    /* nominal state variables used only for calculation */
    Vector4f spatial_quaternion; // q_BG
    Matrix3f spatial_rotation; // R_BG
    Vector3f spatial_position;
    Vector3f spatial_velocity;
    Vector3f gyro_bias;
    Vector3f acce_bias;
    
public:
    MSCKF();
    ~MSCKF();
    
    void resetError();
    void setNoiseMatrix(float dgc, float dac, float dwgc, float dwac);
    void processIMU(float t, Vector3f linear_acceleration, Vector3f angular_velocity);
    void processImage(const vector<pair<int, Vector3d>> &image, vector<pair<Vector3d, Vector3d>> &corres);
};

#endif /* defined(__MyTriangulation__MSCKF__) */
