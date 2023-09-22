#ifndef __CAVE_H__
#define __CAVE_H__


// UPDATED: 2016-08-25  (Y. Hu: Microsoft Visual Studio 2015; System configuration - Windows 7 + 16:9 screen ratio)
// UPDATED: 2018-08-02  (Y. Hu: Microsoft Visual Studio 2017; System configuration - Windows 7 + 16:9 screen ratio) 
// UPDATED: 2021-07-19  (Y. Hu: Microsoft Visual Studio 2019; System configuration - Windows 10 + 16:9 screen ratio) 

// ##############################################################
// ##
// ##  Note: This CAVELib simulator is nor noncommercial,
// ##        educational use only. Any other use could
// ##        get us both in some serious trouble.
// ##
// ##        I've only written this in order to help out
// ##		 developers who'd like to test code when away from
// ##        thier legally licensed copies, or for students
// ##        who are just learning CAVELib
// ##
// ##        Also note that I've implemented no network
// ##        functionality and don't plan to anytime soon.
// ##		 This is no substitue for the real CAVELib!
// ##
// ##        Comments in quotes are from the original header.
// ##
// ##############################################################


//#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>


#ifndef NULL
	#define NULL 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __linux__
#include <stdint.h>
#endif

#ifndef WIN32
typedef int32_t boolean;
#else
typedef int key_t;
typedef unsigned int u_int32_t;
typedef u_int32_t uint32_t;
typedef signed int int32_t;
typedef long pid_t;
#endif // WIN32


#define KNAVE_LIB //gives us something to test for later!

// "Wall IDs - for CAVEWall, WallGeom, ProjectionData, etc
//	(used as array indices, so should be defined as 1-n)"
typedef enum {
		CAVE_BOGUS_WALL=0,
		CAVE_FRONT_WALL=1,
		CAVE_FLOOR_WALL=2,
		CAVE_RIGHT_WALL=3,
		CAVE_LEFT_WALL=4,
		CAVE_CEILING_WALL=5,
		CAVE_BACK_WALL=6,
		CAVE_SCREEN0_WALL=7,
		CAVE_SCREEN1_WALL=8,
		CAVE_SCREEN2_WALL=9,
		CAVE_SCREEN3_WALL=10,
		CAVE_SCREEN4_WALL=11,
		CAVE_SCREEN5_WALL=12,
		CAVE_SCREEN6_WALL=13,
		CAVE_SCREEN7_WALL=14,
		CAVE_SIMULATOR_WALL=15,
		CAVE_SIMULATOR1_WALL=16,
		CAVE_SIMULATOR2_WALL=17,
		CAVE_SCREEN8_WALL=18,
		CAVE_SCREEN9_WALL=19,
		CAVE_SCREEN10_WALL=20,
		CAVE_SCREEN11_WALL=21,
		CAVE_SCREEN12_WALL=22,
		CAVE_SCREEN13_WALL=23,
		CAVE_SCREEN14_WALL=24,
		CAVE_SCREEN15_WALL=25,
		CAVE_SCREEN16_WALL=26,
		CAVE_SCREEN17_WALL=27,
		CAVE_SCREEN18_WALL=28,
		CAVE_SCREEN19_WALL=29,
		CAVE_SCREEN20_WALL=30,
		CAVE_SCREEN21_WALL=31,
		CAVE_SCREEN22_WALL=32,
		CAVE_SCREEN23_WALL=33,
		CAVE_SCREEN24_WALL=34,
		CAVE_SCREEN25_WALL=35,
		CAVE_SCREEN26_WALL=36,
		CAVE_SCREEN27_WALL=37,
		CAVE_SCREEN28_WALL=38,
		CAVE_SCREEN29_WALL=39,
		CAVE_SCREEN30_WALL=40,
		CAVE_SCREEN31_WALL=41,
		CAVE_NUM_WALL_IDS=42
	} CAVE_WALL_ID;
#define CAVE_MAX_WALL_ID	(CAVE_NUM_WALL_IDS-1)

// "Maximum # of walls that can be used simultaneously"
#define CAVE_MAX_WALLS	CAVE_MAX_WALL_ID

#define CAVE_MAX_BUTTONS	32

extern int CAVEButtons[CAVE_MAX_BUTTONS];

#define CAVEBUTTON1 CAVEButtons[0]
#define CAVEBUTTON2 CAVEButtons[1]
#define CAVEBUTTON3 CAVEButtons[2]
#define CAVEBUTTON4 CAVEButtons[3]

#define CAVE_MAX_VALUATORS	32

extern float *_CAVE_JOYSTICK_X;
extern float *_CAVE_JOYSTICK_Y;

#define CAVE_JOYSTICK_X (*_CAVE_JOYSTICK_X)
#define CAVE_JOYSTICK_Y (*_CAVE_JOYSTICK_Y)

#define CAVE_MAX_SENSORS	32

//TBD:
#define CAVESENSOR(i)		((CAVE_SENSOR_ST *)(CAVEptr->sensor[i]))
//#define CAVENETSENSOR(user,i)	((CAVE_SENSOR_ST *)(&user->sensor[i]))

