//Vashist Hegde (vashist99)
#pragma once

#include<bits/stdc++.h>

class interp{
public:
    virtual double interpolate(std::vector<double> xi,std::vector<double> yi,double x)=0;
    virtual std::vector<double> interpolate(std::vector<double> xi,std::vector<double> yi,std::vector<double> xList)=0;    
};

class LagrangeInterp{
public:
    double interpolate(std::vector<double> xi,std::vector<double> yi,double x);
    std::vector<double> interpolate(std::vector<double> xi,std::vector<double> yi,std::vector<double> xList);
};

