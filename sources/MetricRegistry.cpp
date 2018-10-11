//
//  MetricRegistry.cpp
//  agent
//
//  Created by Suresh Rengasamy on 10/9/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#include "MetricRegistry.hpp"

MetricRegistry::MetricRegistry() {
    gethostname(hostname, 1024);
}

Counter* MetricRegistry::counter(string name) {
    Counter* counter = new Counter(name, hostname);
    counters.push_back(counter);
    return counter;
}

list<Counter*> MetricRegistry::getCounters(){
    return counters;
}
