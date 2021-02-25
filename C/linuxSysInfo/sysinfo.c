#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define LB_SIZE 20
#define LONG "long" 
#define SHORT "short"
#define STANDARD "standard"

int main(int argc, char *argv[]){
   
   FILE *context = fopen("/proc/stat", "r");        //Context Switches file
   FILE *cpuinfo = fopen("/proc/cpuinfo", "r");    
   FILE *diskstat = fopen("/proc/diskstats", "r");
   FILE *processes = fopen("/proc/stat/", "r");
   FILE *stat = fopen("/proc/stat", "r");
   FILE *thisProcFile;
   FILE *uptime = fopen("/proc/uptime", "r");       //Uptime File
   FILE *version = fopen("/proc/version", "r");     //Version File
   FILE *memTotal = fopen("/proc/meminfo", "r");
   FILE *memFree = fopen("/proc/meminfo", "r");

  struct timeval currentTime;
  
   int boot_time, context_switch, days, filler, hours, idle_mode, //ints
       mem_Total, mem_Free, minutes, process, reads_completed, seconds, 
       system_mode, user_mode, writes_completed;
   int count = 0;
   int counter1 = 0;
   int counter2 = 0;
   int counter3 = 0;
   int counter4 = 0;
   int counter5 = 0;
   int duration = 0;
   int interval = 0;    
   int iter = 0;

   char c;    //chars
   char c1[1];
   char c2[1];
   char lineBuf[LB_SIZE];
   char line[1000];
   char *reportType = STANDARD;
   char repTypeName[16];
   
        while ((fgets(line, sizeof(line), cpuinfo))){  // Read /proc files
           count++;
           if (count == 5){
           printf("CPU %s", line);
           }
        }

        while ((c = fgetc(version)) != EOF){
           printf("%c", c);
        }

        while ((fgets(line, sizeof(line), uptime))){
           sscanf(line, "%d", &boot_time);
           seconds = boot_time % 60;
           minutes = boot_time / 60 % 60;
           hours = boot_time / 60 / 60 % 24;
           days = boot_time / 60 / 60 / 24;
           printf("Boot time: %02d:%02d:%02d:%02d\n", days, hours, minutes, seconds);
        }

    strcpy(repTypeName, "Standard");
    if (argc > 1){
       sscanf(argv[1], "%s", c1);
       if (c1[0] != '-' || c1[1] != 's' && c1[1] != 'l')
       {
           fprintf(stderr, "usage: observer [-s][-l int dur]\n");
           exit(1);
       }

       if (c1[1] == 's')
       {
           reportType = SHORT;
           strcpy(repTypeName, "Short");
        
           fgets(line, sizeof(line), stat); //check /proc/stat
           sscanf(line, "cpu %d %d %d %d", &user_mode, &filler, &system_mode, &idle_mode);
           printf("User mode :%d\n", user_mode);
           printf("System mode :%d\n", system_mode);
           printf("Idle mode :%d\n", idle_mode);

           while ((fgets(line, sizeof(line), diskstat))){
               counter1++;
               if (counter1 == 1){
                   sscanf(line, "%d %d %d %d %d %d %d %d", &filler, &filler, &filler, &reads_completed, &filler, &filler, &filler, &writes_completed);
                   printf("Reads Completed: %d\n", reads_completed);
                   printf("Writes Completed: %d\n", writes_completed);
                }
            }

        while ((fgets(line, sizeof(line), context))){
           counter2++;
           if (counter2 == 11){
               sscanf(line, "%d %d", &filler, &context_switch);
               printf("Context Switches: %d\n", context_switch);
            }
        }
    
        while ((fgets(line, sizeof(line), processes))){
           counter4++;
           if (counter4 == 13){
               sscanf(line, "%s %d", &filler, &process);
               printf("Processes: %d", process);
            }
        }

        if (memTotal == NULL){
           printf("File not open");
           exit(0);
        }
        else{
           fgets(line, sizeof(line), memTotal);
           sscanf(line, "%s%d", &filler, &mem_Total);
           printf("Memory configured: &d\n\n", mem_Total);
        }

        while ((fgets(line, sizeof(line), memFree))){
           counter5++;
           if(counter5 == 2){
               sscanf(line, "%s%d", &filler, &mem_Free);
               printf("Memory available: %d\n\n", mem_Free);
            }
        }
    }else if (c1[1] == 'l'){
            if (argv[2] == NULL || argv[3] == NULL){
               fprintf(stderr, "usage: observer [-s][-l int dur]\n");
               exit(1);
            }
            else{
               reportType = LONG;
               strcpy(repTypeName, "Long");
               interval = atoi(argv[2]);
               duration = atoi(argv[3]);
            }
        }
   }

    gettimeofday(&currentTime, NULL); //current Time

    printf("Status report type %s at %s", repTypeName, ctime(&(currentTime.tv_sec)));

    thisProcFile = fopen("/proc/sys/kernel/hostname", "r");   // Get current host filename and print
    fgets(lineBuf, LB_SIZE + 1, thisProcFile);
    printf("Machine hostname: %s", lineBuf);
    fclose(thisProcFile);

    while (iter < duration){
       sleep(interval);
       FILE *loadavg = fopen("/proc/loadavg", "r");
       fgets(line, sizeof(line), loadavg);
       printf("Interval: %d\nIteration: %d\nLoad Average: %s", interval, iter, line);
       iter += interval;
    }
    return (0);
}