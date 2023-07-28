#pragma once
#include "CLAID.hpp"
#include "BatteryState.hpp"

namespace claid
{
    class BatteryData
    {

        public:
            int16_t level;
            BatteryState state;
                
            Reflect(BatteryData,
                reflectMember(level);
                reflectMember(state);
            )
    };
}

