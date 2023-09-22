 
// UPDATED: 2016-08-25  (Y. Hu: Microsoft Visual Studio 2015; System configuration - Windows 7 + 16:9 screen ratio) 
// UPDATED: 2018-08-02  (Y. Hu: Microsoft Visual Studio 2017; System configuration - Windows 7 + 16:9 screen ratio)
// UPDATED: 2021-07-19  (Y. Hu: Microsoft Visual Studio 2019; System configuration - Windows 10 + 16:9 screen ratio) 


#include <stdlib.h>
#include <GL/glut.h>
//#include <pthread.h>

#ifdef WIN32
	#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "cave_ogl.h"

#include "vectorMath.h"

CAVECALLBACK initFunc  = 0;
CAVECALLBACK frameFunc = 0;
CAVECALLBACK drawFunc  = 0;
CAVECALLBACK stopFunc  = 0;
float CAVENear = 1.0;
float CAVEFar = 10000.0;

int CAVEEye = CAVE_LEFT_EYE;
int CAVEWall = CAVE_SIMULATOR_WALL;

CAVE_ST * CAVEptr = 0;

char *CAVEVersion = "KNAVELib 0.0.1 - A Limited Functionality CAVELib Simulator";

float * CAVETime = new float;
float * _CAVE_JOYSTICK_X = new float;
float * _CAVE_JOYSTICK_Y = new float;

int CAVEButtons[CAVE_MAX_BUTTONS] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
int CAVEButtonChanges[CAVE_MAX_BUTTONS] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };

float _headPos[3] = { 0.0, 5.0, 0.0 };
float _wandPos[3] = { 0.0, 4.0, 1.0 };

float _headOri[3] = { 0.0, 0.0, 0.0 };
float _wandOri[3] = { 0.0, 0.0, 0.0 };

float headMatrix[16] = { 1,0,0,0,
					    0,1,0,0,
						0,0,1,0,
						0,0,0,1 };
float wandMatrix[16] = { 1,0,0,0,
					    0,1,0,0,
						0,0,1,0,
						0,0,0,1 };

float NavMatrix[16] = { 1,0,0,0,
					    0,1,0,0,
						0,0,1,0,
						0,0,0,1 };

float navRot[3]   = {0,0,0};
float navTrans[3] = {0,0,0};
float navScale[3] = {1,1,1};


const int MAX_KEYS = 512;
unsigned char keys[MAX_KEYS];

int lastX = 0;
int lastY = 0;

int initArgs = 0;
void *initArg1 = 0, *initArg2 = 0, *initArg3 = 0, *initArg4 = 0, *initArg5 = 0;

int frameArgs = 0;
void *frameArg1 = 0, *frameArg2 = 0, *frameArg3 = 0, *frameArg4 = 0, *frameArg5 = 0;

int drawArgs = 0;
void *drawArg1 = 0, *drawArg2 = 0, *drawArg3 = 0, *drawArg4 = 0, *drawArg5 = 0;

int stopArgs = 0;
void *stopArg1 = 0, *stopArg2 = 0, *stopArg3 = 0, *stopArg4 = 0, *stopArg5 = 0;

int bJoystickOn = 0;

unsigned int CAVEFrameNumber = 0;

int lastModifiers = 0;

void KNAVEFrame();
void KNAVEDisplay();
void drawEye(int eye);

void KNAVEInit(){

	if(initFunc != 0){
		initFunc();
	}

}

void KNAVEFrame(){

	*CAVETime = CAVEGetTime();
	++CAVEFrameNumber;

	if(frameFunc != 0 ){
		frameFunc();
	}

	glutPostRedisplay();

	//KNAVEDisplay();

}

void KNAVEDisplay(){
		/* Setup the view of the cube. */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( /* field of view in degree */ 90.0, /* aspect ratio */ 1.7777778, /* Z near */ CAVENear, /* Z far */ CAVEFar );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	//these are just for getting matrices to orient the wand and head
	glPushMatrix();
		glRotatef( _wandOri[1], 0, 1, 0 );
		glRotatef( _wandOri[0], 1, 0, 0 );
		glRotatef( _wandOri[2], 0, 0, 1 );
		glGetFloatv( GL_MODELVIEW_MATRIX, wandMatrix );
		wandMatrix[12] = wandMatrix[13] = wandMatrix[14] = 0.0;
	glPopMatrix();

	glPushMatrix();
		glRotatef( _headOri[1], 0, 1, 0 );
		glRotatef( _headOri[0], 1, 0, 0 );
		glRotatef( _headOri[2], 0, 0, 1 );
		glGetFloatv( GL_MODELVIEW_MATRIX, headMatrix );
		headMatrix[12] = headMatrix[13] = headMatrix[14] = 0.0;
	glPopMatrix();

	glTranslatef( 0, -5, -7 );

	glPushMatrix();

	if(drawFunc != 0 ){
		drawFunc();
	}

	glPopMatrix();

	glDisable( GL_LIGHTING );

	glPushMatrix();
		glTranslatef( 0, 5, 0 );
		glScalef( 1.2, 1.0, 1.2 );
		glutWireCube( 10 );
	glPopMatrix();
	
	//glEnable( GL_LIGHTING );
	//GLfloat light0_position[] = {0.2f, 0.7f, 0.7f, 0.0f};
	//glLightfv(GL_LIGHT0, GL_POSITION,  light0_position);
	//glEnable( GL_LIGHT0 );

	glPushMatrix();
		glTranslatef( _wandPos[0], _wandPos[1], _wandPos[2] );
		//glRotatef( 180, 1, 0, 0 );
		glRotatef( _wandOri[1], 0, 1, 0 );
		glRotatef( _wandOri[0], 1, 0, 0 );
		glRotatef( _wandOri[2], 0, 0, 1 );
		glColor3f( 1, 0, 0 );
		glutSolidCone( 0.4, 0.5, 12, 1 );
	glPopMatrix();

	glPushMatrix();
		glTranslatef( _headPos[0], _headPos[1], _headPos[2] );
		//glRotatef( 180, 1, 0, 0 );
		glRotatef( _headOri[1], 0, 1, 0 );
		glRotatef( _headOri[0], 1, 0, 0 );
		glRotatef( _headOri[2], 0, 0, 1 );
		glColor3f( 0, 0, 1 );
		glutSolidCone( 0.6, 0.5, 12, 1 );
	glPopMatrix();

	glEnable( GL_LIGHTING );

	glutSwapBuffers();


}

