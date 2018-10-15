//
//  Thread.cpp
//  agent
//
//  Created by Suresh Rengasamy on 10/12/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#include "Thread.hpp"

Thread::Thread(JVM* j, MetricRegistry *r){
    jvm = j;
    registry = r;
    threadCounter = registry->counter("thread.all");
    blockedCounter = registry->counter("thread.blocked");
    deadlockedCounter = registry->counter("thread.deadlocked");
}

void Thread::ThreadStart(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread){
    threadCounter->inc();
}

void Thread::ThreadEnd(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread){
    threadCounter->dec();
}

void Thread::MonitorContendedEnter(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread, jobject object){
    blockedCounter->inc();
}

void Thread::MonitorContendedEntered(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread, jobject object){
    blockedCounter->dec();
    //jvmti->SetTag(thread, 0L); // To Find dead lock
}

void Thread::findDeadload(jvmtiEnv *jvmti, jthread thread, jobject object){
    //To Remove
    jvmti->SetTag(thread, (jlong)*(void **)object);
    jobject mon = object;
    while(true){
        void *owner_oop;
        jvmtiMonitorUsage monitor_usage;
        jvmti->GetObjectMonitorUsage(mon, &monitor_usage);
        jvmti->Deallocate((unsigned char *)monitor_usage.waiters);
        jvmti->Deallocate((unsigned char *)monitor_usage.notify_waiters);
        
        if(monitor_usage.owner == NULL){
            return;
        }
        owner_oop = *(void **)monitor_usage.owner;
        if(owner_oop == *(void **)thread){
            jvmtiThreadInfo thread_info;
            jvmti->GetThreadInfo(thread, &thread_info);
            cout <<"deadlock detected!: " << thread_info.name << "\n" << endl;
            jvmti->Deallocate((unsigned char *)thread_info.name);
            return;
        }
        jthread owner_thread = (jthread)&owner_oop;
        
        jint thread_state;
        jvmti->GetThreadState(owner_thread, &thread_state);
        if((thread_state & JVMTI_THREAD_STATE_BLOCKED_ON_MONITOR_ENTER) == 0){
            return;
        }
        
        void *contended_monitor_oop;
        jvmti->GetTag(owner_thread, (jlong *)&contended_monitor_oop);
        if(contended_monitor_oop == NULL){
            return;
        }
        mon = (jobject)&contended_monitor_oop;
    }
}