typedef enum {
		CAVE_NULL=0,
		CAVE_HEAD,
		CAVE_WAND,
		CAVE_LEFT_EYE,
		CAVE_RIGHT_EYE,
		CAVE_FRONT,
		CAVE_BACK,
		CAVE_LEFT,
		CAVE_RIGHT,
		CAVE_UP,
		CAVE_DOWN,
		CAVE_FRONT_NAV,
		CAVE_BACK_NAV,
		CAVE_LEFT_NAV,
		CAVE_RIGHT_NAV,
		CAVE_UP_NAV,
		CAVE_DOWN_NAV,
		CAVE_HEAD_FRONT,
		CAVE_HEAD_BACK,
		CAVE_HEAD_LEFT,
		CAVE_HEAD_RIGHT,
		CAVE_HEAD_UP,
		CAVE_HEAD_DOWN,
		CAVE_WAND_FRONT,
		CAVE_WAND_BACK,
		CAVE_WAND_LEFT,
		CAVE_WAND_RIGHT,
		CAVE_WAND_UP,
		CAVE_WAND_DOWN,
		CAVE_HEAD_NAV,
		CAVE_WAND_NAV,
		CAVE_LEFT_EYE_NAV,
		CAVE_RIGHT_EYE_NAV,
		CAVE_HEAD_FRONT_NAV,
		CAVE_HEAD_BACK_NAV,
		CAVE_HEAD_LEFT_NAV,
		CAVE_HEAD_RIGHT_NAV,
		CAVE_HEAD_UP_NAV,
		CAVE_HEAD_DOWN_NAV,
		CAVE_WAND_FRONT_NAV,
		CAVE_WAND_BACK_NAV,
		CAVE_WAND_LEFT_NAV,
		CAVE_WAND_RIGHT_NAV,
		CAVE_WAND_UP_NAV,
		CAVE_WAND_DOWN_NAV,
// "CAVESetOption() arguments"
		CAVE_PROJ_USEWINDOW,
		CAVE_TRACKER_SIGNALRESET,
		CAVE_DIST_NETWORKSLAVE,
		CAVE_GL_SAMPLES,
		CAVE_GL_STENCILSIZE,
		CAVE_GL_ACCUMSIZE,
		CAVE_SCRAMNET_ARENASIZE,
		CAVE_SHMEM_SIZE,
		CAVE_SHMEM_ADDRESS,
		CAVE_NET_BUFFERSIZE,
		CAVE_NET_NUMBUFFERS,
		CAVE_NET_UPDATELOCALDATA,
// "Values for CAVEConfig->DisplayMode"
		CAVE_MONO,
		CAVE_STEREO,
// "Values for CAVEConfig->ControllerType"
		CAVE_MOUSE_CONTROLLER,
		CAVE_PC_CONTROLLER,
		CAVE_SIMULATOR_CONTROLLER,
		CAVE_LOGITECH_CONTROLLER,
		CAVE_CUSTOM_CONTROLLER,
		CAVE_DAEMON_CONTROLLER,
		CAVE_SCRAMNET_CONTROLLER,
// "Values for CAVEConfig->TrackerType"
		CAVE_POLHEMUS_TRACKER_OBSOLETE,
		CAVE_BIRDS_TRACKER,
		CAVE_LOGITECH_TRACKER,
		CAVE_MOUSE_TRACKER,
		CAVE_SIMULATOR_TRACKER,
		CAVE_SPACEBALL_TRACKER,
		CAVE_BOOM_TRACKER,
		CAVE_DAEMON_TRACKER,
		CAVE_SCRAMNET_TRACKER,
		CAVE_SPACEPAD_TRACKER,
// "Values for CAVEConfig->BirdsHemisphere"
		CAVE_FRONT_HEMI,
		CAVE_LEFT_HEMI,
		CAVE_RIGHT_HEMI,
		CAVE_AFT_HEMI,
		CAVE_UPPER_HEMI,
		CAVE_LOWER_HEMI,
// "Flock-of-birds sync type, for CAVEConfig->SyncBirds"
		CAVE_BIRDS_SYNC1,
		CAVE_BIRDS_SYNC2,
// "Frames of reference, for CAVE_SENSOR_ST.frame"
		CAVE_TRACKER_FRAME,
		CAVE_NAV_FRAME,
// "Values for CAVEConfig->Units"
		CAVE_FEET,
		CAVE_METERS,
		CAVE_INCHES,
		CAVE_CENTIMETERS,
// "Additional eye value for CAVEConfig->WallEyes"
		CAVE_BOTH_EYES,
// "Callback types, for CAVEAddCallback"
		CAVE_DISPLAY_CALLBACK,
		CAVE_INITGRAPHICS_CALLBACK,
		CAVE_PERFRAME_CALLBACK,
		CAVE_NETADDUSER_CALLBACK,
		CAVE_NETDELETEUSER_CALLBACK,
		CAVE_NETAPPDATA_CALLBACK,
// "Distributed CAVE method, for CAVEConfig->Distribution"
		CAVE_DIST_SCRAMNET,
		CAVE_DIST_TCP,
// "Networking types, for CAVEConfig->Network"
		CAVE_NET_MCAST,
		CAVE_NET_TCP,
		CAVE_NET_UDP,
// "Process types; returned by CAVEProcessType()"
		CAVE_APP_PROCESS,
		CAVE_DISPLAY_PROCESS,
		CAVE_TRACKER_PROCESS,
		CAVE_NETWORK_PROCESS,
		CAVE_DISTRIB_PROCESS,
// "Projection types (for screen# walls)"
		CAVE_WALL_PROJECTION,
		CAVE_HMD_PROJECTION,
// "Further 2.6 additions"
		CAVE_PROJ_USEMODELVIEW,
		CAVE_SIM_DRAWWAND,
		CAVE_SIM_DRAWOUTLINE,
		CAVE_SIM_DRAWUSER,
		CAVE_SIM_DRAWTIMING,
		CAVE_SIM_VIEWMODE,
		CAVE_PROJ_INCLUDENAVIGATION,
        // "Further 2.7 additions"
		CAVE_DIST_UDP,
        // "3.0 CAVELib"
		CAVE_SIM_DRAWSTATS
		} CAVEID;

