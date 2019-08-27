#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>

#include <sys/types.h>
#include <sys/sysinfo.h>

#include "sys/times.h"
#include "sys/vtimes.h"


    int getPMemory();
    int getVMemory();
    void init();
    double getCPUValue();