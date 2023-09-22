
 
// UPDATED: 2016-08-25  (Y. Hu: Microsoft Visual Studio 2015; System configuration - Windows 7 + 16:9 screen ratio)
// UPDATED: 2018-08-02  (Y. Hu: Microsoft Visual Studio 2017; System configuration - Windows 7 + 16:9 screen ratio)
// UPDATED: 2021-07-19  (Y. Hu: Microsoft Visual Studio 2019; System configuration - Windows 10 + 16:9 screen ratio) 

#include "vectorMath.h"

void MultVectorByMatrix( float * matrix, float * vectorIn, float * vectorOut ){

	vectorOut[0] = vectorIn[0] * matrix[0*4+0] +
        vectorIn[1] * matrix[1*4+0] +
        vectorIn[2] * matrix[2*4+0] +
                 matrix[3*4+0];

	vectorOut[1] = vectorIn[0] * matrix[0*4+1] +
        vectorIn[1] * matrix[1*4+1] +
        vectorIn[2] * matrix[2*4+1] +
                 matrix[3*4+1];

	vectorOut[2] = vectorIn[0] * matrix[0*4+2] +
        vectorIn[1] * matrix[1*4+2] +
        vectorIn[2] * matrix[2*4+2] +
                 matrix[3*4+2];

}

void MultVector4ByMatrix( float * matrix, float * vectorIn, float * vectorOut ){

	vectorOut[0] = vectorIn[0] * matrix[0*4+0] +
        vectorIn[1] * matrix[1*4+0] +
        vectorIn[2] * matrix[2*4+0] +
                 matrix[3*4+0];

	vectorOut[1] = vectorIn[0] * matrix[0*4+1] +
        vectorIn[1] * matrix[1*4+1] +
        vectorIn[2] * matrix[2*4+1] +
                 matrix[3*4+1];

	vectorOut[2] = vectorIn[0] * matrix[0*4+2] +
        vectorIn[1] * matrix[1*4+2] +
        vectorIn[2] * matrix[2*4+2] +
                 matrix[3*4+2];

	vectorOut[3] = vectorIn[0] * matrix[0*4+3] +
        vectorIn[1] * matrix[1*4+3] +
        vectorIn[2] * matrix[2*4+3] +
                 matrix[3*4+3];

}


void MultVectorByMatrix( double * matrix, double * vectorIn, double * vectorOut ){

	vectorOut[0] = vectorIn[0] * matrix[0*4+0] +
        vectorIn[1] * matrix[1*4+0] +
        vectorIn[2] * matrix[2*4+0] +
                 matrix[3*4+0];

	vectorOut[1] = vectorIn[0] * matrix[0*4+1] +
        vectorIn[1] * matrix[1*4+1] +
        vectorIn[2] * matrix[2*4+1] +
                 matrix[3*4+1];

	vectorOut[2] = vectorIn[0] * matrix[0*4+2] +
        vectorIn[1] * matrix[1*4+2] +
        vectorIn[2] * matrix[2*4+2] +
                 matrix[3*4+2];

}

void MultVector4ByMatrix( double * matrix, double * vectorIn, double * vectorOut ){

	vectorOut[0] = vectorIn[0] * matrix[0*4+0] +
        vectorIn[1] * matrix[1*4+0] +
        vectorIn[2] * matrix[2*4+0] +
                 matrix[3*4+0];

	vectorOut[1] = vectorIn[0] * matrix[0*4+1] +
        vectorIn[1] * matrix[1*4+1] +
        vectorIn[2] * matrix[2*4+1] +
                 matrix[3*4+1];

	vectorOut[2] = vectorIn[0] * matrix[0*4+2] +
        vectorIn[1] * matrix[1*4+2] +
        vectorIn[2] * matrix[2*4+2] +
                 matrix[3*4+2];

	vectorOut[3] = vectorIn[0] * matrix[0*4+3] +
        vectorIn[1] * matrix[1*4+3] +
        vectorIn[2] * matrix[2*4+3] +
                 matrix[3*4+3];

}

void MatrixInvert( float * matrixIn, float * matrixOut ){

  //I don't know if this will work...
  //Let's just try something simple here!

  float matrixIn1 = matrixIn[1];
  float matrixIn2 = matrixIn[2];
  float matrixIn6 = matrixIn[6];

  matrixOut[3*4+0] = -matrixIn[3*4+0];
  matrixOut[3*4+1] = -matrixIn[3*4+1];
  matrixOut[3*4+2] = -matrixIn[3*4+2];

  matrixOut[0] = matrixIn[0];
  matrixOut[5] = matrixIn[5];
  matrixOut[10]= matrixIn[10];

  matrixOut[3] = matrixIn[3];
  matrixOut[7] = matrixIn[7];
  matrixOut[11] = matrixIn[11];
  matrixOut[15] = matrixIn[15];


  matrixOut[1] = matrixIn[4];
  matrixOut[2] = matrixIn[8];
  matrixOut[6] = matrixIn[9];

  matrixOut[4] = matrixIn1;
  matrixOut[8] = matrixIn2;
  matrixOut[9] = matrixIn6;

}
