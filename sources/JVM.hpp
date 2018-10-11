//
//  JVM.hpp
//  agent
//
//  Created by Suresh Rengasamy on 10/10/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#ifndef JVM_hpp
#define JVM_hpp

#include <stdio.h>
#include <jvmti.h>
#include "AgentUtil.hpp"

class JVM{
public:
    jvmtiEnv *jvmti;
    jboolean vmStarted;
    jboolean vmInitialized;
    jboolean vmDead;
    jrawMonitorID lock;
    
    void acquireLock(jvmtiEnv *jvmti);
    
    void releaseLock(jvmtiEnv *jvmti);
    
    void init(jvmtiEnv *jvmti);
    
    void start(jvmtiEnv *jvmti);
    
    void dead(jvmtiEnv *jvmti);
};
#endif /* JVM_hpp */
