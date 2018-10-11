//
//  MetricRegistry.hpp
//  agent
//
//  Created by Suresh Rengasamy on 10/9/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#ifndef MetricRegistry_hpp
#define MetricRegistry_hpp

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <list>
#include "Counter.hpp"

using namespace std;

class MetricRegistry{
private:
    char hostname[100];
    list<Counter*> counters;
public:
    MetricRegistry();
    Counter* counter(string name);
    list<Counter*> getCounters();
};
#endif /* MetricRegistry_hpp */
