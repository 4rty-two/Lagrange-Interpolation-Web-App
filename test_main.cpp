//Vashist Hegde (vashist99)
#include<bits/stdc++.h>
#include "includes/numcpp.hpp"

int main(){
    std::vector<double> x = {0, 1, 2.5, 2.72, 3.14};
    std::vector<double> xi = {2.0,4.0,6.0};
    std::vector<double> yi = {1.0,3.0,5.0};
    LagrangeInterp lagrangeInterp;
    std::vector<double> ans = lagrangeInterp.interpolate(xi,yi,x);
    for(int i=0;i<ans.size();i++){
        std::cout<<ans[i]<<" ";
    }
    std::cout<<std::endl;
     
}