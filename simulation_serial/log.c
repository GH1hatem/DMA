#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include <stdbool.h>
// bool is_valid_nmea_sentence(const char *nmea_sentence) {
//     if (nmea_sentence[0] != '$') {
//         return false; // NMEA sentences start with '$'
//     }

//     const char checksum_str = strchr(nmea_sentence, '');
//     if (!checksum_str) {
//         return false; // No checksum delimiter found
//     }

//     int checksum = 0;
//     for (const char *p = nmea_sentence + 1; p < checksum_str; ++p) {
//         checksum ^= *p;
//     }

//     int provided_checksum;
//     sscanf(checksum_str , "%X", &provided_checksum);

//     return checksum == provided_checksum;
// }
int main()
{
    char nmea_sentence[] = "$GPRMC,210230,A,3855.4487,N,09446.0071,W,0.0,076.2,130495,003.8,E*69\n\r";
    char* token = strtok(nmea_sentence, ",");
    char* arr[14];
    int i = 0;
    while (token != NULL) {
        arr[i++] = token;
        token = strtok(NULL, ",");
    }

    int number;
    sscanf(arr[11], "%*[^0123456789]%d", &number) ; 
    printf("%d" , number) ;
    return 0;
}
