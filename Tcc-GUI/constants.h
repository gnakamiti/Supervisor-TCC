#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//#include <vld.h>

/*
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG*/


#define LOCAL_HOST "localhost"
#define PORT_HOST 8814

#define CLOSE_SUMO 0x7F
#define SUMO_STEP 0x02

#define SUMO_TRAFFIC_LIGHTS 0xa2
#define SUMO_GET_TRAFFIC_LIGHTS 0x00
#define SUMO_GET_COMPLETE_TRAFFIC_LIGHTS_DEFINITION 0x2b
#define SUMO_GET_CONTROLLED_LANES  0x26
#define SUMO_GET_CONTROLLED_LINKS 0x27
#define SUMO_SET_TRAFFIC_LIGHTS_VALUE 0xc2
#define SUMO_SET_TRAFFIC_LIGHT_PROGRAM 0x23
#define SUMO_TURN_OFF_CONTROLLER "off"
#define SUMO_TYPE_STRING 0x0C

#endif