// "For old code using obsolete names"
#define	CAVE_NO_CONTROLLER	CAVE_NULL
#define	CAVE_NO_TRACKING	CAVE_NULL
#define	CAVE_DIST_NONE		CAVE_NULL

//enum CAVEID { CAVE_NULL = -1, CAVE_HEAD, CAVE_WAND, CAVE_LEFT_EYE, CAVE_RIGHT_EYE, CAVE_HEAD_NAV, CAVE_WAND_NAV, CAVE_LEFT_EYE_NAV, CAVE_RIGHT_EYE_NAV };
//enum CAVE_WALL { CAVE_FRONT_WALL, CAVE_LEFT_WALL, CAVE_RIGHT_WALL, CAVE_FLOOR_WALL, CAVE_BACK_WALL, CAVE_CEILING_WALL, CAVE_SCREEN0_WALL, CAVE_SCREEN1_WALL, CAVE_SCREEN2_WALL, CAVE_SCREEN3_WALL, CAVE_SCREEN4_WALL, CAVE_SCREEN5_WALL, CAVE_SCREEN6_WALL, CAVE_SCREEN7_WALL, CAVE_SIMULATOR_WALL, CAVE_SIMULATOR1_WALL, CAVE_SIMULATOR2_WALL };

// "Device ID's for Custom controller buttons & valuators"
// These have been modified to work with glut
// TBD: Finish the list, ouch!
typedef enum {
	CAVE_NULLDEVICE=0,
	CAVE_AKEY = 'a',
	CAVE_BKEY = 'b',
	CAVE_CKEY = 'c',
	CAVE_DKEY = 'd',
	CAVE_EKEY = 'e',
	CAVE_FKEY = 'f',
	CAVE_GKEY = 'g',
	CAVE_HKEY = 'h',
	CAVE_IKEY = 'i',
	CAVE_JKEY = 'j',
	CAVE_KKEY = 'k',
	CAVE_LKEY = 'l',
	CAVE_MKEY = 'm',
	CAVE_NKEY = 'n',
	CAVE_OKEY = 'o',
	CAVE_PKEY = 'p',
	CAVE_QKEY = 'q',
	CAVE_RKEY = 'r',
	CAVE_SKEY = 's',
	CAVE_TKEY = 't',
	CAVE_UKEY = 'u',
	CAVE_VKEY = 'v',
	CAVE_WKEY = 'w',
	CAVE_XKEY = 'x',
	CAVE_YKEY = 'y',
	CAVE_ZKEY = 'z',
	CAVE_ESCKEY = 27,
	CAVE_ZEROKEY = '0',
	CAVE_ONEKEY = '1',
	CAVE_TWOKEY = '2',
	CAVE_THREEKEY = '3',
	CAVE_FOURKEY = '4',
	CAVE_FIVEKEY = '5',
	CAVE_SIXKEY = '6',
	CAVE_SEVENKEY = '7',
	CAVE_EIGHTKEY = '8',
	CAVE_NINEKEY = '9',
	CAVE_BREAKKEY,
	CAVE_CTRLKEY,
	CAVE_LEFTCTRLKEY,
	CAVE_CAPSLOCKKEY,
	CAVE_RIGHTSHIFTKEY,
	CAVE_LEFTSHIFTKEY,
	CAVE_NOSCRLKEY,
	CAVE_TABKEY,
	CAVE_RETKEY,
	CAVE_SPACEKEY = 32,
	CAVE_LINEFEEDKEY,
	CAVE_BACKSPACEKEY,
	CAVE_DELKEY,
	CAVE_SEMICOLONKEY,
	CAVE_PERIODKEY,
	CAVE_COMMAKEY,
	CAVE_QUOTEKEY,
	CAVE_ACCENTGRAVEKEY,
	CAVE_MINUSKEY,
	CAVE_VIRGULEKEY,
	CAVE_BACKSLASHKEY,
	CAVE_EQUALKEY,
	CAVE_LEFTBRACKETKEY,
	CAVE_RIGHTBRACKETKEY,
	CAVE_LEFTARROWKEY,
	CAVE_DOWNARROWKEY,
	CAVE_RIGHTARROWKEY,
	CAVE_UPARROWKEY,
	CAVE_PAD0,
	CAVE_PAD1,
	CAVE_PAD2,
	CAVE_PAD3,
	CAVE_PAD4,
	CAVE_PAD5,
	CAVE_PAD6,
	CAVE_PAD7,
	CAVE_PAD8,
	CAVE_PAD9,
	CAVE_PADPF1,
	CAVE_PADPF2,
	CAVE_PADPF3,
	CAVE_PADPF4,
	CAVE_PADPERIOD,
	CAVE_PADMINUS,
	CAVE_PADCOMMA,
	CAVE_PADENTER,
	CAVE_LEFTALTKEY,
	CAVE_RIGHTALTKEY,
	CAVE_RIGHTCTRLKEY,
	CAVE_F1KEY,
	CAVE_F2KEY,
	CAVE_F3KEY,
	CAVE_F4KEY,
	CAVE_F5KEY,
	CAVE_F6KEY,
	CAVE_F7KEY,
	CAVE_F8KEY,
	CAVE_F9KEY,
	CAVE_F10KEY,
	CAVE_F11KEY,
	CAVE_F12KEY,
	CAVE_PRINTSCREENKEY,
	CAVE_SCROLLLOCKKEY,
	CAVE_PAUSEKEY,
	CAVE_INSERTKEY,
	CAVE_HOMEKEY,
	CAVE_PAGEUPKEY,
	CAVE_ENDKEY,
	CAVE_PAGEDOWNKEY,
	CAVE_NUMLOCKKEY,
	CAVE_PADVIRGULEKEY,
	CAVE_PADASTERKEY,
	CAVE_PADPLUSKEY,

	CAVE_LEFTMOUSE,
	CAVE_MIDDLEMOUSE,
	CAVE_RIGHTMOUSE,
	CAVE_MOUSEX,
	CAVE_MOUSEY,
	CAVE_MOUSEWINX,
	CAVE_MOUSEWINY,

	CAVE_DIAL0,
	CAVE_DIAL1,
	CAVE_DIAL2,
	CAVE_DIAL3,
	CAVE_DIAL4,
	CAVE_DIAL5,
	CAVE_DIAL6,
	CAVE_DIAL7,
	CAVE_DIAL8,
	CAVE_BUT110,
	CAVE_BUT111,
	CAVE_BUT112,
	CAVE_BUT113,
	CAVE_BUT114,
	CAVE_BUT115,
	CAVE_BUT116,
	CAVE_BUT117,
	CAVE_BUT118,
	CAVE_BUT119,
	CAVE_BUT120,
	CAVE_BUT121,
	CAVE_BUT122,
	CAVE_BUT123,
	CAVE_BUT124,
	CAVE_BUT125,
	CAVE_BUT126,
	CAVE_BUT127,
	CAVE_BUT128,
	CAVE_BUT129,
	CAVE_BUT130,
	CAVE_BUT131,
	CAVE_BUT132,
	CAVE_BUT133,
	CAVE_BUT134,
	CAVE_BUT135,
	CAVE_BUT136,
	CAVE_BUT137,
	CAVE_BUT138,
	CAVE_BUT139,
	CAVE_BUT140,
	CAVE_BUT141,

	CAVE_SBPICK,
	CAVE_SBBUT1,
	CAVE_SBBUT2,
	CAVE_SBBUT3,
	CAVE_SBBUT4,
	CAVE_SBBUT5,
	CAVE_SBBUT6,
	CAVE_SBBUT7,
	CAVE_SBBUT8,
	CAVE_SBTX,
	CAVE_SBTY,
	CAVE_SBTZ,
	CAVE_SBRX,
	CAVE_SBRY,
	CAVE_SBRZ,
	CAVE_SBPERIOD,

	CAVE_NUM_DEVICES
	} CAVEDevice;


