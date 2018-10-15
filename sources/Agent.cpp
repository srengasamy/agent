//
//  Agent.cpp
//  agent
//
//  Created by Suresh Rengasamy on 10/9/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#include "Agent.hpp"

unsigned int max_n_threads = 10;
static MetricRegistry *registry;
static WavefrontReporter *reporter;
static Scheduler *scheduler;
static JVM* jvm;
static Thread *threadMonitor;

void report(WavefrontReporter *reporter){
    reporter->report();    
}

void ThreadStart(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread) {
    threadMonitor->ThreadStart(jvmti, jni_env, thread);
}

void ThreadEnd(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread) {
    threadMonitor->ThreadEnd(jvmti, jni_env, thread);
}

void JNICALL MonitorWait(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread, jobject object, jlong timeout) {
}

void JNICALL MonitorWaited(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread, jobject object, jboolean timed_out) {
}

void JNICALL MonitorContendedEnter(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread, jobject object) {
    threadMonitor->MonitorContendedEnter(jvmti, jni_env, thread, object);
}

void JNICALL MonitorContendedEntered(jvmtiEnv *jvmti, JNIEnv *jni_env, jthread thread, jobject object) {
    threadMonitor->MonitorContendedEntered(jvmti, jni_env, thread, object);
}

void JNICALL VMStart(jvmtiEnv *jvmti, JNIEnv *env) {
    jvm->start(jvmti);
}

void JNICALL VMInit(jvmtiEnv *jvmti, JNIEnv *env, jthread thread) {
    jvm->init(jvmti);
}

void JNICALL VMDeath(jvmtiEnv *jvmti, JNIEnv *env) {
    jvm->dead(jvmti);
}

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *vm, char *options, void *reserved) {
    cout<< "Loading agent." << endl;
    registry = new MetricRegistry();
    reporter = new WavefrontReporter(registry);
    scheduler = new Scheduler(max_n_threads);
    scheduler->every(15s, report, reporter);
    
    jvmtiError error;
    jvmtiEnv *jvmti;
    jvmtiCapabilities capabilities;
    jvmtiEventCallbacks callbacks;
    
    static JVM localJVM;
    jvm = &localJVM;
    
    jint res = vm->GetEnv((void **) &jvmti, JVMTI_VERSION_1);
    
    if (res != JNI_OK) {
        cout << "ERROR: Unable to access JVMTI" << endl;
    }
    jvm->jvmti = jvmti;
    threadMonitor = new Thread(jvm, registry);
    
    (void) memset(&capabilities, 0, sizeof(capabilities));
    (void) memset(&callbacks, 0, sizeof(callbacks));
    
    capabilities.can_generate_monitor_events = 1;
    capabilities.can_get_source_file_name = 1;
    capabilities.can_get_line_numbers = 1;
    capabilities.can_get_monitor_info = 1;
    capabilities.can_tag_objects = 1;
    
    error = jvmti->AddCapabilities(&capabilities);
    checkError(error, "ERROR: Unable to get necessary JVMTI capabilities.");
    
    error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_THREAD_START, (jthread) NULL);
    checkError(error, "ERROR: Unable to set thread start event!");
    error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_THREAD_END, (jthread) NULL);
    checkError(error, "ERROR: Unable to set thread end event!");
    error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_MONITOR_WAIT, (jthread) NULL);
    checkError(error, "ERROR: Unable to set monitor wait event!");
    error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_MONITOR_WAITED, (jthread) NULL);
    checkError(error, "ERROR: Unable to set monitor waited event!");
    error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_MONITOR_CONTENDED_ENTER, (jthread) NULL);
    checkError(error, "ERROR: Unable to set monitor enter event!");
    error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_MONITOR_CONTENDED_ENTERED, (jthread) NULL);
    checkError(error, "ERROR: Unable to set monitor resumed event!");
    
    callbacks.ThreadStart = &ThreadStart;
    callbacks.ThreadEnd = &ThreadEnd;
    callbacks.MonitorWait = &MonitorWait;
    callbacks.MonitorWaited = &MonitorWaited;
    callbacks.MonitorContendedEnter = &MonitorContendedEnter;
    callbacks.MonitorContendedEntered = &MonitorContendedEntered;
    callbacks.VMStart = &VMStart;
    callbacks.VMInit = &VMInit;
    callbacks.VMDeath = &VMDeath;
    
    error = jvmti->SetEventCallbacks(&callbacks, (jint) sizeof(callbacks));
    checkError(error, "ERROR: Unable to set callbacks");
    
    error = jvmti->CreateRawMonitor("agent data", &(jvm->lock));
    checkError(error, "ERROR: Cannot create agent monitor");
    return JNI_OK;
}
