//
//  Counter.hpp
//  agent
//
//  Created by Suresh Rengasamy on 10/9/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#ifndef Counter_hpp
#define Counter_hpp

#include <stdio.h>
#include <iosfwd>
#include <atomic>
#include <list>
#include <map>
#include <string>
#include <array>
#include <sstream>
#include <iostream>

#define BUCKET 60
using namespace std;

class Counter{
private:
    string name;
    string host;
    list<string> tags;
    atomic_int value;
    long times[BUCKET];
    int values[BUCKET];
    
public:
    Counter(string metricName, string hostName);
    
    void inc();
    
    void dec();
    
    string getPoints();
    
};
#endif /* Counter_hpp */
