//Vashist Hegde (vashist99)
#include<bits/stdc++.h>
#include "../includes/numcpp.hpp"

double LagrangeInterp::interpolate(std::vector<double> xi,std::vector<double> yi,double x){
    //values of lagrange polynomials
    std::vector<double> li;

    //populate li
    for(int i=0;i<xi.size();i++){
        double prod = 1;
        for(int j=0;j<xi.size();j++){
            if(i!=j){
                prod*=((x-xi[j])/(xi[i]-xi[j]));
            }
        }
        li.push_back(prod);
    }

    //for all i, find sum of li*yi (i.e product of actual value and value of lagrange polynomial for a given xi)
    double final=0;
    for(int i=0;i<xi.size();i++){
        final+=(li[i]*yi[i]);
    }

    return final;
}

std::vector<double> LagrangeInterp::interpolate(std::vector<double> xi,std::vector<double> yi,std::vector<double> x){
    
    std::vector<double> final;

    
    for(int i=0;i<x.size();i++){
        final.push_back(interpolate(xi,yi,x[i]));
    }

    return final;
}