void keyPress(unsigned char key, int x, int y){

	if( key == 27 ){
		CAVEExit();
		exit( 0 );
	}

	if( key == 32 ){
		//spacebar down
		if(bJoystickOn){
			
			int width = glutGet( GLUT_WINDOW_WIDTH );
			int height = glutGet( GLUT_WINDOW_HEIGHT );		

			*_CAVE_JOYSTICK_X = (x-(width/2.0))/(width/2.0);
			*_CAVE_JOYSTICK_Y = -(y-(height/2.0))/(height/2.0);
				
			bJoystickOn = 0;
			*_CAVE_JOYSTICK_X = 0.0;
			*_CAVE_JOYSTICK_Y = 0.0;
		}
		else{
			bJoystickOn = 1;
			
			int width = glutGet( GLUT_WINDOW_WIDTH );
			int height = glutGet( GLUT_WINDOW_HEIGHT );		

			*_CAVE_JOYSTICK_X = (x-(width/2.0))/(width/2.0);
			*_CAVE_JOYSTICK_Y = -(y-(height/2.0))/(height/2.0);
			
		}

		//printf( "Joystick X: %f, Joystick Y: %f \n", *_CAVE_JOYSTICK_X, *_CAVE_JOYSTICK_Y );
	}

	for( int i=0; i<MAX_KEYS; i++ ) keys[i]=0;

	//printf( "%c pressed (as int: %d)\n", key, (int)key );

	keys[key] = 1;

	lastModifiers = glutGetModifiers();

}

void specialKeyPress(int key, int x, int y){

	int dummy;

	switch( key ){
	case GLUT_KEY_LEFT:
		if( (dummy = glutGetModifiers()) &= GLUT_ACTIVE_ALT )
			_headOri[1] -= 1.1;
		else
			_headPos[0] -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		if( (dummy = glutGetModifiers()) &= GLUT_ACTIVE_ALT )
			_headOri[1] += 1.1;
		else
			_headPos[0] += 0.1;
		break;
	case GLUT_KEY_UP:
		if( (dummy = glutGetModifiers()) &= GLUT_ACTIVE_CTRL )
			_headPos[1] += 0.1;
		else if( (dummy = glutGetModifiers()) &= GLUT_ACTIVE_ALT )
			_headOri[0] += 1.1;
		else
			_headPos[2] -= 0.1;
		break;
	case GLUT_KEY_DOWN:
		if( (dummy = glutGetModifiers()) &= GLUT_ACTIVE_CTRL )
			_headPos[1] -= 0.1;
		else if( (dummy = glutGetModifiers()) &= GLUT_ACTIVE_ALT )
			_headOri[0] -= 1.1;
		else
			_headPos[2] += 0.1;
		break;
		break;
	}

	if( _headPos[0] >  6.0 ) _headPos[0] =  6.0;
	if( _headPos[0] < -6.0 ) _headPos[0] = -6.0;
	
	if( _headPos[1] >  10.0 ) _headPos[1] =  10.0;
	if( _headPos[1] <   0.0 ) _headPos[1] =  0.0;

	if( _headPos[2] >  6.0 ) _headPos[2] =  6.0;
	if( _headPos[2] < -6.0 ) _headPos[2] = -6.0;


	lastModifiers = glutGetModifiers();
}

int GetModifiers(){

       
#ifdef WIN32

  int result = 0;

  if( GetAsyncKeyState( VK_CONTROL ) < 0 ) result |= GLUT_ACTIVE_CTRL;
  if( GetAsyncKeyState( VK_SHIFT ) < 0 )   result |= GLUT_ACTIVE_SHIFT;
  if( GetAsyncKeyState( VK_MENU ) < 0 )    result |= GLUT_ACTIVE_ALT;
  return result;
#else
  //what to do here!!!
  return lastModifiers;
#endif
	
}

