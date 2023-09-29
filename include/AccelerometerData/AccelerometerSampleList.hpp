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
#include "AccelerometerSample.hpp"

namespace claid
{
    class AccelerometerSampleList
    {

        public:
            
            
            std::vector<AccelerometerSample> samples;
            std::vector<int64_t> timestamps;

            void addSample(double x, double y, double z, int64_t timestamp)
            {
                this->samples.push_back(AccelerometerSample(x, y, z));
                this->timestamps.push_back(timestamp);
            }
            
            void insertSamples(std::vector<double> xs, std::vector<double> ys, std::vector<double> zs, std::vector<int64_t> timestamps)
            {
                if(xs.size() != ys.size() || ys.size() != zs.size() || xs.size() != timestamps.size())
                {
                    CLAID_THROW(claid::Exception, "Error, cannot set samples in AccelerometerSampleList: Expected xs, ys and zs and timestamps of same size,\n"
                    << "however they have sizes " << xs.size() << " " << ys.size() << " " << zs.size() << " and " << timestamps.size());
                }

                this->samples = std::vector<AccelerometerSample>(xs.size());

                for(size_t i = 0; i < xs.size(); i++)
                {
                    this->samples[i] = AccelerometerSample(xs[i], ys[i], zs[i]);
                }
                this->timestamps = timestamps;
            }

            void clear()
            {
                this->samples.clear();
                this->timestamps.clear();
            }
            
            Reflect(AccelerometerSampleList,
                reflectMember(timestamps); 
                reflectMember(samples);
                reflectFunction(addSample);
                reflectFunction(insertSamples);
                reflectFunction(clear);
                
                )
    };
}


