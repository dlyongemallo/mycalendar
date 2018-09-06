// mydate.cpp
// Output the current date in my serial calendar.
// D. L. Yonge-Mallo

#include<iomanip>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>

#include"lunar/watdefs.h"
#include"lunar/date.h"
#include"sdncal.h"

using namespace std;

const char *PersianMonthName[13] = {
    "",
    "Farvardin",
    "Ordibehesht",
    "Khordad",
    "Tir",
    "Mordad",
    "Shahrivar",
    "Mehr",
    "Aban",
    "Azar",
    "Dey",
    "Bahman",
    "Esfand"
};

const char *PersianDayName[7] = {
    "Yekshanbeh",
    "Doshanbeh",
    "Sehshanbeh",
    "ChahArshanbeh",
    "Panjshanbeh",
    "Juma`ah",
    "Shanbeh"
};

int main(int argc, char** argv)
{
    // Declare stuff.
    const long int day_zero = 2443309;
    time_t seconds;
    struct tm *tstruct;
    long int jdn, serial_day = 0;
    int dow;
    bool status = false;

    // Determine if there was a command-line argument.
    if( argc == 2 ) {
        if( !strcmp(argv[1], "--status") ) {
            status = true;
        } else {
            serial_day = atoi(argv[1]);
            jdn = day_zero + serial_day;
            dow = DayOfWeek(jdn);
        }
    }

    // If not, then use the current date.
    if(serial_day == 0) {
        // Get the system date and time.
        time(&seconds);
        tstruct = localtime(&seconds);
        dow = tstruct->tm_wday;

        // Compute the Julian day number and the date on my serial calendar.
        jdn = GregorianToSdn( (tstruct->tm_year + 1900), (tstruct->tm_mon + 1), tstruct->tm_mday );
        serial_day = jdn - day_zero;
    }

    // Compute the Gregorian date (this is redundant since we already have it).
    int g_year, g_month, g_day;
    SdnToGregorian(jdn, &g_year, &g_month, &g_day);

    // Compute the Persian date.
    long p_year; int p_month, p_day;
    day_to_dmy(jdn, &p_day, &p_month, &p_year, CALENDAR_PERSIAN);

    // Output the results.
    // cout << serial_day << "\t" << asctime(tstruct);
    if( status ) {
        cout << setfill('0') << serial_day << " " << DayNameShort[dow] << " ";
        cout << setw(4) << g_year << "-" << setw(2) << g_month << "-" << setw(2) << g_day << " ";
        cout << setw(2) << tstruct->tm_hour << ":" << setw(2) << tstruct->tm_min;
    } else {
        cout << serial_day << " - " << DayNameLong[dow] << ", " << MonthNameLong[g_month] << " " << g_day << ", " << g_year << endl;
        cout << "        " << PersianDayName[dow] << ", " << p_day << " " << PersianMonthName[p_month] << " " << p_year << endl;
    }
}

