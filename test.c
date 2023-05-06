#include <stdio.h>
#include <time.h>

int main() {
    char time_str[50];
    time_t current_time;
    struct tm* local_time;

    // Get the current time
    current_time = time(NULL);

    // Convert to local time
    local_time = localtime(&current_time);

    // Format the time as a string
    strftime(time_str, sizeof(time_str), "%m-%d-%Y %H:%M:%S", local_time);

    // Print the formatted time string
    printf("Current time: %s\n", time_str);

    return 0;
}
