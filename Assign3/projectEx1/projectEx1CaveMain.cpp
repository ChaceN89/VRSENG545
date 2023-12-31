#ifdef WIN32
#include <windows.h>
#endif

#ifdef WIN32
#include <sys/timeb.h>
#endif

// UPDATED: 2016-08-25  (Y. Hu: Microsoft Visual Studio 2015; System configuration - Windows 7 + 16:9 screen ratio)
// UPDATED: 2018-08-02  (Y. Hu: Microsoft Visual Studio 2017; System configuration - Windows 7 + 16:9 screen ratio)
// UPDATED: 2021-07-19  (Y. Hu: Microsoft Visual Studio 2019; System configuration - Windows 10 + 16:9 screen ratio) 

#include <stdio.h>
#include "caveMain.h"
#include "cave_ogl.h"

void init_gl(void);
void draw(void);
void frame(void);
void cleanup(void);

int main(int argc,char **argv)
{

	//for CAVELib compatibility, this function will most likely do nothing...
    CAVEConfigure( &argc, argv, NULL);

	//register your per-context (per-window) initialization function
    CAVEInitApplication( (CAVECALLBACK)init_gl, 0 );
    
	//register your pre-frame function
    CAVEFrameFunction( (CAVECALLBACK)frame, 0 );

    //register your isplay function
    CAVEDisplay( (CAVECALLBACK)draw, 0 );

#ifdef KNAVE_LIB
    //register your cleanup function
    // (Because of the way glut does things under the hood,
    //  we have to register it ahead of time,
    //  to get it called back when we quit. )
    CAVEStopApplication( (CAVECALLBACK)cleanup, 0 );
#endif

    //get things going!
    CAVEInit();

    // Usually, in a CAVELib App, we wait for the escape key
    // to be hit then call CAVEExit, but KNAVELib is going to
    // handle that for us...

#ifndef KNAVE_LIB

    while (!CAVEgetbutton(CAVE_ESCKEY))
    {
      // Nap so that this busy loop doesn't waste CPU time 
      // reset timeval struct every time for linux compatibility 
      timeval tval;
      tval.tv_usec = 25000;
      tval.tv_sec = 0;
      select(0,NULL,NULL,NULL,&tval);
      //printf( "App running\n");
    }
    
    //call your cleanup function
    CAVEStopApplication( (CAVECALLBACK)cleanup, 0 );

    CAVEExit();

#endif

    return 0;
}

void init_gl(void)
{
	printf( "Initialized.\n" );

	/* Use depth buffering for hidden surface elimination. */
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_COLOR_MATERIAL );

	glDisable( GL_LIGHTING );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_NONE );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

}


double rotateAmt = 0.0;

void frame(void)
{
    //printf( "Frame Update.\n" );

    if( CAVEBUTTON1 ) printf( "Button 1 Down\n" );
    if( CAVEBUTTON2 ) printf( "Button 2 Down\n" );
    if( CAVEBUTTON3 ) printf( "Button 3 Down\n" );
	
    //timing for navigation!

    float jx, jy, dt, t;
    
    const float SPEED = 2.0f;

    static float prevtime = 0;

    jx=CAVE_JOYSTICK_X;
    jy=CAVE_JOYSTICK_Y;
    t = CAVEGetTime();
    dt = t - prevtime;

    ////// Frames Per Second Counter //////
    
    if( CAVEMasterDisplay() ){
      
      static int frameCount = 0;
      static float lastFpsTime = t;

      ++frameCount;
      if( t-lastFpsTime > 1.0 ){
	printf( "fps: %d %f %f %f\n", frameCount, dt, t, prevtime );
	frameCount = 0;
	lastFpsTime = t;
      }

    }
    
    prevtime = t;

    if (fabs(jy)>0.1 ){
      float wandFront[3];
      CAVEGetVector(CAVE_WAND_FRONT,wandFront);
      CAVENavTranslate(wandFront[0]*jy*SPEED*dt, wandFront[1]*jy*SPEED*dt,
		       wandFront[2]*jy*SPEED*dt);
    }
    if (fabs(jx)>0.2 )
	CAVENavRot(-jx*25.0f*dt,'y');


	rotateAmt += 180.0 * dt;

}

