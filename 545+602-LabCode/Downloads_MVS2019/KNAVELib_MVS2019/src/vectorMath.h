
#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

 
// UPDATED: 2016-08-25  (Y. Hu: Microsoft Visual Studio 2015; System configuration - Windows 7 + 16:9 screen ratio)
// UPDATED: 2018-08-02  (Y. Hu: Microsoft Visual Studio 2017; System configuration - Windows 7 + 16:9 screen ratio)
// UPDATED: 2021-07-19  (Y. Hu: Microsoft Visual Studio 2019; System configuration - Windows 10 + 16:9 screen ratio) 

#include <math.h>

inline double vecLength( double * vec ){
  
  return sqrt( vec[0]*vec[0] +  vec[1]*vec[1] +  vec[2]*vec[2] );

}

inline float vecLength( float * vec ){
  
  return (float)sqrt( vec[0]*vec[0] +  vec[1]*vec[1] +  vec[2]*vec[2] );

}

inline double * vecNormalize( double * vec ){

  double length = vecLength( vec );
  vec[0]/=length;
  vec[1]/=length;
  vec[2]/=length;

  return vec;

}

inline float * vecNormalize( float * vec ){

  float length = vecLength( vec );
  vec[0]/=length;
  vec[1]/=length;
  vec[2]/=length;

  return vec;

}

inline double vecDot( double * vec1, double * vec2 ){

  return ( vec1[0]*vec2[0] +  vec1[1]*vec2[1] +  vec1[2]*vec2[2] );

}

inline float vecDot( float * vec1, float * vec2 ){

  return ( vec1[0]*vec2[0] +  vec1[1]*vec2[1] +  vec1[2]*vec2[2] );

}


inline double * vecSubtract( double * vec1, double * vec2, double * vecOut ){

  vecOut[0] = vec1[0] - vec2[0];
  vecOut[1] = vec1[1] - vec2[1];
  vecOut[2] = vec1[2] - vec2[2];

  return vecOut;

}

inline float * vecSubtract( float * vec1, float * vec2, float * vecOut ){

  vecOut[0] = vec1[0] - vec2[0];
  vecOut[1] = vec1[1] - vec2[1];
  vecOut[2] = vec1[2] - vec2[2];

  return vecOut;

}

inline double * vecCross( double * vec1, double * vec2, double * vecOut ){

  vecOut[0] = ( vec1[1] * vec2[2] ) - ( vec1[2] * vec2[1] );
  vecOut[1] = ( vec1[2] * vec2[0] ) - ( vec1[0] * vec2[2] );
  vecOut[2] = ( vec1[0] * vec2[1] ) - ( vec1[1] * vec2[0] );

  return vecOut;

}

inline float * vecCross( float * vec1, float * vec2, float * vecOut ){

  vecOut[0] = ( vec1[1] * vec2[2] ) - ( vec1[2] * vec2[1] );
  vecOut[1] = ( vec1[2] * vec2[0] ) - ( vec1[0] * vec2[2] );
  vecOut[2] = ( vec1[0] * vec2[1] ) - ( vec1[1] * vec2[0] );

  return vecOut;

}

void MultVectorByMatrix( float * matrix, float * vectorIn, float * vectorOut );
void MultVector4ByMatrix( float * matrix, float * vectorIn, float * vectorOut );
void MultVectorByMatrix( double * matrix, double * vectorIn, double * vectorOut );
void MultVector4ByMatrix( double * matrix, double * vectorIn, double * vectorOut );

void MatrixInvert( float * matrixIn, float * matrixOut );

#endif
