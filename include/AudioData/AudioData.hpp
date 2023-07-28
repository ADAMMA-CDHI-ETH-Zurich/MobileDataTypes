#pragma once
#include "CLAID.hpp"

#include <stdint.h>
#include <vector>
#include <string.h>
namespace claid
{
    struct AudioData
    {
        std::vector<uint8_t> data;

        AudioData()
        {
        }

        AudioData(size_t size)
        {
            this->data.resize(size);
        }

        size_t size() const
        {
            return data.size();
        }

        template<typename T>
        const T* getData() const
        {
            return reinterpret_cast<const T*>(this->data.data());
        }

        Reflect(AudioData, 
            reflectMember(data);
        )
    };

}

