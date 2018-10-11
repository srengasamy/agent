//
//  WavefrontReporter.cpp
//  agent
//
//  Created by Suresh Rengasamy on 10/9/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#include "WavefrontReporter.hpp"

WavefrontReporter::WavefrontReporter(MetricRegistry *metricRegistry){
    registry = metricRegistry;
}

void WavefrontReporter::report(){
    list<Counter*> counters = registry->getCounters();
    list<Counter*>::iterator it =counters.begin();
    while (it != counters.end()) {
        string points  = (*it)->getPoints();
        if(!points.empty()){
            cout << points << endl;
        }
        it++;
    }
}
