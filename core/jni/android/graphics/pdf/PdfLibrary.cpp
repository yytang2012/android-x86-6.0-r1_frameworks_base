/*
 * Copyright (C) 2015 Intel iCDG
 *
 * Move the reference count of fpdfview in PdfRenderer.cpp and PdfEditor.cpp
 * to PdfLibrary.cpp
 *
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "jni.h"
#include "JNIHelp.h"
#include "fpdfview.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
#include "fsdk_rendercontext.h"
#pragma GCC diagnostic pop

#include "core_jni_helpers.h"
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

namespace android {

static Mutex sLock;

static int sUnmatchedInitRequestCount = 0;

void initializeLibraryIfNeeded() {
    Mutex::Autolock _l(sLock);
    if (sUnmatchedInitRequestCount == 0) {
        FPDF_InitLibrary();
    }
    sUnmatchedInitRequestCount++;
}

void destroyLibraryIfNeeded() {
    Mutex::Autolock _l(sLock);
    sUnmatchedInitRequestCount--;
    if (sUnmatchedInitRequestCount == 0) {
       FPDF_DestroyLibrary();
    }
}

};