#define CAVE_REDMASK_BIT	1
#define CAVE_GREENMASK_BIT	2
#define CAVE_BLUEMASK_BIT	4

#ifndef boolean
//#define	boolean unsigned char
typedef unsigned char boolean;
#endif

/* CAVE display window description (from WallDisplay configuration) */
typedef struct
	{
	int		xoff,yoff;
	int		xdim,ydim;
	boolean		window;		/* TRUE == "normal" window - framed, sizeable */
	char		*display_env;	/* definition of DISPLAY variable */
	} CAVE_WINDOW_ST;


/* Offsets for tracker devices */
typedef struct
	{
	float dx,dy,dz;
	} CAVE_OFFSET_ST;

typedef struct
	{
	float axis_x,axis_y,axis_z;
	float theta;
	} CAVE_ROTATION_ST;

typedef struct
	{
	float elem[3][3];
	} CAVE_ROTATIONMATRIX_ST;

typedef struct
	{
	int x0,x1,y0,y1;
	} CAVE_VIEWPORT_ST;


/* Screen geometry; corners are in tracker space for a WALL, or eye space for an HMD */
typedef struct
	{
	CAVEID type;		/* CAVE_WALL_PROJECTION or CAVE_HMD_PROJECTION */
	float lowerleft[3];	/* Position of lower left corner */
	float upperleft[3];	/* Position of upper left corner */
	float lowerright[3];	/* Position of lower right corner */
	} CAVE_PROJINFO_ST;