void passiveMotionFunction(int x, int y){

	//printf( "Passive. X: %d, Y: %d\n", x, y );

	int dummy;

	static int startXCtrl = x;
	static int startYCtrl = y;

	lastX = x;
	lastY = y;

	int width = glutGet( GLUT_WINDOW_WIDTH );
	int height = glutGet( GLUT_WINDOW_HEIGHT );

	if( (dummy = GetModifiers()) &= GLUT_ACTIVE_CTRL ){

		if( (x - startXCtrl) > 0) _wandPos[0] += 0.05 * (x - startXCtrl);
		if( (x - startXCtrl) < 0) _wandPos[0] += 0.05 * (x - startXCtrl);

		if( (y - startYCtrl) > 0) _wandPos[2] += 0.05 * (y - startYCtrl);
		if( (y - startYCtrl) < 0) _wandPos[2] += 0.05 * (y - startYCtrl);

		startXCtrl = x;
		startYCtrl = y;
	}
	else if( (dummy = GetModifiers()) &= GLUT_ACTIVE_SHIFT ){

		if( (x - startXCtrl) > 0) _wandPos[0] += 0.05 * (x - startXCtrl);
		if( (x - startXCtrl) < 0) _wandPos[0] += 0.05 * (x - startXCtrl);

		if( (y - startYCtrl) > 0) _wandPos[1] -= 0.05 * (y - startYCtrl);
		if( (y - startYCtrl) < 0) _wandPos[1] -= 0.05 * (y - startYCtrl);

		startXCtrl = x;
		startYCtrl = y;
	}
	else if( (dummy = GetModifiers()) &= GLUT_ACTIVE_ALT ){

		if( (x - startXCtrl) > 0) _wandOri[1] += 0.15 * (x - startXCtrl);
		if( (x - startXCtrl) < 0) _wandOri[1] += 0.15 * (x - startXCtrl);

		if( (y - startYCtrl) > 0) _wandOri[0] -= 0.15 * (y - startYCtrl);
		if( (y - startYCtrl) < 0) _wandOri[0] -= 0.15 * (y - startYCtrl);

		startXCtrl = x;
		startYCtrl = y;
	}
	else{

		startXCtrl = x;
		startYCtrl = y;	

	}

	if( _wandPos[0] >  6.0 ) _wandPos[0] =  6.0;
	if( _wandPos[0] < -6.0 ) _wandPos[0] = -6.0;
	
	if( _wandPos[1] >  10.0 ) _wandPos[1] =  10.0;
	if( _wandPos[1] <   0.0 ) _wandPos[1] =  0.0;

	if( _wandPos[2] >  6.0 ) _wandPos[2] =  6.0;
	if( _wandPos[2] < -6.0 ) _wandPos[2] = -6.0;


	if(bJoystickOn){
		int width = glutGet( GLUT_WINDOW_WIDTH );
		int height = glutGet( GLUT_WINDOW_HEIGHT );		

		*_CAVE_JOYSTICK_X = (x-(width/2.0))/(width/2.0);
		*_CAVE_JOYSTICK_Y = -(y-(height/2.0))/(height/2.0);
	}

}

void motionFunction(int x, int y){

	//printf( "X: %d, Y: %d\n", x, y );

	int dummy;

	static int startXCtrl = x;
	static int startYCtrl = y;

	lastX = x;
	lastY = y;

	int width = glutGet( GLUT_WINDOW_WIDTH );
	int height = glutGet( GLUT_WINDOW_HEIGHT );

	if( (dummy = GetModifiers()) &= GLUT_ACTIVE_CTRL ){

		if( (x - startXCtrl) > 0) _wandPos[0] += 0.05 * (x - startXCtrl);
		if( (x - startXCtrl) < 0) _wandPos[0] += 0.05 * (x - startXCtrl);

		if( (y - startYCtrl) > 0) _wandPos[2] += 0.05 * (y - startYCtrl);
		if( (y - startYCtrl) < 0) _wandPos[2] += 0.05 * (y - startYCtrl);

		startXCtrl = x;
		startYCtrl = y;
	}
	else if( (dummy = GetModifiers()) &= GLUT_ACTIVE_SHIFT ){

		if( (x - startXCtrl) > 0) _wandPos[0] += 0.05 * (x - startXCtrl);
		if( (x - startXCtrl) < 0) _wandPos[0] += 0.05 * (x - startXCtrl);

		if( (y - startYCtrl) > 0) _wandPos[1] -= 0.05 * (y - startYCtrl);
		if( (y - startYCtrl) < 0) _wandPos[1] -= 0.05 * (y - startYCtrl);

		startXCtrl = x;
		startYCtrl = y;
	}
	else if( (dummy = GetModifiers()) &= GLUT_ACTIVE_ALT ){

		if( (x - startXCtrl) > 0) _wandOri[1] += 0.15 * (x - startXCtrl);
		if( (x - startXCtrl) < 0) _wandOri[1] += 0.15 * (x - startXCtrl);

		if( (y - startYCtrl) > 0) _wandOri[0] -= 0.15 * (y - startYCtrl);
		if( (y - startYCtrl) < 0) _wandOri[0] -= 0.15 * (y - startYCtrl);

		startXCtrl = x;
		startYCtrl = y;
	}
	else{

		startXCtrl = x;
		startYCtrl = y;	

	}

	if( _wandPos[0] >  6.0 ) _wandPos[0] =  6.0;
	if( _wandPos[0] < -6.0 ) _wandPos[0] = -6.0;
	
	if( _wandPos[1] >  10.0 ) _wandPos[1] =  10.0;
	if( _wandPos[1] <   0.0 ) _wandPos[1] =  0.0;

	if( _wandPos[2] >  6.0 ) _wandPos[2] =  6.0;
	if( _wandPos[2] < -6.0 ) _wandPos[2] = -6.0;


	if(bJoystickOn){
		int width = glutGet( GLUT_WINDOW_WIDTH );
		int height = glutGet( GLUT_WINDOW_HEIGHT );		

		*_CAVE_JOYSTICK_X = (x-(width/2.0))/(width/2.0);
		*_CAVE_JOYSTICK_Y = -(y-(height/2.0))/(height/2.0);
	}


}

