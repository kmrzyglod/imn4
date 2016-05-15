#include <iostream>
#include "imnmath.h"
#include "Point.h"
#include "FlagMatrix.h"
#include "Relaxation.h"
#include "RelaxationNeumann.h"
#include "PoiseuilleFlow.h"

using namespace std;

#define XSIZE 301
#define YSIZE 91
#define TOL 1e-7


double boundaryConditionPoiseuilleFlowVorticity(int x, int y) {
    double Q = -1;
    double mi = 1;
    double xMin = 0;
    double xMax = 3;
    double yMin = 0;
    double yMax = 0.9;

    if(x == xMin  || y == yMin || x == xMax || x == xMax) {
        double a = pow(y, 3) / 3;
        double b = pow(y, 2) / 2 * (yMin + yMax);
        double c = yMin * yMax * y;
        double vorticity = Q / 2 * mi * (a - b + c);
        return vorticity;
    }
    return 0;

}
double boundaryConditionPoiseuilleFlowStreamFunction(int x, int y) {
    double Q = -1;
    double mi = 1;
    double xMin = 0;
    double xMax = 3;
    double yMin = 0;
    double yMax = 0.9;

    if(x == xMin  || y == yMin || x == xMax || x == xMax) {
        double streamFunction = Q / 2 * mi * (2 * y - yMin - yMax);
        return streamFunction;
    }
    return 0;

}
double boundaryConditionNeumann(int x, int y ) {
    x++;
    y++;
    double u0 = 1;
    int  xmin, ymin;
    xmin = ymin = 1;
    int xsize  = 200;
    int ysize = 100;
    if((x == xmin || x == xsize) && y>ymin && y<ysize) {
        return u0*x;
    }
    else if (y <= 30) {
        return u0*ymin;
    }
    else {
        return  u0*ysize;
    }
}

void zad1() {
//    vector<Point> obstacle1 = {{85,90}, {100,90}, {100,70}, {115,70}, {115, 100}, {85, 100}, {85,90}};
//    vector<Point> obstacle2 = {{85,1}, {85,10}, {100,10}, {100,30}, {115, 30}, {115, 1}, {85,1}};
//    FlagMatrix flagMatrix = FlagMatrix(XSIZE, YSIZE);
//    flagMatrix.DrawObstacle(obstacle1);
//    flagMatrix.DrawObstacle(obstacle2);
//    flagMatrix.SetBorders();
//    Relaxation * relaxation = new RelaxationDirichlet(XSIZE, YSIZE, &flagMatrix, boundaryConditionPoiseuilleFlow);
//    relaxation->NextIteration();
//    relaxation->NextIteration();
//    while(relaxation->CheckTolerance()>=TOL) {
//        relaxation->NextIteration();
//    }
//    cout  << relaxation->GetIteration();
//    relaxation->SaveResults();
//    delete relaxation;


}
void zad2() {
//    vector<Point> obstacle1 = {{85,90}, {100,90}, {100,70}, {115,70}, {115, 100}, {85, 100}, {85,90}};
//    vector<Point> obstacle2 = {{85,1}, {85,10}, {100,10}, {100,30}, {115, 30}, {115, 1}, {85,1}};
//    FlagMatrix flagMatrix = FlagMatrix(XSIZE, YSIZE);
//    flagMatrix.DrawObstacle(obstacle1);
//    flagMatrix.DrawObstacle(obstacle2);
//    flagMatrix.SetBorders();
//    flagMatrix.ConvertToNeumann();
//    Relaxation *  relaxation =  new RelaxationNeumann(XSIZE,YSIZE,&flagMatrix, boundaryConditionNeumann);
//    relaxation->NextIteration();
//    relaxation->NextIteration();
//    while(relaxation->CheckTolerance()>=TOL) {
//        relaxation->NextIteration();
//    }
//    cout  << relaxation->GetIteration();
//    relaxation->SaveResults();
//    delete relaxation;

}



int main() {
    zad1();
    zad2();
    return 0;
}