//From onboard-software-2018-19/src/Onboard Software V1.0/main/GPS.cpp



#include <Arduino.h>
#include "GPS/Include/GPS_2018-19/GPS_NEO6.h"           //Might need to change these back
#include "GPS/Include/GPS_2018-19/GPS_2018-19.h"

GPS::GPS() {}
GPS::~GPS() {}
//getZero and getXYZ can be used with any GPS unit (not specific to ETV4, or NEO)

void GPS::getZero(float lat, float lon, float alt){
  refLat = lat;
  refLon = lon;
  refAlt = alt;
}

void GPS::getXYZ(float latitude, float longitude, float alt, float baseLatitude, float baseLongitude){
  double lonToMetre, latToMetre; 
  
  //finds the diference in position from the reference (zero) in meters 
  double latRad = 0.0174533*latitude;
  double lonRad = 0.0174533*longitude;  

  //converts min/deg/sec to metres
  latToMetre = 111132.92 - 559.82*cos(2*latRad) + 1.175*cos(4*latRad) - 0.0023*cos(6*latRad);
  lonToMetre = 111412.84*cos(lonRad) - 93.5*cos(3*lonRad) + 0.118*cos(5*lonRad);

  //find change in position
  deltaX = lonToMetre*(longitude - refLon);
  deltaY = latToMetre*(latitude - refLat);
  Z = (refAlt-alt); 
}
