//
//  WavefrontReporter.cpp
//  agent
//
//  Created by Suresh Rengasamy on 10/9/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#include "WavefrontReporter.hpp"

#define SOCKET_ERROR "FATAL: Unable to connect to proxy"

WavefrontReporter::WavefrontReporter(MetricRegistry *metricRegistry){
    registry = metricRegistry;
    sock = -1;
}

void WavefrontReporter::report(){
    if(!createSocket()){
        cout<<"FATAL: Unable to send metric" << endl;
        return;
    }
    list<Counter*> counters = registry->getCounters();
    list<Counter*>::iterator it =counters.begin();
    while (it != counters.end()) {
        string points  = (*it)->getPoints();
        if(!points.empty()){
            sendData(points);
        }
        it++;
    }
}

bool WavefrontReporter::createSocket(){
    if(sock != -1){
        return true;
    }
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if(sock == -1){
        cout << SOCKET_ERROR << endl;
        return false;
    }
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(2878);
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){
        cout << SOCKET_ERROR << endl;
        return false;
    }
    return true;
}

bool WavefrontReporter::sendData(string data){
    if(send(sock, data.c_str(), strlen(data.c_str()), 0) < 0){
        return false;
    }
    //cout << "Points sent." << endl;
    return true;
}

bool WavefrontReporter::closeSocket(){
    return false;
}
