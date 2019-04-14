#include "legendviewmodel.h"

LegendViewModel::LegendViewModel()
{
    isSmoothed = false;
    this->a = 0;
    this->b = 0;
    this->c = 0;
    this->d = 0;
    this->m = 0;
    this->n = 0;
}

LegendViewModel::LegendViewModel(int a, int b, int c, int d, int m, int n, std::vector<QColor *> colors)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->m = m;
    this->n = n;
    this->colors = colors;
}

void LegendViewModel::start(int width, int height)
{
    for(int u=0;u<width;u++){
        for(int v=0;v<height;v++){
            double x = (double)u/(double)width*(b-a)+a;
            double y = ((double)v/(double)height)*(d-c)+c;
            double x0=((x-a)/(b-a))*(m-1)*(double)(b-a)/(double)(m-1);
            double y0=((y-c)/(d-c))*(n-1)*(double)(d-c)/(double)(n-1);
            double x1=x0+(double)(b-a)/(m);
            double y1=y0+(double)(d-c)/(n);
            double z0=f(x1,y1);
            double z1=f(x0,y1);
            double z2=f(x0,y0);
            double z3=f(x1,y0);
            double z01=approximation(z1,z0,(double)(x-x0)/(x1-x0));
            double z23=approximation(z2,z3,(double)(x-x0)/(x1-x0));
            val.push_back(approximation(z23,z01,(double)(y-y0)/(y1-y0)));
        }
    }

    double maxElement = *std::max_element(val.begin(), val.end());
    double minElement = *std::min_element(val.begin(), val.end());
    foreach (double var, val) {
        colInd.push_back((var-minElement)/(maxElement-minElement)*(colors.size()-1));
        bool check=false;
        for(int i=0;i<divide.size();i++){
            if(divide[i].color == colInd.back()){
                check=true;
                if( divide[i].lower>var){
                    divide[i].lower=var;
                }
                if( divide[i].higher<var){
                    divide[i].higher=var;
                }
            }
        }
        if(!check){
            divide.push_back(LegendBoundaries(colInd.back(),var,var));
        }
    }
}


double LegendViewModel::approximation(double x, double y, double k)
{
    return x+k*(y-x);
}

double LegendViewModel::f(double x,double y){
    return x;
}