/* Configuration - contains data from config files */
/* All data is the same across all process/threads */
/* data is READ-ONLY */
typedef struct
	{
/* Display stuff */
	int		ActiveWalls;
	CAVE_WALL_ID	DisplayWall[CAVE_MAX_WALLS];
	CAVE_WINDOW_ST	WallGeom[CAVE_NUM_WALL_IDS];
	CAVE_PROJINFO_ST	ProjectionData[CAVE_NUM_WALL_IDS][2];
	CAVEID		WallEyes[CAVE_NUM_WALL_IDS];
	CAVE_VIEWPORT_ST	Viewport[CAVE_NUM_WALL_IDS][2];
	char *		ViewportMask[CAVE_NUM_WALL_IDS][2];
	int		Colormask[CAVE_NUM_WALL_IDS][2];
	float		CAVEWidth,CAVEHeight;
	float		OrigX,OrigY,OrigZ;
	CAVEID		DisplayMode;
	boolean		StereoBuffer;
	CAVE_OFFSET_ST		CAVETranslation;
	CAVE_ROTATIONMATRIX_ST	CAVERotation;
	float		CAVEScale;
	boolean		HideCursor;
	char *		InitCommand[CAVE_NUM_WALL_IDS];
	char *		ExitCommand[CAVE_NUM_WALL_IDS];
/* Tracker stuff */
	boolean		UseTracker;
	boolean		SerialTracking;
	boolean		SensorActive[CAVE_MAX_SENSORS];
	CAVEID		TrackerType;  /* CAVE_BIRDS / CAVE_LOGITECH / etc. */
	char *		TrackerSerialPort[CAVE_MAX_SENSORS];
	int		TrackerBaudRate;
	CAVEID		SyncBirds;
	boolean		FilterBirds;
	int		FilterBirdsParameter;
	CAVEID		BirdsHemisphere;
	int		BirdsSensorsCount;
	int		BirdsSensors[CAVE_MAX_SENSORS];
	int		BirdsTransmitter;
	boolean		UseCalibration;
	char *		CalibrationFile;
	float		DefaultTrackerPosition[3];
	float		DefaultTrackerOrientation[3];
	CAVE_OFFSET_ST		TransmitterOffset;
	CAVE_ROTATIONMATRIX_ST	TransmitterRotationMatrix;
	CAVE_OFFSET_ST		WandSensorOffset;
	CAVE_ROTATIONMATRIX_ST	HeadSensorRotationMatrix;
	CAVE_OFFSET_ST		HeadSensorOffset;
	CAVE_ROTATIONMATRIX_ST	WandSensorRotationMatrix;
	float		InterocularDistance;
	key_t		TrackdKey;
/* Controller stuff */
	CAVEID		ControllerType;
	int		ControllerButtonsCount;
	CAVEDevice	ControllerButtons[CAVE_MAX_BUTTONS];
	int		ControllerValuatorsCount;
	CAVEDevice	ControllerValuators[CAVE_MAX_VALUATORS];
	int		ControllerValuatorsMin[CAVE_MAX_VALUATORS];
	int		ControllerValuatorsMax[CAVE_MAX_VALUATORS];
	key_t		ControllerdKey;
/* Simulator stuff */
	boolean		Simulator;
	CAVEDevice	SimulatorControls[23];
	float		SimViewDistance,SimViewHeight,SimViewWidth;
	CAVEDevice	SimulatorJoystickControl;
	int		SimulatorNumWands;
/* Network stuff */
	CAVEID		Network;
	int		NetworkPort;
	int		NetworkAppPort;
	char *		NetworkAddr;
	float		NetworkUpdateInterval;
	int		NetworkTTL;
	int		NetworkMaxUsers;
	boolean		NetworkCPUHog;
	char *		NetworkTCPServer;
	char *		NetworkUDPHost;
/* Distributed CAVE stuff */
	CAVEID		Distribution;	/* Method - none/Scramnet/TCP */
	CAVEID		AppDistribution;
	int		DistribNodes;
	int		DistribID;
	char *		DistribTCPMaster;
	int		DistribTCPPort;
	boolean		GangSwap;
	boolean		DistribCPUHog;
/* Scramnet stuff */
	boolean		Scramnet;
	char *		ScramnetDevice[2];
	int		ScramnetMemSize;
	int		ScramnetMemBase;
	int		ScramnetRegSize;
	int		ScramnetRegBase;
	short		ScramnetPrefix;
	key_t		SimScramKey;
/* Miscellaneous stuff */
	boolean		CPULock;
	CAVEID		Units;
	int		ShmemKey_obsolete;
	int		SimulatorCommandPort;
/* 2.7 additions */
	char *		DistribUDPMaster;
	int		DistribUDPPort;
	}  CAVE_CONFIG_ST;


/* Display process synchronization data */
typedef	struct
	{
	boolean 	Initted;
	boolean		Quit;
	} CAVE_SYNC_ST;

/* Note: CAVE_TIMESTAMP_ST, CAVE_SENSOR_ST, and CAVE_CONTROLLER_ST explicitly
   use int32's because these structs are used in the tracker daemon's shared
   memory.  We can't have them be different sizes when in 32 vs 64 bit mode. */
/* Sensor timestamp (can't use struct timeval because its size is different in 64-bit mode!) */
typedef struct
	{
	uint32_t	sec;
	uint32_t	usec;
	} CAVE_TIMESTAMP_ST;

/* Position & orientation data for trackers */
typedef struct
	{
	float 		x, y, z;
	float 		azim, elev, roll;
	CAVE_TIMESTAMP_ST	timestamp;
	int32_t		calibrated;
	CAVEID		frame;		/* CAVE_TRACKER_FRAME or CAVE_NAV_FRAME */
	} CAVE_SENSOR_ST;


