#pragma once
#include "CLAID.hpp"

class LocationData
{
    public:
        std::string provider;
        int16_t floor;                  // Floor of eventual building
        int64_t timestamp;
        double hAccuracy;
        double vAccuracy;
        double speed;
        double altitude;
        double latitude;
        double longitude;
        double elapsedRealtimeSeconds;  // Elapsed time since system boot
        double bearing;                 // Horizontal direction of travel of device, unrelated to the device orientation.
                                        // Range is (0-360 degree). On iOS is called Course
    
        Reflect(LocationData,
            reflectMember(vAccuracy);
            reflectMember(hAccuracy);
            reflectMember(bearing);
            reflectMember(speed);
            reflectMember(timestamp);
            reflectMember(altitude);
            reflectMember(latitude);
            reflectMember(longitude);
            reflectMember(elapsedRealtimeSeconds);
            reflectMember(provider);
            reflectMember(floor);
            )
};