void mouseFunction(int button, int state, int x, int y){

	printf( "Mouse Button %d, state %d\n", button, state );

	if( button == GLUT_LEFT_BUTTON ){
		
		if( state == GLUT_DOWN ){
			CAVEButtons[0] = 1;
			CAVEButtonChanges[0] = 1;
			keys[ CAVE_LEFTMOUSE ] = 1;
		}
		else{
			CAVEButtons[0] = 0;
			CAVEButtonChanges[0] = -1;
			keys[ CAVE_LEFTMOUSE ] = 0;
		}
	}

	if( button == GLUT_MIDDLE_BUTTON ){
		CAVEButtonChanges[1] = 1;
		if( state == GLUT_DOWN ){
			CAVEButtons[1] = 1;
			CAVEButtonChanges[1] = 1;
			keys[ CAVE_MIDDLEMOUSE ] = 1;
		}
		else{
			CAVEButtons[1] = 0;
			CAVEButtonChanges[1] = -1;
			keys[ CAVE_MIDDLEMOUSE ] = 0;
		}
	}

	if( button == GLUT_RIGHT_BUTTON ){
		CAVEButtonChanges[2] = 1;
		if( state == GLUT_DOWN ){
			CAVEButtons[2] = 1;
			CAVEButtonChanges[2] = 1;
			keys[ CAVE_RIGHTMOUSE ] = 1;
		}
		else{
			CAVEButtons[2] = 0;
			CAVEButtonChanges[2] = -1;
			keys[ CAVE_RIGHTMOUSE ] = 0;
		}
	}

}

void CAVEConfigure( int * argc, char** argv, char** appdefaults){

	glutInit( argc, argv );

	CAVEptr = new CAVE_ST;
	CAVEptr->sensor = (volatile CAVE_SENSOR_ST **)new CAVE_SENSOR_ST*[CAVE_MAX_SENSORS];

}

void CAVEInit( void ){

  int res;

	printf( "Initializing KNAVELib\n" );

	*CAVETime = 0.0;
	*_CAVE_JOYSTICK_X = 0.0;
	*_CAVE_JOYSTICK_Y = 0.0;

	glutInitWindowSize( 12.0 * 40.0, 10.0 * 40.0 );
	glutInitWindowPosition( 100, 100 );

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH |GLUT_STEREO);
	res = glutGet( GLUT_DISPLAY_MODE_POSSIBLE );

	if( !res ){
	  /*  for Graphic computers at ENA10A
	  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH |GLUT_STEREO);
		*/
		// for non graphic computers at ICT217
	   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	  
	}

	glutCreateWindow("KNAVELib - CAVE Simulator Window");

	glutFullScreen();
	glutKeyboardFunc( keyPress );
	glutSpecialFunc( specialKeyPress );
	glutMotionFunc( motionFunction );
	glutPassiveMotionFunc( passiveMotionFunction );
	glutMouseFunc( mouseFunction );

	glutIdleFunc(KNAVEFrame);
	glutDisplayFunc(KNAVEDisplay);

	KNAVEInit();

	glutMainLoop();

}

void CAVEInitApplication( CAVECALLBACK function, int num_args, void * arg1, void * arg2, void * arg3, void * arg4, void * arg5 ){

	initFunc = function;
	initArgs = num_args;
	initArg1 = arg1;
	initArg2 = arg2;
	initArg3 = arg3;
	initArg4 = arg4;
	initArg5 = arg5;

}

void CAVEFrameFunction( CAVECALLBACK function, int num_args, void * arg1, void * arg2, void * arg3, void * arg4, void * arg5 ){

	frameFunc = function;
	frameArgs = num_args;
	frameArg1 = arg1;
	frameArg2 = arg2;
	frameArg3 = arg3;
	frameArg4 = arg4;
	frameArg5 = arg5;

}

void CAVEDisplay( CAVECALLBACK function, int num_args, void * arg1, void * arg2, void * arg3, void * arg4, void * arg5 ){

	drawFunc = function;
	drawArgs = num_args;
	drawArg1 = arg1;
	drawArg2 = arg2;
	drawArg3 = arg3;
	drawArg4 = arg4;
	drawArg5 = arg5;

}

void CAVEStopApplication( CAVECALLBACK function, int num_args, void * arg1, void * arg2, void * arg3, void * arg4, void * arg5 ){

	stopFunc = function;
	stopArgs = num_args;
	stopArg1 = arg1;
	stopArg2 = arg2;
	stopArg3 = arg3;
	stopArg4 = arg4;
	stopArg5 = arg5;

}

