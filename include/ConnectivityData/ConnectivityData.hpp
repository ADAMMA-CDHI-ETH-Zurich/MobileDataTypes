#pragma once
#include "CLAID.hpp"
#include "ConnectivityNetworkType.hpp"
class ConnectivityData
{

    public:
        bool connected;

        ConnectivityNetworkType networkType;

            
        Reflect(ConnectivityData,
            reflectMember(connected);
            reflectMember(networkType);
        )
};
