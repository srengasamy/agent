//
//  Counter.cpp
//  agent
//
//  Created by Suresh Rengasamy on 10/9/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#include "Counter.hpp"
#include <time.h>
#include <chrono>
using namespace std::chrono;

Counter::Counter(string metricName, string hostName) {
    name = metricName;
    host = hostName;
    for(int i=0;i<BUCKET;i++){
        times[i] = 0;
        values[i] = 0;
    }
}

void Counter::inc() {
    long now = time(NULL);
    int bucket = now % BUCKET;
    values[bucket] = ++value;
    times[bucket] = now;
}

void Counter::dec() {
    long now = time(NULL);
    int bucket = now % BUCKET;
    values[bucket] = --value;
    times[bucket] = now;
}

string Counter::getPoints(){
    stringstream stream;
    long now = time(NULL) - 1;
    for(int i=0;i<BUCKET;i++){
        if(times[i] == 0 || times[i]> now){
            continue;
        }
        stream << name << " " << values[i] <<" " << times[i] << " " << "host=\"" << host << "\"" << "\n";
        times[i] = 0;
        values[i] = 0;
    }        
    return stream.str();
}
