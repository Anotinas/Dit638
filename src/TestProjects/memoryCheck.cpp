#include "memoryCheck.h"


//Used by getValue
int ParseLine(char* line){
	int i = strlen(line);
	const char* p = line;
	while(*p<'0' || *p > '9') p++;
	line[i-3] = '\0';
	return i;
}
//Used to get the amount of Virtual memory used by current process
int getVMemory(){
	FILE* file =fopen("/proc/self/status",  "r");
	int result = -1;
	char line[128];
	while(fgets(line, 128, file)!=NULL){
		if(strncmp(line, "VmSize:",7) == 0){
			result = ParseLine(line);
			break;
		}
	}
	fclose(file);
	return result;

}
//Used to get the amount of physical memory used by the process
int getPMemory(){
	FILE* file =fopen("/proc/self/status",  "r");
	int result = -1;
	char line[128];
	while(fgets(line, 128, file)!=NULL){
		if(strncmp(line, "VmRSS:",6) == 0){
			result = ParseLine(line);
			break;
		}
	}
	fclose(file);
	return result;
}

//The following functions and values are used to get the CPU currently used by the process.
static clock_t lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
//Run this once before calling any other CPU funcs.
void init(){
    FILE* file;
    struct tms timeSample;
    char line[128];

    lastCPU = times(&timeSample);
    lastSysCPU = timeSample.tms_stime;
    lastUserCPU = timeSample.tms_utime;

    file = fopen("/proc/cpuinfo", "r");
    numProcessors = 0;
    while(fgets(line, 128, file) != NULL){
        if (strncmp(line, "processor", 9) == 0) numProcessors++;
    }
    fclose(file);
}

double getCPUValue(){
    struct tms timeSample;
    clock_t now;
    double percent;

    now = times(&timeSample);
    if (now <= lastCPU || timeSample.tms_stime < lastSysCPU ||
        timeSample.tms_utime < lastUserCPU){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        percent = (timeSample.tms_stime - lastSysCPU) +
            (timeSample.tms_utime - lastUserCPU);
        percent /= (now - lastCPU);
        percent /= numProcessors;
        percent *= 100;
    }
    lastCPU = now;
    lastSysCPU = timeSample.tms_stime;
    lastUserCPU = timeSample.tms_utime;

    return percent;
}


