#include <stdlib.h>
#include <math.h>
#include <new>          
#include <iostream>
#include <algorithm>    
using namespace std;

#include "mex.h"

void FIRFilter(double* out, double* in,  double* kernel, unsigned int ksize,
        unsigned int n)
{
    unsigned int i, j;
    for( i = 0; i < n - ksize + 1; ++i )
    {
    out[ i ] = 0.0;
    for( j = 0; j < ksize; ++j )
        out[ i ] += in[ i + j ] * kernel[ j ];
    }
}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    //inputs
    double* in;
    double* kernel;
    unsigned int ksize;
	unsigned int n;

    //outputs
    double* out;

    // checking number of arguments
    if(nrhs!=4) {
        mexErrMsgIdAndTxt("MyToolbox:alg_cacfar_2d:nrhs",
                          "Four inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:alg_cacfar_2d:nlhs",
                          "One output required.");
    }

    in     =    mxGetPr(prhs[0]);
	kernel =    mxGetPr(prhs[1]);
    ksize  =   (int)mxGetScalar(prhs[2]);
    n      =   (int)mxGetScalar(prhs[3]);
    
	plhs[0] = mxCreateDoubleMatrix(n-1,1,mxREAL);
	out = mxGetPr(plhs[0]);
   

    FIRFilter(out, in, kernel, ksize, n);

}
  