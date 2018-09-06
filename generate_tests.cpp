// generate_tests.cpp
// Generate random dates for the serial calendar.
// D. L. Yonge-Mallo

#include<iostream>

#include"lunar/watdefs.h"
#include"lunar/date.h"
#include"sdncal.h"

using namespace std;

int main(int, char**)
{
    const long int day_zero = 2443309;
    const long int start_day = day_zero + 11000;
    const long int end_day = day_zero + 11000 + 365;
    const long int difference = end_day - start_day + 1;
    const int how_many = 44;

    srand(time(0));

    for(int count = 0 ; count < how_many ; count++ ) {

        long int jdn1 = (rand() % difference) + start_day;
        long int jdn2 = (rand() % difference) + start_day;
        long int serial_day1 = jdn1 - day_zero;
        long int serial_day2 = jdn2 - day_zero;

        // Find out the (Gregorian) day of week.
        int dow1, dow2;
        dow1 = DayOfWeek(jdn1);
        dow2 = DayOfWeek(jdn2);

        // Find the Gregorian calendar date.
        int g_year1, g_month1, g_day1;
        SdnToGregorian(jdn1, &g_year1, &g_month1, &g_day1);
        int g_year2, g_month2, g_day2;
        SdnToGregorian(jdn2, &g_year2, &g_month2, &g_day2);

        // Output the dates.
        char buffer1[100], day_buffer1[10], buffer2[100], day_buffer2[10];

        // Put Month+day into string buffers.
        strcpy(buffer1, MonthNameLong[g_month1]);
        strcat(buffer1, " ");
        sprintf(day_buffer1, "%d", g_day1);
        strcat(buffer1, day_buffer1);
        strcpy(buffer2, MonthNameLong[g_month2]);
        strcat(buffer2, " ");
        sprintf(day_buffer2, "%d", g_day2);
        strcat(buffer2, day_buffer2);

        // Line 1
        cout << buffer1;
        for( int i = 33 - strlen(buffer1) ; i > 0 ; i-- ) {
            cout << " ";
        }
        if( serial_day1 < 10000 ) cout << "0";
        cout << serial_day1 << "    ";
        if( serial_day2 < 10000 ) cout << "0";
        cout << serial_day2;
        for( int i = 33 - strlen(buffer2) ; i > 0 ; i-- ) {
            cout << " ";
        }
        cout << buffer2 << endl;

        // Line 2
        cout << "                (     day) ";
        for( int i = 10 - strlen(DayNameLong[dow1]) ; i > 0 ; i--) {
            cout << " ";
        }
        cout << " " << DayNameLong[dow1] << "    ";
        cout << "                (     day) ";
        for( int i = 10 - strlen(DayNameLong[dow2]) ; i > 0 ; i--) {
            cout << " ";
        }
        cout << " " << DayNameLong[dow2] << endl;
        cout << endl;

        /*cout << endl;
        cout << endl;
        cout << endl;
        cout << "                             + ______________";
        for( int i = 0 ; i < 25 ; i++ ) cout << " ";
        if( serial_day < 10000 ) cout << "0";
        cout << serial_day << endl;
        cout << "                                              (     day)";
        for( int i = strlen(DayNameLong[dow]) ; i < 19 ; i++ ) cout << " ";
        cout << DayNameLong[dow] << endl;
        cout << endl;*/

        /*cout << serial_day
             //<< " [0x" << hex << serial_day << dec << "]"
             << " - " << DayNameLong[dow] << ", " << MonthNameLong[g_month]
             << " " << g_day << ", " << g_year;
        cout << endl;*/


    }
}
