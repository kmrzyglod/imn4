//
// Created by Kamil on 15.05.2016.
//

#include "Relaxation.h"

#ifndef IMN3_2_RELAXATIONDIRICHLET_H
#define IMN3_2_RELAXATIONDIRICHLET_H

class FlowWithObstacle: public Relaxation {
protected:

    void makeRelaxation(){
        for(int i=0;i<_xsize;i++) {
            for(int j=0;j<_ysize;j++) {
                if(_flagMatrix->GetMatrix()[i][j] == 0)
                {
                    double a = (_vorticityMatrix[i+1][j] + _vorticityMatrix[i-1][j]
                                + _vorticityMatrix[i][j-1] + _vorticityMatrix[i][j+1])/4.0;
                    double b = _streamFunctionMatrix[i][j+1] - _streamFunctionMatrix[i][j-1];
                    double c = _vorticityMatrix[i+1][j] - _vorticityMatrix[i-1][j];
                    double d = _streamFunctionMatrix[i+1][j] - _streamFunctionMatrix[i-1][j];
                    double e = _vorticityMatrix[i][j+1] - _vorticityMatrix[i][j-1];
                    _vorticityMatrix[i][j]  = a - 1.0/16.0 * (b*d - d*e);

                    _streamFunctionMatrix[i][j] = (_streamFunctionMatrix[i-1][j] + _streamFunctionMatrix[i][j-1]
                                               + _streamFunctionMatrix[i+1][j] + _streamFunctionMatrix[i][j+1] - _vorticityMatrix[i][j] * pow(_dx, 2))/4.0;
                }
            }
        }
    }

public:
    FlowWithObstacle(int xsize, int ysize, double dx, double dy, FlagMatrix* flagMatrix,  function < double( double x, double y) > boundaryConditionFnStream,  function <double( double x, double y)> boundaryConditionFnVorticity)
            : Relaxation(xsize, ysize, dx, dy, flagMatrix, boundaryConditionFnStream,  boundaryConditionFnVorticity) {}

    void SaveResults() {
//        double Q = -1;
//        double mi = 1;
//        double xMin = 0;
//        double xMax = 3;
//        double yMin = 0;
//        double yMax = 0.9;
//        imnd::plot_params.title = "Zad1. Przeplyw ";
//        imnd::plot_params.stype = GNUPLOT_CONTOUR | GNUPLOT_PM3D;
//        SaveFlagsMatrixToPNGFile("StreamZad1.png", "VorticityZad1.png");
//        ofstream oFile;
//        oFile.open ("FnZad1Vorticity.txt");
//        for(int j=0;j<_ysize;j++) {
//            double vorticityAnalitical = Q / 2 * mi * (2 * j*_dx - yMin - yMax);
//            oFile << j*_dy << " " <<  _vorticityMatrix[50][j] << " " <<  _vorticityMatrix[250][j] << " " << vorticityAnalitical << "\n";
//        }
//        oFile.close();
//        //system("gnuplot FnZad1i50.plt");
//
//        ofstream oFile2;
//        oFile2.open ("FnZad1Stream.txt");
//        for(int j=0;j<_ysize;j++) {
//            double a = pow(j*_dy, 3) / 3;
//            double b = pow(j*_dy, 2) / 2 * (yMin + yMax);
//            double c = yMin * yMax * j*_dy;
//            double stream = Q / 2 * mi * (a - b + c);
//
//            oFile2 << j*_dy << " " <<  _streamFunctionMatrix[50][j] << " " <<  _streamFunctionMatrix[250][j] << " " << stream << "\n";
//        }
//        oFile2.close();
//        //system("gnuplot FnZad1i250.plt");
//
//        ofstream oFile3;
//        oFile3.open ("FnZad1Velocity.txt");
//        for(int j=0;j<_ysize-1;j++) {
//            double fn = Q/2*mi * (j*_dy - yMin)*(j*_dy - yMax);
//            double fnCalculated = (_streamFunctionMatrix[50][j+1] - _streamFunctionMatrix[50][j-1])/(2*_dx);
//            oFile3 << j*_dy << " " << fn << " " << fnCalculated << "\n";
//        }
//        oFile3.close();
//        system("gnuplot plotAll.plt");


    }

};

#endif //IMN3_2_RELAXATIONDIRICHLET_H
