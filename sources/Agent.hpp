//
//  Agent.hpp
//  agent
//
//  Created by Suresh Rengasamy on 10/9/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#ifndef Agent_hpp
#define Agent_hpp

#include <jvmti.h>
#include <stdio.h>
#include <iostream>
#include "WavefrontReporter.hpp"
#include "MetricRegistry.hpp"
#include "Counter.hpp"
#include "Scheduler.h"
#include "JVM.hpp"
#include "AgentUtil.hpp"

using namespace std;
using namespace Bosma;

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *vm, char *options, void *reserved);

#endif /* Agent_hpp */
