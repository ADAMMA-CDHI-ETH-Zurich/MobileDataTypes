/***************************************************************************
* Copyright (C) 2023 ETH Zurich
* Core AI & Digital Biomarker, Acoustic and Inflammatory Biomarkers (ADAMMA)
* Centre for Digital Health Interventions (c4dhi.org)
* 
* Authors: Patrick Langer, Francesco Feher
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*         http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/

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

