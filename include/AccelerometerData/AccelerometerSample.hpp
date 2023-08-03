#pragma once
#include "CLAID.hpp"

namespace claid
{
    class AccelerometerSample
    {

        public:
            AccelerometerSample()
            {

            }

            AccelerometerSample(double x, double y, double z) : x(x), y(y), z(z)
            {

            }

            void setData(double x, double y, double z)
            {
                this->x = x;
                this->y = y;
                this->z = z;
            }

            double x;
            double y;
            double z;
        
            Reflect(AccelerometerSample,
                reflectMember(x);
                reflectMember(y);
                reflectMember(z);
                reflectFunction(setData);
            )
    };
}