/* Collection of buttons & valuators associated with wand */
typedef struct
	{
	uint32_t	num_buttons,num_valuators;
	int32_t		button[CAVE_MAX_BUTTONS];
	float		valuator[CAVE_MAX_VALUATORS];
	} CAVE_CONTROLLER_ST;


/* CAVENETID & CAVE_USER_ST use explicit int32's because we can't guarantee
   that the default integer size on different networked systems will be
   the same. */

typedef uint32_t CAVENETID[2];

/* A networked user - tracker & controller data, & time of last info received.
	Tracker data is in navigated coordinates. */
typedef struct
	{
	CAVENETID		id;
	float			timestamp;
	uint32_t		num_sensors;
	CAVE_SENSOR_ST		sensor[CAVE_MAX_SENSORS];
	CAVE_CONTROLLER_ST	controller;
	void 			*app_data;
	} CAVE_USER_ST;


/* CAVE lock pointer */
typedef struct CAVE_LOCK_ST * CAVELOCK;

typedef void (*CAVECALLBACK)();

typedef void (*CAVECalibrationFunc)(CAVE_SENSOR_ST *,int);


typedef struct
	{
	CAVE_CONFIG_ST		*config;
	volatile CAVE_SYNC_ST	*procsync;
	unsigned int		num_sensors;
	volatile CAVE_SENSOR_ST **sensor;
	volatile CAVE_CONTROLLER_ST	*controller;
	volatile float		*time;
	volatile float		*framesPerSecond;
	volatile CAVE_USER_ST	**user;
	volatile unsigned int	*numUsers;
 
	struct _CAVEipcdata		      *ipc; /* allocated before CAVEInit, read-only */
	volatile struct _CAVEdispdata	*disp;
	struct _CAVEprojdata		  *projection; /* not used */	
	struct _CAVEsimdata		      *sim; /* allocated before CAVEInit, read-only */
	struct _CAVEcallbackdata	  *callbacks; /* not used */
	volatile struct _CAVEtrackerData	*trackerData;
	struct _CAVEdistribdata		  *distrib; /* allocated before CAVEInit, read-only? */
	struct _CAVEscramdata		  *scram; /* allocated before CAVEInit, read-only? */
	struct _CAVEshmemdata		  *shmem; /* allocated before CAVEInit, read-only */
	volatile struct _CAVEnetdata  *net; 
#ifndef CAVE_THREAD
	CAVE_WALL_ID		           wall;
	CAVEID			               eye;
	struct _CAVEpipedata		*pipe;
	struct _CAVEchannel		*channel;
	struct _CAVEprocdata		*proc;
#else
	CAVE_WALL_ID		          wall[CAVE_MAX_THREADS];
	CAVEID			              eye[CAVE_MAX_THREADS];
	struct _CAVEpipedata		  **pipe;
	struct _CAVEchannel		      **channel;
	struct _CAVEprocdata		  **proc; /* For CAVE_THREAD - This is a ptr to an array of
										 ptrs to proc structures, one for each thread. 
										 Access using CAVETID e.g. CAVEptr->proc[CAVETID]*/
#endif /* CAVE_THREAD */
	} CAVE_ST;



//My Own Stuff

extern float CAVENear;
extern float CAVEFar;
extern int CAVEEye;
extern int CAVEWall;
extern float * CAVETime;

//extern "C"{

//currently appdefaults is ignored
void CAVEConfigure( int* argc, char** argv, char** appdefaults = NULL );

void CAVEInit( void );

typedef void( *CAVECALLBACK )(void);

void CAVEInitApplication( CAVECALLBACK function, int num_args, void * arg1 = NULL, void * arg2 = NULL, void * arg3 = NULL, void * arg4 = NULL, void * arg5 = NULL );

void CAVEFrameFunction( CAVECALLBACK function, int num_args, void * arg1 = NULL, void * arg2 = NULL, void * arg3 = NULL, void * arg4 = NULL, void * arg5 = NULL );

void CAVEDisplay( CAVECALLBACK function, int num_args, void * arg1 = NULL, void * arg2 = NULL, void * arg3 = NULL, void * arg4 = NULL, void * arg5 = NULL );

void CAVEStopApplication( CAVECALLBACK function, int num_args, void * arg1 = NULL, void * arg2 = NULL, void * arg3 = NULL, void * arg4 = NULL, void * arg5 = NULL );

void CAVEExit();

int CAVEgetbutton( int buttonID );

//TBD: complete this, but seeing as this is only supposed
//     to be a simulator, there should only be 1 process/thread anyway
void CAVEDisplayBarrier();

//TBD: there "should" allocate from "shared memory"
//     but since this is just a simulator, malloc and free will do
void * CAVEMalloc( int size );

void CAVEFree( void * data );

void CAVEGetOrientation(CAVEID oname,float *angle);

void CAVEGetPosition(CAVEID oname,float *pos);

float CAVEGetTime();

boolean CAVEMasterDisplay();
boolean CAVEMasterWall();

void CAVESetOption(CAVEID option,int value);

int	CAVENumPipes(void);
int	CAVEPipeNumber(void);

//}


