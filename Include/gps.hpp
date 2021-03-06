//Parent Class for GPS

/*
Copied from aero-cpp-lib/include/sensors.hpp and aero-cpp-lib/include/data.hpp
*/

#pragma once

#if defined(ARDUINO) || defined(CORE_TEENSY)
    #include "Arduino.h"
#else
    #include <cstddef>
    #include <cstdint>
#endif

//#include "Data.hpp"           //No longer include this?

/*!
 *  \addtogroup aero
 *  @{
 */

//! Aero library code
namespace aero
{

/*!
 *  \addtogroup sensor          //Change sensor to GPS?
 *  @{
 */

//! Sensor interfaces
namespace sensor                //Change sensor to GPS?
{

    
/**
 * @brief Raw GPS data
 */
struct __attribute__((__packed__)) GPS_t                //Should the stuff from Data.hpp be added or put somewhere else
{
    int32_t lat;
    int32_t lon;
    uint16_t speed;
    uint8_t satellites;
    uint16_t altitude;
    uint32_t time;  // 4 BYTES. XX HR MIN SEC
    uint32_t date;  // 4 BYTES. XX YR MNTH DAY
};

/**
 * @brief Enum class for data signatures of each struct that can be sent
 */
//enum class Signature{ Pitot, IMU, GPS, Enviro, Batt, Config, Status, Actuators, AData, Cmds, Drop };     
    
/**
 * @brief Abstract GPS definition
 */
class GPS
{
public:
    /** @brief Defines configuration data for the GPS */
    struct Config_t
    {
        uint32_t baud_rate;
        uint16_t poll_time_ms;
        // Can add things like offsets here
        // Make sure to include defaults here
    };

    /**
     * @brief Initializes the GPS
     * 
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    virtual bool init( ) = 0;

    /**
     * @brief Initializes the GPS with user configuration
     * 
     * @param config user selected GPS configuration
     * @return true if initialization was successful
     * @return false if initialization was unsuccessful
     */
    bool init( GPS::Config_t config )
    {
        m_config = config;
        init();
    }

    /**
     * @brief Update the GPS data
     * 
     * @return true if update was successful
     * @return false if update was unsuccessful
     */
    virtual bool update( ) = 0;

    /**
     * @brief Get GPS data
     * 
     * @return const def::GPS_t& reference to GPS's data struct
     */
    const def::GPS_t& data(void) { return m_data; }

    /**
     * @brief Destructor
     */
    virtual ~GPS(){}

protected:
    // Hidden constructor that only children can redefine
    GPS(){}

    // Member variables
    def::GPS_t m_data;      // For gps data
    GPS::Config_t m_config; // For gps configuration
};

} //End of Namespace sensor

} //End of Namespace Aero
