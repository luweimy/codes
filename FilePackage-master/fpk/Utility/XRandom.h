//
//  XRandom.h
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_RANDOM__
#define __LM_UTILITY_RANDOM__
#include <random>

namespace LM
{
    class Random
    {
    public:
        /** [Gen]: [int_min, int_max]
            [Genf]: [0.f, 1.f) */
        static int   Gen()                                          {
            static std::random_device rand_device;
            static std::mt19937 mt(rand_device());
            return mt();
        }
        static float Genf()                                         {
            static std::random_device rand_device;
            static std::mt19937 mt(rand_device());
            std::uniform_real_distribution<float> dis(0);
            return dis(mt);
        }
        
        /** [Gen]: [min, ~) */
        static int   Gen(int min)                                   {
            static std::random_device rand_device;
            static std::mt19937 mt(rand_device());
            std::uniform_int_distribution<int> dis(min);
            return dis(mt);
        }
        
        /** range: [min, max] */
        static int   Gen(int min, int max)                          {
            static std::random_device rand_device;
            static std::mt19937 mt(rand_device());
            std::uniform_int_distribution<int> dis(min, max);
            return dis(mt);
        }
        static float Genf(float min, float max)                     {
            static std::random_device rand_device;
            static std::mt19937 mt(rand_device());
            std::uniform_real_distribution<float> dis(min, max);
            return dis(mt);
        }
    };

}

#endif /* __LM_UTILITY_RANDOM__ */
