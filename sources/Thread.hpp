//
//  Thread.hpp
//  agent
//
//  Created by Suresh Rengasamy on 10/12/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#ifndef Thread_hpp
#define Thread_hpp

#include <stdio.h>
#include "JVM.hpp"
#include "MetricRegistry.hpp"
#include "Counter.hpp"

using namespace std;

class Thread{
private:
    JVM *jvm;
    MetricRegistry *registry;
    Counter* threadCounter;
    Counter* blockedCounter;
    Counter* deadlockedCounter;
public:
    Thread(JVM *j, MetricRegistry *r);
    void ThreadStart(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread);
    void ThreadEnd(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread);
    void MonitorContendedEnter(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread, jobject object);
    void MonitorContendedEntered(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread, jobject object);
    void findDeadload(jvmtiEnv *jvmti, jthread thread, jobject object);
};
#endif /* Thread_hpp */