void draw(void)
{

	//printf( "Drawing.\n" );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	/* Code responsible to setup aspect ratio and frusturm (NO NEED TO CHANGE UNLESS YOU KNOW AWHAT YOU ARE DOING) */
	double dx0 = -0.070 / 4.0; 
	double dx1 = 0.40 / 4.0; 

	double frustumTop = 1.0;
	double frustumRight = 1.7777; //Monitor aspect ratio is 16:9 = 1.7777
	double CAVENear = 1.0;
	double CAVEFar = 10000.0;

	glDrawBuffer(GL_BACK_LEFT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-frustumRight-dx0, frustumRight-dx0, -frustumTop, frustumTop,CAVENear,CAVEFar);
	glTranslatef(0+dx1,0,0);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);

	/* Draw the CAVE*/
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	float headPos[3];
	float headVec[3];

	CAVEGetPosition( CAVE_HEAD, headPos );

	glPushMatrix();

	glTranslatef( headPos[0], headPos[1], headPos[2] );

	glDisable( GL_LIGHTING );

	//headLines
	CAVEGetVector( CAVE_HEAD_FRONT, headVec );
	glBegin( GL_LINES );
		glColor3f( 1,1,1 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_HEAD_BACK, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_HEAD_LEFT, headVec );
	glBegin( GL_LINES );
		glColor3f( 1,1,1 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_HEAD_RIGHT, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_HEAD_UP, headVec );
	glBegin( GL_LINES );
		glColor3f( 1,1,1 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_HEAD_DOWN, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();

	glPopMatrix();

	//wand lines
	CAVEGetPosition( CAVE_WAND, headPos );
	glPushMatrix();
	glTranslatef( headPos[0], headPos[1], headPos[2] );

	CAVEGetVector( CAVE_WAND_FRONT, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.99,0.99,0.99 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_WAND_BACK, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_WAND_LEFT, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.99,0.99,0.99 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_WAND_RIGHT, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_WAND_UP, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.99,0.99,0.99 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_WAND_DOWN, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();

	glPopMatrix();


	CAVENavTransform();

	glBegin( GL_QUADS );

	glColor3f( 0.81, 0.81, 0.81 );

	for( int i=-50; i<50;++i ){
		int shift = i%2;
		for( int j=-50; j<50;j+=2 ){
			
			glVertex3f( j+shift+1, 0,  i   );
			glVertex3f( j+shift,   0,  i   );
			glVertex3f( j+shift,   0,  i+1 );
			glVertex3f( j+shift+1, 0,  i+1 );
			
		}
	}

	glEnd();

	//navigated head-lines
	CAVEGetPosition( CAVE_HEAD_NAV, headPos );
	glPushMatrix();
	glTranslatef( headPos[0], headPos[1], headPos[2] );

	//Begin test of head/wand vectors in navigated coords
	CAVEGetVector( CAVE_HEAD_FRONT_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 1,1,1 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_HEAD_BACK_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_HEAD_LEFT_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 1,1,1 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_HEAD_RIGHT_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_HEAD_UP_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 1,1,1 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_HEAD_DOWN_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();

	glPopMatrix();

	//wand lines
	CAVEGetPosition( CAVE_WAND_NAV, headPos );
	glPushMatrix();
	glTranslatef( headPos[0], headPos[1], headPos[2] );

	CAVEGetVector( CAVE_WAND_FRONT_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.99,0.99,0.99 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_WAND_BACK_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_WAND_LEFT_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.99,0.99,0.99 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_WAND_RIGHT_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_WAND_UP_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.99,0.99,0.99 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();
	CAVEGetVector( CAVE_WAND_DOWN_NAV, headVec );
	glBegin( GL_LINES );
		glColor3f( 0.5,0.5,0.5 );
		glVertex3f( 0, 0, 0 );
		glVertex3f(headVec[0], headVec[1], headVec[2] );
	glEnd();


	glPopMatrix();

	//glEnable( GL_LIGHTING );
	//end nav vectors test

	 /* Draw triangles */
	//triangle 1
	glPushMatrix();

	glTranslatef( 0, 0, -2.0 );

	glRotatef( rotateAmt, 0, 1, 0 );

	glBegin( GL_TRIANGLES );
		glColor3f( 0.7, 0.7, 0.7 );
		glVertex3f( -1.0, -0.5, 0.0 );
		glVertex3f(  0.0,  1.0, 0.0 );
		glVertex3f(  1.0, -0.5, 0.0 );
	glEnd();

	glPopMatrix();

	//triangle 2
	glPushMatrix();

	glTranslatef( -6, 0, 0.0 );

	glRotatef( rotateAmt, 0, 1, 0 );

	glBegin( GL_TRIANGLES );
		glColor3f( 1, 0, 0 );
		glVertex3f( -1.0, -0.5, 0.0 );
		glColor3f(0, 1, 0);
		glVertex3f(  0.0,  1.0, 0.0 );
		glColor3f(0, 0, 1);
		glVertex3f(  1.0, -0.5, 0.0 );
	glEnd();

	glPopMatrix();

	//triangle 3
	glPushMatrix();

	glTranslatef( 6, 0, 0.0 );

	glRotatef( rotateAmt, 1, 0, 0 );

	glBegin( GL_POLYGON );
		glColor3f( 0.8, 0.4, 0 );
		glVertex3f(-0.75, -0.75, 0.0);
		glVertex3f(0.75, -0.75, 0.0);
		glVertex3f(0.75, 0.75, 0.0);
		glVertex3f(-0.75, 0.75, 0.0);
	glEnd();

	glPopMatrix();

	//triangle 4
	glPushMatrix();

	glTranslatef( 0, 0, -6.0 );

	glRotatef( rotateAmt, 0, 0.0 , 0.05f);

	glBegin( GL_TRIANGLES );
		glColor3f( 0, 0, 1 );

		
		//LEFT
		glVertex3f(0.0, 5.0, 0.0);
		glVertex3f(-2.5, -2.5, 2.5);
		glVertex3f(  2.5,  -2.5, 0 );
		
		glColor3f(0, 1, 0);
		//RIGHT
		glVertex3f(0.0, 5.0, 0.0);
		glVertex3f(2.5, -2.5, 0.0);
		
		glVertex3f(-2.5, -2.5, -2.5);
		
		
		
		//LEFT
		glColor3f(1, 0, 0);
		glVertex3f(0.0, 5.0, 0.0);
		glVertex3f(-2.5, -2.5, -2.5);
		
		glVertex3f(-2.5, -2.5, 2.5);
		
		
		//BOTTOM
		glColor3f(0.5, 0.5, 0);
		glVertex3f(2.5, -2.5, 0.0);
		glVertex3f(-2.5, -2.5, 2.5);
		glVertex3f(-2.5, -2.5, -2.5);
		
	glEnd();

	glPopMatrix();

	glPopMatrix();

	glFlush();

}

void cleanup(void)
{
	printf( "Cleaning Up.\n" );
}