void CAVEExit(){

	if(stopFunc != 0){
		stopFunc();
	}

}

int CAVEgetbutton( int buttonID ){

	return keys[buttonID];

}

int CAVEgetvaluator( CAVEDevice dev ){

	printf( "CAVEgetvaluator: I'm not sure this is implemented correctly!\n" );
	return keys[dev];
	return 0;

}

void CAVEDisplayBarrier(){ return; }

void * CAVEMalloc( int size ){
	return malloc( size );
}

void CAVEFree( void * data ){
	free( data );
}

//TBD: Make these do something useful!
void CAVEGetOrientation( CAVEID oname, float *angle ){

	switch( oname ){
	case CAVE_HEAD: case CAVE_LEFT_EYE: case CAVE_RIGHT_EYE:
		angle[0] = _headOri[0];
		angle[1] = _headOri[1];
		angle[2] = _headOri[2];
		break;
	case CAVE_WAND:
		angle[0] = _wandOri[0];
		angle[1] = _wandOri[1];
		angle[2] = _wandOri[2];
		break;
	case CAVE_HEAD_NAV: case CAVE_LEFT_EYE_NAV: case CAVE_RIGHT_EYE_NAV:
		angle[0] = angle[1] = angle[2] = 0.0;
		break;
	case CAVE_WAND_NAV:
		angle[0] = angle[1] = angle[2] = 0.0;
		break;
	default:
		angle[0] = angle[1] = angle[2] = 0.0;
		break;
	}

	
}

void CAVEGetPosition( CAVEID posname, float *pos ){
	
	float tempMatrix[16];

	switch( posname ){
	case CAVE_HEAD: case CAVE_LEFT_EYE: case CAVE_RIGHT_EYE:
		pos[0] = _headPos[0];
		pos[1] = _headPos[1];
		pos[2] = _headPos[2];
		break;
	case CAVE_WAND:
		pos[0] = _wandPos[0];
		pos[1] = _wandPos[1];
		pos[2] = _wandPos[2];
		break;
	case CAVE_HEAD_NAV: case CAVE_LEFT_EYE_NAV: case CAVE_RIGHT_EYE_NAV:
		
		MatrixInvert( NavMatrix, tempMatrix );
		MultVectorByMatrix( tempMatrix, _headPos, pos );

		pos[0] = pos[0] + (-navTrans[0]);
		pos[1] = pos[1] + (-navTrans[1]);
		pos[2] = pos[2] + (-navTrans[2]);

		//MultVectorByMatrix( NavMatrix, _headPos, pos );
		//pos[0] = pos[1] = pos[2] = 0.0;
		break;
	case CAVE_WAND_NAV:
		
		MatrixInvert( NavMatrix, tempMatrix );
		MultVectorByMatrix( tempMatrix, _wandPos, pos );

		pos[0] = pos[0] + (-navTrans[0]);
		pos[1] = pos[1] + (-navTrans[1]);
		pos[2] = pos[2] + (-navTrans[2]);


		//MultVectorByMatrix( NavMatrix, _wandPos, pos );
		//pos[0] = pos[1] = pos[2] = 0.0;
		break;
	default:
		printf( "CAVEGetPosition: Position for this particular item not yet implemented.\n" );
		pos[0] = pos[1] = pos[2] = 0.0;
		break;
	}


}

float CAVEGetTime(){

	int nMilliseconds = glutGet( GLUT_ELAPSED_TIME );

	return nMilliseconds/1000.0;

}

boolean CAVEMasterDisplay(){ return true; }

boolean CAVEMasterWall(){ return true; }

//TBD: Finish this?
void CAVESetOption(CAVEID option,int value){


}

int	CAVENumPipes(void){ return 1; }

int	CAVEPipeNumber(void){ return 1; }

//
// the Nav stuff!
//
void CAVENavLoadIdentity(void){

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glLoadIdentity();
	glGetFloatv( GL_MODELVIEW_MATRIX, NavMatrix );

	glPopMatrix();

}

void CAVENavLoadMatrix(float matrix[4][4]){

	for( int i=0; i<4; ++i ){
		for( int j=0; j<4; ++j ){
			NavMatrix[4*i+j] = matrix[i][j];
		}
	}

}

void CAVENavGetMatrix(float matrix[4][4]){

	for( int i=0; i<4; ++i ){
		for( int j=0; j<4; ++j ){
			 matrix[i][j] = NavMatrix[4*i+j];
		}
	}

}

void CAVENavMultMatrix(float matrix[4][4]){

	float tempMatrix[16];
	for( int i=0; i<4; ++i ){
		for( int j=0; j<4; ++j ){
			tempMatrix[4*i+j] = matrix[i][j];
		}
	}

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glLoadMatrixf( NavMatrix );
	glMultMatrixf( tempMatrix );

	glGetFloatv( GL_MODELVIEW_MATRIX, NavMatrix );

	glPopMatrix();

}

