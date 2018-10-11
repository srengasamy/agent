//
//  AgentUtil.cpp
//  agent
//
//  Created by Suresh Rengasamy on 10/10/18.
//  Copyright © 2018 Suresh Rengasamy. All rights reserved.
//

#include "AgentUtil.hpp"

void checkError(jvmtiError error, const char *message) {
    if (error != JVMTI_ERROR_NONE) {
        cout << message << "\n" << endl;
    }
}
