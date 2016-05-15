//
// Created by Kamil on 15.05.2016.
//

#include "Relaxation.h"

#ifndef IMN3_2_RELAXATIONDIRICHLET_H
#define IMN3_2_RELAXATIONDIRICHLET_H

class PoiseuilleFlow: public Relaxation {
protected:

    void makeRelaxation(){
        for(int i=0;i<_xsize;i++) {
            for(int j=0;j<_ysize;j++) {
                if(_flagMatrix->GetMatrix()[i][j] == 0)
                {
                    _vorticityMatrix[i][j] = (_vorticityMatrix[i-1][j] + _vorticityMatrix[i][j-1]
                                               + _vorticityMatrix[i+1][j] + _vorticityMatrix[i][j+1] - _streamFunctionMatrix[i][j] * pow(_dx, 2))/4.0;

                    //_streamFunctionMatrix  = ?? <- jak ma ten wzór wyglądac  ?
                }
            }
        }
    }

public:
    PoiseuilleFlow(int xsize, int ysize, double dx, double dy, FlagMatrix* flagMatrix,  function < double( int x, int y) > boundaryConditionFn,  function <double( int x, int y)> boundaryConditionFnVorticity)
            : Relaxation(xsize, ysize, dx, dy, flagMatrix, boundaryConditionFn,  boundaryConditionFnVorticity) {}

    void SaveResults() {
        imnd::plot_params.title = "Zad1. Przeplyw potencjalny";
        imnd::plot_params.stype = GNUPLOT_CONTOUR | GNUPLOT_PM3D;
        SaveFlagsMatrixToPNGFile("RelaxationZad1.png");
        ofstream oFile;
        oFile.open ("IntegralZad1.txt");
        for(IntegralGraphPoint el:  _integralGraph) {
            oFile << el.GetX() << " " << el.GetY() << "\n";
        }
        oFile.close();
        system("gnuplot integralZad1.plt");
    }

};

#endif //IMN3_2_RELAXATIONDIRICHLET_H
