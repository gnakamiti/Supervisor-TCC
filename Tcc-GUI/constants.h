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
#define PORT_HOST 8813

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
#define SUMO_LANE_VARIABLE 0xa3
#define SUMO_GET_QUEUE_SIZE 0x14
#define SUMO_INDUCTION_LOOP 0xa0
#define SUMO_GET_CAR_FLOW 0x10
#define SUMO_PHASE_DURATION 0x24
#define SUMO_INT_TYPE 0x09
#define SUMO_CURRENT_PROGRAM 0x29

#define FUZZY_INPUTL_VAR_CURRENT_QUEUE "CurrentQueue"
#define FUZZY_INPUTL_VAR_CAR_STREAM "CarStream"
#define FUZZY_INPUTL_VAR_QUEUE_AD_DEGREE "AdquationDegree"

#define FUZZY_INPUT_NOTHING "NOTHING"
#define FUZZY_INPUT_SMALL "SMALL"
#define FUZZY_INPUT_REGULAR "REGULAR"
#define FUZZY_INPUT_BIG "BIG"
#define FUZZY_INPUT_ENORMOUS "ENORMOUS"

#define FUZZY_INPUT_SIZE 5
#define FUZZY_OUTPUT_SIZE 25
#define FUZZY_STR_SIZE 1024
#define FUZZY_SIMILAR_CONTROLLER_TRESHOLD 60.0
#define FUZZY_SITUATION_NOT_GOOD_TRESHOLD 30.0
#define FUZZY_TIMER_INTERVAL 1000
#define FUZZY_USE_CAR_STREAM 1
#define FUZZY_DONT_USE_CAR_STREAM 2

#define FUZZY_OUTPUT_VALUE_SHOW_SCREEN_NOTHING "Excellent"
#define FUZZY_OUTPUT_VALUE_SHOW_SCREEN_SMALL "Good"
#define FUZZY_OUTPUT_VALUE_SHOW_SCREEN_REGULAR "Normal"
#define FUZZY_OUTPUT_VALUE_SHOW_SCREEN_BIG "Bad"
#define FUZZY_OUTPUT_VALUE_SHOW_SCREEN_ENOURMOUS "Critical"

#define LOG_FILE_NAME "SUPERVISOR_LOG.txt"

#define GUI_TIMER_UPDATE_UI 2000

#define GUI_MAP_FILE_LOCATION "qrc:/MainWindow/maps.html"
#define CONTROLLER_CFG_LOCATION ":/MainWindow/controllersPos.cfg"

#define CONTROLLER_LOGIC_BASE_DIR "logic-base"
#define MAX_LOGICS_PER_CONTROLLER 15
#define LOGICS_DATA_BASE_MAX_QUEUE_SIZE 30
#define LOGICS_DATA_BASE_MAC_CAR_STREAM 800
#define LOGICS_DATA_BASE_MIN_NUM 5

#define LOGIC_MAX_TIME 120
#define LOGIC_MED_TIME 60
#define LOGIC_SMALL_TIME 30

#endif