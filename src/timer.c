#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "timer.h"

struct timeval start_time, end_time;
struct rusage usage;

void start_timer() {
    gettimeofday(&start_time, NULL);
}

void stop_timer() {
    gettimeofday(&end_time, NULL);
}

void print_timer() {
    getrusage(RUSAGE_SELF, &usage);
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;

    printf("Tempo total: %.3f segundos\n", elapsed);
    printf("Tempo de CPU (usuario): %ld.%06ld segundos\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("Tempo de CPU (sistema): %ld.%06ld segundos\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
}