void CAVENavTranslate(float x,float y,float z){

	//NavMatrix[12]-=x;
	//NavMatrix[13]-=y;
	//NavMatrix[14]-=z;

	float vecIn[3] = {x,y,z};
	float vecOut[3] = {0,0,0};
	
	float tempMatrix[16];
	MatrixInvert( NavMatrix, tempMatrix );

	MultVectorByMatrix( tempMatrix, vecIn, vecOut );

	navTrans[0]-=vecOut[0];
	navTrans[1]-=vecOut[1];
	navTrans[2]-=vecOut[2];

	/*
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	
	glLoadMatrixf( NavMatrix );
	glTranslatef( -x, -y, -z );
	//glMultMatrixf( NavMatrix );

	glGetFloatv( GL_MODELVIEW_MATRIX, NavMatrix );

	glPopMatrix();
	*/
}

void CAVENavRot(float a,char axis){

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	float x, y, z;

	x=NavMatrix[12];
	y=NavMatrix[13];
	z=NavMatrix[14];

	glLoadMatrixf( NavMatrix );
	switch( axis ){
	case 'x': case 'X':
		glRotatef( -a, 1, 0, 0 );
		break;
	case 'y': case 'Y':
		glRotatef( -a, 0, 1, 0 );
		break;
	case 'z': case 'Z':
		glRotatef( -a, 0, 0, 1 );
		break;
	}
	//glMultMatrixf( NavMatrix );

	glGetFloatv( GL_MODELVIEW_MATRIX, NavMatrix );

	NavMatrix[12]=x;
	NavMatrix[13]=y;
	NavMatrix[14]=z;


	glPopMatrix();

}

void CAVENavScale(float x,float y,float z){

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glLoadMatrixf( NavMatrix );
	glScalef( x, y, z );

	glGetFloatv( GL_MODELVIEW_MATRIX, NavMatrix );

	glPopMatrix();

}

void CAVENavPreMultMatrix(float matrix[4][4]){

	float tempMatrix[16];
	for( int i=0; i<4; ++i ){
		for( int j=0; j<4; ++j ){
			tempMatrix[4*i+j] = matrix[i][j];
		}
	}

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glLoadMatrixf( tempMatrix );
	glMultMatrixf( NavMatrix );

	glGetFloatv( GL_MODELVIEW_MATRIX, NavMatrix );

	glPopMatrix();

}

void CAVENavWorldTranslate(float x,float y,float z){

	//convert values to CAVE coords and then call the normal function?
	printf( "CAVENavWorld...: Not implemented!\n" );

}

void CAVENavWorldRot(float a,char axis){

	//convert values to CAVE coords and then call the normal function?
	printf( "CAVENavWorld...: Not implemented!\n" );

}

void CAVENavWorldScale(float x,float y,float z){

	//convert values to CAVE coords and then call the normal function?
	printf( "CAVENavWorld...: Not implemented!\n" );

}

void CAVENavConvertWorldToCAVE(float *in,float *out){

	printf( "CAVENavConvert...: Not implemented!\n" );

}

void CAVENavConvertCAVEToWorld(float *in,float *out){

	printf( "CAVENavConvert...: Not implemented!\n" );

}

void CAVENavConvertVectorWorldToCAVE(float *in,float *out){

	printf( "CAVENavConvert...: Not implemented!\n" );

}

void CAVENavConvertVectorCAVEToWorld(float *in,float *out){

	printf( "CAVENavConvert...: Not implemented!\n" );

}

void CAVENavTransform(void){

	//glLoadMatrixf( NavMatrix );
	
	glMultMatrixf( NavMatrix );
	glTranslatef( navTrans[0], navTrans[1], navTrans[2] );

}

void CAVENavInverseTransform(void){

	float tempMatrix[16];

	for( int i=0; i<3; ++i ){
		for( int j=0; j<3; ++j ){
			tempMatrix[4*i+j] = NavMatrix[4*j+i];
		}
	}

	tempMatrix[3] = -NavMatrix[3];
	tempMatrix[7] = -NavMatrix[7];
	tempMatrix[11] = -NavMatrix[11];

	glLoadMatrixf( tempMatrix );

}

void CAVENavLock(void){

	printf( "CAVENavLock: Not implemented!\n" );
	//I'm not sure what these are supposed to do!

}

void CAVENavUnlock(void){

	printf( "CAVENavUnlock: Not implemented!\n" );
	//I'm not sure what these are supposed to do!

}

