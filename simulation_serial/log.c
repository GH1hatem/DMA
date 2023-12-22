#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include <stdbool.h>

int main()
{
    char nmea_sentence[] = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,545.4,$GPRMC,220516\n\r$GPRMC,123519,4807.038,N,01131.000,E,1,08,545.4,$GPRMC,220516";
    char* result[7];
    // can u redo the code to get the result in an array of strings
    // divide the string into tokens and store them based on $ 
    // then divide the tokens into tokens based on , and store them in an array of strings
    // then use the array of strings to get the values
    










    char* token = strtok(nmea_sentence, "$");
    while (token!=NULL){
         token = strtok(NULL, ",");
        if (token == "GPGGA"){
            char* arr[14];
            int i = 0;
            while (token != NULL) {
                arr[i++] = token;
                token = strtok(NULL, ",");
            }
            printf("hdhdh");
        }
        if (token == "$GPRMC"){
            printf("hey");
        }
    }
    // int number;
    // sscanf(arr[11], "%*[^0123456789]%d", &number) ; 
    // printf("%d" , number) ;
    return 0;
}
