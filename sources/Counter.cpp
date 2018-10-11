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
}

void Counter::inc() {
    inc(1);
}

void Counter::inc(int value) {
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    values.push_back(make_pair(ms.count(), value));
}

void Counter::dec() {
    dec(1);
}

void Counter::dec(int value) {
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    values.push_back(make_pair(ms.count(), -value));
}

string Counter::getPoints(){
    stringstream stream;
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    long now = ms.count() - 5000;
    list<pair<long, int>>::iterator it =values.begin();
    while (it != values.end()) {
        pair<long, int> point  = (*it);
        if(point.first>now){
            break;
        }
        stream << "\u2206" << name << " " << point.second <<" " << point.first << " " << "host=" << host << "\n";
        values.erase(it++);
    }
    return stream.str();
}