void CAVEGetVector(CAVEID vecname,float *vec){

	float upVec[3]		= {  0,  1,  0 };
	float downVec[3]	= {  0, -1,  0 };
	float leftVec[3]	= { -1,  0,  0 };
	float rightVec[3]	= {  1,  0,  0 };
	float frontVec[3]	= {  0,  0, -1 };
	float backVec[3]	= {  0,  0,  1 };
	
	float * vectorIn;
	float vectorOut[3];

	switch( vecname ){
	case CAVE_HEAD_FRONT: case CAVE_HEAD_FRONT_NAV: case CAVE_WAND_FRONT: case CAVE_WAND_FRONT_NAV:
		vectorIn = frontVec;
		break;
	case CAVE_HEAD_BACK: case CAVE_HEAD_BACK_NAV: case CAVE_WAND_BACK: case CAVE_WAND_BACK_NAV:
		vectorIn = backVec;
		break;
	case CAVE_HEAD_LEFT: case CAVE_HEAD_LEFT_NAV: case CAVE_WAND_LEFT: case CAVE_WAND_LEFT_NAV:
		vectorIn = leftVec;
		break;
	case CAVE_HEAD_RIGHT: case CAVE_HEAD_RIGHT_NAV: case CAVE_WAND_RIGHT: case CAVE_WAND_RIGHT_NAV:
		vectorIn = rightVec;
		break;
	case CAVE_HEAD_UP: case CAVE_HEAD_UP_NAV: case CAVE_WAND_UP: case CAVE_WAND_UP_NAV:
		vectorIn = upVec;
		break;
	case CAVE_HEAD_DOWN: case CAVE_HEAD_DOWN_NAV: case CAVE_WAND_DOWN: case CAVE_WAND_DOWN_NAV:
		vectorIn = downVec;
		break;
	}

	float tempMatrix[16];

	switch( vecname ){
	case CAVE_HEAD_FRONT: case CAVE_HEAD_BACK: case CAVE_HEAD_UP: case CAVE_HEAD_DOWN: case CAVE_HEAD_LEFT: case CAVE_HEAD_RIGHT:
		//mult by head matrix
		MultVectorByMatrix( headMatrix, vectorIn, vec );
		break;
	case CAVE_WAND_FRONT: case CAVE_WAND_BACK: case CAVE_WAND_UP: case CAVE_WAND_DOWN: case CAVE_WAND_LEFT: case CAVE_WAND_RIGHT:
		//mult by wand matrix
		MultVectorByMatrix( wandMatrix, vectorIn, vec );
		break;
	case CAVE_HEAD_FRONT_NAV: case CAVE_HEAD_BACK_NAV: case CAVE_HEAD_UP_NAV: case CAVE_HEAD_DOWN_NAV: case CAVE_HEAD_LEFT_NAV: case CAVE_HEAD_RIGHT_NAV:
		//mult by head matrix and by nav matrix
		MultVectorByMatrix( headMatrix, vectorIn, vectorOut );
		//MultVectorByMatrix( NavMatrix, vectorOut, vec );
		
		MatrixInvert( NavMatrix, tempMatrix );
		//tempMatrix[3] = tempMatrix[7] = tempMatrix[11] = 0.0;
		tempMatrix[12] = tempMatrix[13] = tempMatrix[14] = 0.0;
		MultVectorByMatrix( tempMatrix, vectorOut, vec );
		break;
	case CAVE_WAND_FRONT_NAV: case CAVE_WAND_BACK_NAV: case CAVE_WAND_UP_NAV: case CAVE_WAND_DOWN_NAV: case CAVE_WAND_LEFT_NAV: case CAVE_WAND_RIGHT_NAV:
		//mult by wand matrix and by nav matrix 
		MultVectorByMatrix( wandMatrix, vectorIn, vectorOut );
		//MultVectorByMatrix( NavMatrix, vectorOut, vec );
		MatrixInvert( NavMatrix, tempMatrix );
		tempMatrix[12] = tempMatrix[13] = tempMatrix[14] = 0.0;
		//tempMatrix[3] = tempMatrix[7] = tempMatrix[11] = 0.0;
		MultVectorByMatrix( tempMatrix, vectorOut, vec );

		break;
	}

}

void CAVEGetProjection(CAVE_WALL_ID wall,CAVEID eye,float *frustum,float viewmat[4][4]){

	//just set up some slightly bogus default values!

	viewmat[0][0] = viewmat[0][1] = viewmat[0][2] = viewmat[0][3] = 0.0;
	viewmat[1][0] = viewmat[1][1] = viewmat[1][2] = viewmat[1][3] = 0.0;
	viewmat[2][0] = viewmat[2][1] = viewmat[2][2] = viewmat[2][3] = 0.0;
	viewmat[3][0] = viewmat[3][1] = viewmat[3][2] = viewmat[3][3] = 0.0;

	viewmat[0][0] = viewmat[1][1] = viewmat[2][2] = viewmat[3][3] = 1.0;

	frustum[0] = -1.0;
	frustum[1] =  1.0;
	frustum[2] =  1.0;
	frustum[3] = -1.0;
	frustum[4] = CAVENear;
	frustum[5] = CAVEFar;

}

int CAVEButtonChange(int num){

  if( num < 1 || num > CAVE_MAX_BUTTONS ){
    printf( "CAVE Button %d Out of Range! This function is 1-based\n", num);
    return 0;
  }
  
  int result = CAVEButtonChanges[num-1];
  CAVEButtonChanges[num-1] = 0;
    
  return result;
		
}

