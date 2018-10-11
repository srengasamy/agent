//
//  AgentUtil.hpp
//  agent
//
//  Created by Suresh Rengasamy on 10/10/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#ifndef AgentUtil_hpp
#define AgentUtil_hpp
#include <jvmti.h>
#include <iostream>
#include <stdio.h>

using namespace std;

void checkError(jvmtiError error, const char *message);
#endif /* AgentUtil_hpp */
