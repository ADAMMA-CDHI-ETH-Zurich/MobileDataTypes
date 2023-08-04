#pragma once
#include "CLAID.hpp"
#include "AccelerometerSample.hpp"

namespace claid
{
    class AccelerometerData
    {

        public:
            
            // How many seconds do the samples in this data represent?
            // E.g., if frequency = 20Hz and timeScale = 0.5s, samples.size() should be 10.
            float seconds;

            
            uint16_t frequency;
            std::vector<AccelerometerSample> samples;
        
            void set(float seconds, uint16_t frequency, std::vector<AccelerometerSample> samples)
            {
                this->seconds = seconds;
                this->frequency = frequency;
                this->samples = samples;

                if(seconds * frequency != samples.size())
                {
                    CLAID_THROW(claid::Exception, "Error in AccelerometerData. Mismatch between time, frequency and number of samples in provided data.\n"
                    << "Data represents a time of " << seconds << "s, sampled at frequency " << frequency << ",\n"
                    << "therefore " << seconds << " * " << frequency << " = " << seconds * frequency << " samples were expected, however " << samples.size() << " samples were provided.");
                }

            }
            // If timescale is 1s and frequency is 20hz,
            // this assures that only 20 sample points are available in samples.
            // Hence, we assume that the data points provided in samples were sampled at a higher frequency,
            // so we now just take every, we take every samples.size() / 20th element.
            
            // In other words, if more samples are provided than expected by seconds * frequency,
            // we take a subset of the samples, by taking every samples.size() / (seconds * frequency)th element.
            void setAndSubsample(float seconds, uint16_t frequency, std::vector<AccelerometerSample> samples)
            {
                int expectedSamples = 1.0 * seconds * frequency;

                this->seconds = seconds;
                this->frequency = frequency;

                if(samples.size() < expectedSamples)
                {
                    CLAID_THROW(claid::Exception, "Error, cannot setAndSubsample. A time of " << seconds << "s and a frequency of " << frequency
                    << " were provided. Thus, >= " << expectedSamples << " were expected to subsample from, but only " << samples.size() << " were provided");
                }

                if(expectedSamples == samples.size())
                {
                    this->samples = samples;
                    return;
                }

                float fraction = samples.size() * 1.0 / (expectedSamples * 1.0);

                this->samples.clear();
                for(int i = 0; i < expectedSamples; i++)
                {
                    this->samples.push_back(samples[i * fraction]);
                }


            }

            
            Reflect(AccelerometerData,
                reflectMember(seconds);
                reflectMember(frequency);
                reflectMember(samples);
                reflectFunction(set);
                reflectFunction(setAndSubsample);
                )
    };
}