////extern void	CAVEInit(void);
//extern void	CAVEHalt(void);
////extern void	CAVEExit(void);
////extern void	CAVEDisplay(CAVECALLBACK, int, ...);
////extern void	CAVEInitApplication(CAVECALLBACK, int, ...);
////extern void	CAVEFrameFunction(CAVECALLBACK, int, ...);
////extern void	CAVEStopApplication(CAVECALLBACK, int, ...);
//extern void	CAVEAddCallback(CAVEID cbtype, CAVECALLBACK function, void *app_data);
//extern void	*CAVEUserSharedMemory(int);
////extern void	*CAVEMalloc(size_t);
////extern void	CAVEFree(void *p);
//extern void	CAVEGetEyePosition(CAVEID eye,float *x,float *y,float *z);
////extern void	CAVEConfigure(int *argc,char **argv,char **appdefaults);
////extern boolean	CAVEMasterDisplay(void);
////extern boolean	CAVEMasterWall(void);
////extern void	CAVEDisplayBarrier(void);
//extern void	CAVEDisplaySync(void);
////extern void	CAVESetOption(CAVEID option,int value);
//extern CAVEID	CAVEProcessType(void);
////extern int	CAVENumPipes(void);
////extern int	CAVEPipeNumber(void);
//extern CAVEID   CAVEUnits(void);
//extern	char *	CAVEWallName(CAVE_WALL_ID);
//extern CAVE_WALL_ID	CAVEWallID(char *wallname);
//extern void     CAVEGetWallCorners(CAVE_WALL_ID id, float* ll, float* ul, float* lr);

extern int	CAVEButtonChange(int num);
extern void	CAVEGetSensorVector(CAVE_SENSOR_ST *sensor,CAVEID vecname,float *vec);
extern void	CAVEGetVector(CAVEID vecname,float *vec);
extern void	CAVEGetSensorPosition(CAVE_SENSOR_ST *sensor,CAVEID frame,float *pos);
////extern void	CAVEGetPosition(CAVEID posname,float *pos);
extern void	CAVEGetSensorOrientation(CAVE_SENSOR_ST *sensor,CAVEID frame,float *ori);
////extern void	CAVEGetOrientation(CAVEID oname,float *ori);
////extern double	CAVEGetTime(void);
extern unsigned int	CAVEGetFrameNumber(void);
extern void	CAVEWallTransform(void);
extern void	CAVEHeadTransform(void);
extern void	CAVEWandTransform(void);
extern void	CAVESensorTransform(CAVE_SENSOR_ST *sensor);
extern boolean	CAVEInStereo(void);
//extern void	CAVEGetWindowGeometry(int *origX,int *origY,int *width,int *height);
//extern void	CAVEGetViewport(int *x,int *y,int *width,int *height);
//extern void	CAVEGetPipeChannels(CAVEID wall[CAVE_NUM_WALL_IDS]);
//extern void	CAVEGetActiveChannels(CAVEID wall[CAVE_NUM_WALL_IDS]);
//extern float	CAVEConvertToCAVEUnits(float val,CAVEID units);
//extern float	CAVEConvertFromCAVEUnits(float val,CAVEID units);
extern void	CAVEGetProjection(CAVE_WALL_ID wall,CAVEID eye,float *frustum,float viewmat[4][4]);
//extern void	CAVEGetProjectionForViewpoint(CAVE_WALL_ID wall, CAVEID eye, float *eyePos,
//						float *eyeRot, float *frustum, float viewmat[4][4]);

//extern CAVELOCK	CAVENewLock(void);
//extern void	CAVEFreeLock(CAVELOCK lock);
//extern void	CAVESetReadLock(CAVELOCK lock);
//extern void	CAVESetWriteLock(CAVELOCK lock);
//extern void	CAVEUnsetReadLock(CAVELOCK lock);
//extern void	CAVEUnsetWriteLock(CAVELOCK lock);
//extern void	*CAVEScramnetMalloc(size_t);
//extern void	CAVEScramnetFree(void *p);

extern void	CAVENavLoadIdentity(void);
extern void	CAVENavLoadMatrix(float matrix[4][4]);
extern void	CAVENavGetMatrix(float matrix[4][4]);
extern void	CAVENavMultMatrix(float matrix[4][4]);
extern void	CAVENavTranslate(float x,float y,float z);
extern void	CAVENavRot(float a,char axis);
extern void	CAVENavScale(float x,float y,float z);
extern void	CAVENavPreMultMatrix(float matrix[4][4]);
extern void	CAVENavWorldTranslate(float x,float y,float z);
extern void	CAVENavWorldRot(float a,char axis);
extern void	CAVENavWorldScale(float x,float y,float z);
extern void	CAVENavConvertWorldToCAVE(float *in,float *out);
extern void	CAVENavConvertCAVEToWorld(float *in,float *out);
extern void	CAVENavConvertVectorWorldToCAVE(float *in,float *out);
extern void	CAVENavConvertVectorCAVEToWorld(float *in,float *out);
extern void	CAVENavTransform(void);
extern void	CAVENavInverseTransform(void);
extern void	CAVENavLock(void);
extern void	CAVENavUnlock(void);

//extern void	CAVEResetTracker(void);

