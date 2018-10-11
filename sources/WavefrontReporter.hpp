//
//  WavefrontReporter.hpp
//  agent
//
//  Created by Suresh Rengasamy on 10/9/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#ifndef WavefrontReporter_hpp
#define WavefrontReporter_hpp

#include <stdio.h>
#include "MetricRegistry.hpp"
#include <iterator>
#include <list>
#include <iostream>

class WavefrontReporter{
private:
    MetricRegistry *registry;
public:
    WavefrontReporter(MetricRegistry *metricRegistry);
    void report();
};
#endif /* WavefrontReporter_hpp */