void CAVEGetSensorVector(CAVE_SENSOR_ST *sensor,CAVEID vecname,float *vec){

	if( sensor == CAVEptr->sensor[0] ){
		switch(vecname){
		case CAVE_UP:
			CAVEGetVector( CAVE_HEAD_UP, vec );
			break;
		case CAVE_UP_NAV:
			CAVEGetVector( CAVE_HEAD_UP_NAV, vec );
			break;
		case CAVE_DOWN:
			CAVEGetVector( CAVE_HEAD_DOWN, vec );
			break;
		case CAVE_DOWN_NAV:
			CAVEGetVector( CAVE_HEAD_DOWN_NAV, vec );
			break;
		case CAVE_LEFT:
			CAVEGetVector( CAVE_HEAD_LEFT, vec );
			break;
		case CAVE_LEFT_NAV:
			CAVEGetVector( CAVE_HEAD_LEFT_NAV, vec );
			break;
		case CAVE_RIGHT:
			CAVEGetVector( CAVE_HEAD_RIGHT, vec );
			break;
		case CAVE_RIGHT_NAV:
			CAVEGetVector( CAVE_HEAD_RIGHT_NAV, vec );
			break;
		case CAVE_FRONT:
			CAVEGetVector( CAVE_HEAD_FRONT, vec );
			break;
		case CAVE_FRONT_NAV:
			CAVEGetVector( CAVE_HEAD_FRONT_NAV, vec );
			break;
		case CAVE_BACK:
			CAVEGetVector( CAVE_HEAD_BACK, vec );
			break;
		case CAVE_BACK_NAV:
			CAVEGetVector( CAVE_HEAD_BACK_NAV, vec );
			break;
		}
	}else if( sensor == CAVEptr->sensor[1] ){
		switch(vecname){
		case CAVE_UP:
			CAVEGetVector( CAVE_WAND_UP, vec );
			break;
		case CAVE_UP_NAV:
			CAVEGetVector( CAVE_WAND_UP_NAV, vec );
			break;
		case CAVE_DOWN:
			CAVEGetVector( CAVE_WAND_DOWN, vec );
			break;
		case CAVE_DOWN_NAV:
			CAVEGetVector( CAVE_WAND_DOWN_NAV, vec );
			break;
		case CAVE_LEFT:
			CAVEGetVector( CAVE_WAND_LEFT, vec );
			break;
		case CAVE_LEFT_NAV:
			CAVEGetVector( CAVE_WAND_LEFT_NAV, vec );
			break;
		case CAVE_RIGHT:
			CAVEGetVector( CAVE_WAND_RIGHT, vec );
			break;
		case CAVE_RIGHT_NAV:
			CAVEGetVector( CAVE_WAND_RIGHT_NAV, vec );
			break;
		case CAVE_FRONT:
			CAVEGetVector( CAVE_WAND_FRONT, vec );
			break;
		case CAVE_FRONT_NAV:
			CAVEGetVector( CAVE_WAND_FRONT_NAV, vec );
			break;
		case CAVE_BACK:
			CAVEGetVector( CAVE_WAND_BACK, vec );
			break;
		case CAVE_BACK_NAV:
			CAVEGetVector( CAVE_WAND_BACK_NAV, vec );
			break;
		}
	}else{
		vec[0] = vec[1] = vec[2] = 0.0;
	}

}

void CAVEGetSensorPosition(CAVE_SENSOR_ST *sensor,CAVEID frame,float *pos){

	if( sensor == CAVEptr->sensor[0] ){
		if( frame == CAVE_TRACKER_FRAME ){
			CAVEGetPosition( CAVE_HEAD, pos);
		}
		else{
			CAVEGetPosition( CAVE_HEAD_NAV, pos);
		}
	}
	else if( sensor == CAVEptr->sensor[1] ){
		if( frame == CAVE_TRACKER_FRAME ){
			CAVEGetPosition( CAVE_WAND, pos);
		}
		else{
			CAVEGetPosition( CAVE_WAND_NAV, pos);
		}
	}
	else{
		pos[0] = pos[1] = pos[2] = 0.0;
	}

}

void CAVEGetSensorOrientation(CAVE_SENSOR_ST *sensor,CAVEID frame,float *ori){

	if( sensor == CAVEptr->sensor[0] ){
		if( frame == CAVE_TRACKER_FRAME ){
			CAVEGetOrientation( CAVE_HEAD, ori);
		}
		else{
			CAVEGetOrientation( CAVE_HEAD_NAV, ori);
		}
	}
	else if( sensor == CAVEptr->sensor[1] ){
		if( frame == CAVE_TRACKER_FRAME ){
			CAVEGetOrientation( CAVE_WAND, ori);
		}
		else{
			CAVEGetOrientation( CAVE_WAND_NAV, ori);
		}
	}
	else{
		ori[0] = ori[1] = ori[2] = 0.0;
	}
	
}

unsigned int CAVEGetFrameNumber(void){

	return CAVEFrameNumber;

}

void CAVEWallTransform(void){
	
	printf( "CAVEWallTransform(void) not implemented!\n" );
	return;

}

void CAVEHeadTransform(void){

	glTranslatef( _headPos[0], _headPos[1], _headPos[2] );

	glRotatef( _headOri[1], 0, 1, 0 );
	glRotatef( _headOri[0], 1, 0, 0 );
	glRotatef( _headOri[2], 0, 0, 1 );	

}

void CAVEWandTransform(void){

	glTranslatef( _wandPos[0], _wandPos[1], _wandPos[2] );
	
	glRotatef( _wandOri[1], 0, 1, 0 );
	glRotatef( _wandOri[0], 1, 0, 0 );
	glRotatef( _wandOri[2], 0, 0, 1 );

}

void CAVESensorTransform(CAVE_SENSOR_ST *sensor){

	if( sensor == CAVEptr->sensor[0] ){

		CAVEHeadTransform();

	}else if( sensor == CAVEptr->sensor[0] ){

		CAVEWandTransform();

	}else{

		printf( "CAVESensorTransform: unrecognized sensor\n" );

	}

}

boolean	CAVEInStereo(void){ return false; }
