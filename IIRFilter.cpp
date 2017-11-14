#include <stdlib.h>
#include <math.h>
#include <new>          
#include <iostream>
#include <algorithm>    
using namespace std;

#include "mex.h"

void IIRFilter(double* out, double* in,  double* b, double* a, unsigned int filtorder, unsigned int n)
{
    unsigned int i, j;
	double bsum,asum;
	for (i = 0; i < filtorder + 1; ++i){
		out[ i ] = 0.0;
	}
    for( i = filtorder; i < n ; ++i ){
		out[ i ] = 0.0;
		bsum = 0.0;
		asum = 0.0;
		for( j = 0; j <= filtorder; ++j )
		{
			bsum += in[ i - j ] * b[ j ];
		}
		for( j = 1; j <= filtorder; ++j )
		{
			asum += out[ i - j ] * a[ j ];
		}

		out[ i ]  = (bsum - asum);
	}
}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    //inputs
    double* in;
	double* b;
	double* a;
    unsigned int filtorder;
	unsigned int n;

    //outputs
    double* out;

    // checking number of arguments
    if(nrhs!=5) {
        mexErrMsgIdAndTxt("MyToolbox:alg_cacfar_2d:nrhs",
                          "Five inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:alg_cacfar_2d:nlhs",
                          "One output required.");
    }

    in         =    mxGetPr(prhs[0]);
	b          =    mxGetPr(prhs[1]);
	a          =    mxGetPr(prhs[2]);
    filtorder  =   (int) mxGetScalar(prhs[3]);
    n          =   (int) mxGetScalar(prhs[4]);
    
	plhs[0]    = mxCreateDoubleMatrix(n , 1, mxREAL);
	out        = mxGetPr(plhs[0]);
   

    IIRFilter(out, in, b, a, filtorder, n);

}
  