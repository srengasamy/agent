//
//  Counter.cpp
//  agent
//
//  Created by Suresh Rengasamy on 10/9/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#include "Counter.hpp"
#include <time.h>

Counter::Counter(string metricName, string hostName) {
    name = metricName;
    host = hostName;
}

void Counter::inc() {
    inc(1);
}

void Counter::inc(int value) {
    long now = time(NULL);
    int second = now % BUCKET;
    values[second] += value;
    times[second] = now;
}

void Counter::dec() {
    dec(1);
}

void Counter::dec(int value) {
    long now = time(NULL);
    int second = now % BUCKET;
    values[second] -= value;
    times[second] = now;
}

string Counter::getPoints(){
    stringstream stream;
    long limit = time(NULL)-1;
    for(int i=0;i<BUCKET;i++){
        if(times[i] <= 0){
            continue;
        }else if(times[i] <=limit){
            last += values[i];
            stream << name << " " << last <<" " << times[i] << " " << "host=" << host << "\n";
            times[i] = -1;
            values[i] = 0;
        }
    }
    return stream.str();
}
