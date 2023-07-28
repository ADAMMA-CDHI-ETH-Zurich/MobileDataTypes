#pragma once
#include "CLAID.hpp"

namespace claid
{
    class AccelerometerSample
    {

        public:
            double x;
            double y;
            double z;
        
            Reflect(AccelerometerSample,
                reflectMember(x);
                reflectMember(y);
                reflectMember(z);
                )
    };
}


