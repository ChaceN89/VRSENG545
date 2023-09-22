#ifndef PointManipulationAfx_H_
#define PointManipulationAfx_H_

// UPDATED: 2016-08-25  (Y. Hu: Microsoft Visual Studio 2015; System configuration - Windows 7 + 16:9 screen ratio)
// UPDATED: 2018-08-02  (Y. Hu: Microsoft Visual Studio 2017; System configuration - Windows 7 + 16:9 screen ratio)
// UPDATED: 2021-07-19  (Y. Hu: Microsoft Visual Studio 2019; System configuration - Windows 10 + 16:9 screen ratio) 

#if defined(WIN32)
// identifier was truncated to '255' characters in the debug information.
# pragma warning( disable: 4786 )
# include <windows.h>
#endif // WIN32

#if defined(WIN32) || defined(linux)
#include "cave_ogl.h"
#elif defined(__APPLE__)
# include <GLUT/glut.h>
#endif

#endif // PointManipulationAfx_H_
