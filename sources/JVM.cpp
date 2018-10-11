//
//  JVM.cpp
//  agent
//
//  Created by Suresh Rengasamy on 10/10/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#include "JVM.hpp"

void JVM::acquireLock(jvmtiEnv *jvmti) {
    jvmtiError error = jvmti->RawMonitorEnter(lock);
    checkError(error, "ERROR: Cannot enter with raw monitor");
}

void JVM::releaseLock(jvmtiEnv *jvmti) {
    jvmtiError error = jvmti->RawMonitorExit(lock);
    checkError(error, "ERROR: Cannot exit with raw monitor");
}

void JVM::init(jvmtiEnv *jvmti) {
    acquireLock(jvmti);
    {
        vmInitialized = JNI_TRUE;
    }
    releaseLock(jvmti);
}

void JVM::start(jvmtiEnv *jvmti) {
    acquireLock(jvmti);
    {
        vmStarted = JNI_TRUE;
    }
    releaseLock(jvmti);
}

void JVM::dead(jvmtiEnv *jvmti) {
    acquireLock(jvmti);
    {
        vmDead = JNI_TRUE;
    }
    releaseLock(jvmti);
}
