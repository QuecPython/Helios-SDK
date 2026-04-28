/*
 * Copyright (c) Quectel Wireless Solution, Co., Ltd.All Rights Reserved.
 *  
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *  
 *     http://www.apache.org/licenses/LICENSE-2.0
 *  
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "helios_os.h"
#include <stdlib.h>

typedef struct {
    Helios_Mutex_t mutex;
    Helios_Thread_t bound_thread;
    uint32_t recurse_depth;
} helios_mutex_r_t;

Helios_ReMutex_t Helios_ReMutex_Create(void) {
    helios_mutex_r_t * helios_mutex_r = malloc(sizeof(helios_mutex_r_t));
    if(!helios_mutex_r) {
        goto error;
    }

    if(!(helios_mutex_r->mutex = Helios_Mutex_Create())) {
        goto error;
    }

    helios_mutex_r->bound_thread = 0;
    helios_mutex_r->recurse_depth = 0;

    return (Helios_ReMutex_t)helios_mutex_r;

error:
    if(helios_mutex_r->mutex) {
        Helios_Mutex_Delete(helios_mutex_r->mutex);
    }

    if(helios_mutex_r) {
        free(helios_mutex_r);
    }

    return 0;
}

static int _Helios_ReMutex_Lock(helios_mutex_r_t * helios_mutex_r, uint32_t wait) {
    int ret = Helios_Mutex_Lock(helios_mutex_r->mutex, wait);

    // If hold the lock
    if(ret == 0) {
        helios_mutex_r->bound_thread = Helios_Thread_GetID();
        helios_mutex_r->recurse_depth++;
    }

    return ret;
}

int Helios_ReMutex_Lock(Helios_ReMutex_t mutex_r, uint32_t wait) {
    helios_mutex_r_t * helios_mutex_r = (helios_mutex_r_t *)mutex_r;

    if(!helios_mutex_r) {
        return -1;
    }

    if(helios_mutex_r->recurse_depth == 0) {
        // Nobady hold the lock.
        return _Helios_ReMutex_Lock(helios_mutex_r, wait);
    } else {
        if(Helios_Thread_GetID() != helios_mutex_r->bound_thread) {
            // Lock is held by other thread.
            // Current thread won't acquire the lock, need to wait for it.
            return _Helios_ReMutex_Lock(helios_mutex_r, wait);
        } else {
            // Lock is held by current thread.
            helios_mutex_r->recurse_depth++;
            return 0;
        }
    }
}

void Helios_ReMutex_Unlock(Helios_ReMutex_t mutex_r) {
    helios_mutex_r_t * helios_mutex_r = (helios_mutex_r_t *)mutex_r;

    if(helios_mutex_r) {
        if(helios_mutex_r->recurse_depth && (Helios_Thread_GetID() == helios_mutex_r->bound_thread)) {
            // If the lock is held
            // And want to release the lock in the bound thread.
            helios_mutex_r->recurse_depth--;
            if(!helios_mutex_r->recurse_depth) {
                helios_mutex_r->bound_thread = 0;
                Helios_Mutex_Unlock(helios_mutex_r->mutex);
            }
        }
    }
}

void Helios_ReMutex_Delete(Helios_ReMutex_t mutex_r) {
    helios_mutex_r_t * helios_mutex_r = (helios_mutex_r_t *)mutex_r;

    if(helios_mutex_r) {
        Helios_Mutex_Delete(helios_mutex_r->mutex);
        free(helios_mutex_r);
    }
}
