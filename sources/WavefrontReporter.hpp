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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

class WavefrontReporter{
private:
    MetricRegistry *registry;
    int sock;
public:
    WavefrontReporter(MetricRegistry *metricRegistry);
    void report();
    bool createSocket();
    bool sendData(string data);
    bool closeSocket();
};
#endif /* WavefrontReporter_hpp */
