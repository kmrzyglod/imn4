//
// Created by Kamil on 08.05.2016.
//
#ifndef IMN3_2_RELAXATION_H
#define IMN3_2_RELAXATION_H

#include <c++/functional>
#include "FlagMatrix.h"
#include "IntegralGraphPoint.h"

class Relaxation {
protected:
    double** _streamFunctionMatrix;
    double** _vorticityMatrix;
    vector<IntegralGraphPoint> _integralGraph;
    int _xsize, _ysize, _iter;
    double _nowFnStreamValue,  _nowVorticityValue, _prevFnStreamValue, _prevVorticityValue, _dx, _dy;
    FlagMatrix* _flagMatrix;
    function < double(int x, int y) > _boundaryConditionFnStream;
    function < double(int x, int y) > _boundaryConditionFnVorticity;


    Relaxation() {}

    virtual void makeRelaxation()  =  0;

    void checkValuesInPoint(int i, int j) {
        _nowFnStreamValue = _streamFunctionMatrix[i][j];
        _nowVorticityValue = _vorticityMatrix[i][j];

    }


    void setBoundaryConditions() {
        for(int i=0;i<_xsize;i++) {
            for(int j=0;j<_ysize;j++) {
                if(_flagMatrix->GetMatrix()[i][j] == 1)
                {
                    _streamFunctionMatrix[i][j] = _boundaryConditionFnStream(i*_dx, j*_dy);
                    _vorticityMatrix[i][j] = _boundaryConditionFnVorticity(i*_dx, j*_dy);
                }
            }
        }
    }

public:
    Relaxation(int xsize, int ysize, double dx, double dy,  FlagMatrix* flagMatrix,  function <double( int x, int y)> boundaryConditionFnStream,  function <double( int x, int y)> boundaryConditionFnVorticity):
            _xsize(xsize), _ysize(ysize), _flagMatrix(flagMatrix), _dx(dx), _dy(dy), _boundaryConditionFnStream(boundaryConditionFnStream), _boundaryConditionFnVorticity(boundaryConditionFnVorticity) {
        _streamFunctionMatrix = imnd::matrix(_xsize, _ysize);
        _vorticityMatrix = imnd::matrix(_xsize, _ysize);
        Reset();
    }

    void Reset() {
        imnd::set_matrix(_streamFunctionMatrix, _xsize, _ysize, 0);
        imnd::set_matrix(_vorticityMatrix, _xsize, _ysize, 0);
        _nowFnStreamValue = 0;
        _prevFnStreamValue = 0;
        _prevVorticityValue = 0;
        _nowVorticityValue = 0;
        _iter = 0;
        setBoundaryConditions();
    }

    void NextIteration(int i, int j) {
        makeRelaxation();
        checkValuesInPoint(i, j);
//        if(_iter > 100) {
//            _integralGraph.push_back({_iter, _nowFnStreamValue});
//        }
        _prevFnStreamValue = _nowFnStreamValue;
        _prevVorticityValue = _nowVorticityValue;
        _iter++;
    }

    int GetIteration() {
        return _iter;
    }

     bool CheckTolerance(double tol) {
        if(fabs(_nowFnStreamValue - _prevFnStreamValue)  < tol &&  fabs(_nowVorticityValue - _prevVorticityValue) < tol && _iter > 100) {
            return false;
        }
            return true;
    }

    void SaveFlagsMatrixToPNGFile(const char *fileName) {
        imnd::plot_2d_system(fileName, _streamFunctionMatrix, _xsize, _ysize,  _dx, _dy);
    }

    virtual void SaveResults() = 0;

    void PrintMatrixToFile(const char* fileName) {
        ofstream oFile;
        oFile.open (fileName);
        for(int i=0;i<_xsize;i++) {
            for(int j=0;j<_ysize;j++) {
                oFile << _streamFunctionMatrix[i][j] << ", ";
            }
            oFile << "\b\b\n";
        }
        oFile.close();
    }

};

#endif //IMN3_2_RELAXATION_H