//extern CAVE_USER_ST * CAVENetFindUser(CAVENETID id);
//extern void CAVENetGetVector(volatile CAVE_USER_ST *user,CAVEID vecname,float *vec);
//extern void CAVENetGetPosition(volatile CAVE_USER_ST *user,CAVEID posname,float *pos);
//extern void CAVENetGetOrientation(volatile CAVE_USER_ST *user,CAVEID oname,float *ori);
//extern void CAVENetHeadTransform(volatile CAVE_USER_ST *user);
//extern void CAVENetWandTransform(volatile CAVE_USER_ST *user);
//extern void CAVENetSend(void *data,size_t size);
//extern int CAVENetReceive(void *buf,size_t size,CAVE_USER_ST **user);
////extern boolean CAVEgetbutton(CAVEDevice);
extern int CAVEgetvaluator(CAVEDevice);

//extern boolean CAVEDistribOpenConnection(int chanID);
//extern void CAVEDistribCloseConnection(int chanID);
//extern void CAVEDistribWrite(int chanID,void *buf,size_t size);
//extern size_t CAVEDistribRead(int chanID,void *buf,size_t size);
//extern void	CAVEDistribBarrier(int chanID);
//extern boolean	CAVEDistribMaster(void);
//extern unsigned int CAVEDistribNumNodes(void);
//extern volatile void * CAVEAllocDisplayData(size_t size);
//extern void CAVEPassDisplayData(volatile void *buf,size_t size);
//extern void CAVEPassAllDisplayData(void);
//extern volatile void * CAVEGetDisplayData(volatile void *buf,size_t *size);
//extern boolean CAVEDisplayDataChanged(volatile void *buf);
//extern volatile void * CAVEAllocDisplayDataByID(int id,size_t size);
//extern void CAVEPassDisplayDataByID(int id,size_t size);
//extern volatile void * CAVEGetDisplayDataByID(int id,size_t *size);
//extern boolean CAVEDisplayDataChangedByID(int id);
//extern boolean CAVEDisplayDataIDExists(int id);
//extern int CAVEGetDisplayDataID(volatile void *buf);
//extern int CAVENewID(void);

//extern void  CAVESetCalibrationFunc(CAVECalibrationFunc callback);

//extern int CAVEUniqueIndex(void);

//extern  void CAVEUSleep(unsigned long microseconds);
//extern  void CAVESleep(float seconds);

#ifndef WIN32
//extern Display * CAVEXDisplay(void);
//extern Window CAVEXWindow(void);
//extern XVisualInfo *CAVEXVisualInfo(void);
//extern GLXContext CAVEGLXContext(void);
#else
//extern HDC CAVEXDisplay(void);
//extern HWND CAVEXWindow(void);
//extern PIXELFORMATDESCRIPTOR *CAVEXVisualInfo(void);
//extern HGLRC CAVEGLXContext(void);
#endif


/* CAVE library global data; */ 

/* data in shared memory is declared volatile, works the same across
   process/threads */
//extern	volatile float     	*CAVEFramesPerSecond;
//extern	volatile float		*CAVETime;
//extern	volatile CAVE_SYNC_ST  	*CAVESync;
//extern	volatile CAVE_SENSOR_ST	*CAVESensor1, *CAVESensor2;
//extern	volatile CAVE_CONTROLLER_ST	*CAVEController;
//extern	volatile CAVE_USER_ST		**CAVEUser;
//extern	volatile unsigned int		*CAVENumUsers;

/* Data that is READ-ONLY and the same for each process/threads */
extern	char 			            *CAVEVersion;
//extern	CAVE_CONFIG_ST              *CAVEConfig;


#ifndef CAVE_THREAD
/* Data that is READ-ONLY and may be different for each process/threads */
////extern	CAVE_WALL_ID    CAVEWall;
////extern	CAVEID			CAVEEye;
extern	CAVE_ST			*CAVEptr; /* see CAVE_ST above for difference in proc data member */

/* Data that is READ-WRITE and different for each process/threads */
////extern  float    		CAVENear, CAVEFar;

#else /* CAVE_THREAD - Thread version */

/* Thread local storage(TLS) versions of CAVE globals, they are
   arrays of data, one for each thread */
//extern	CAVE_WALL_ID    CAVEWallTLS[CAVE_MAX_THREADS];
//extern  CAVEID          CAVEEyeTLS[CAVE_MAX_THREADS];
//extern  float    		CAVENearTLS[CAVE_MAX_THREADS], CAVEFarTLS[CAVE_MAX_THREADS];

/* Macros for backwards compatibility to original process-based CAVELib */

#if (__sgi || __sun || __hpux || __linux__)
//#define CAVEWall        (CAVEWallTLS[CAVETID])
//#define CAVEEye         (CAVEEyeTLS[CAVETID])
//#define CAVENear        (CAVENearTLS[CAVETID])
//#define CAVEFar         (CAVEFarTLS[CAVETID])
#else
//#define CAVEWall        ((CAVE_WALL_ID)(CAVEWallTLS[CAVETID]))
//#define CAVEEye         ((CAVEID)(CAVEEyeTLS[CAVETID]))
//#define CAVENear        ((float)CAVENearTLS[CAVETID])
//#define CAVEFar         ((float)CAVEFarTLS[CAVETID])
#endif


/* see definition of CAVE_ST above for difference in proc data member */
extern	CAVE_ST			*CAVEptr; 
#endif /* CAVE_THREAD */

#ifdef __cplusplus
}
#endif


#endif
