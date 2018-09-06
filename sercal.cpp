// sercal.cpp
// Serial Calendar
// D. L. Yonge-Mallo

#include<iostream>

#include"lunar/watdefs.h"
#include"lunar/date.h"
#include"sdncal.h"

using namespace std;

char *PersianMonthName[13] = {
    "",
    "farwardIn",
    "ordIbehe^st",
    "_hordAd",
    "tIr",
    "mordAd",
    "^sahrIwar",
    "mehr",
    "AbAn",
    "A_dar",
    "dI",
    "bahman",
    "esfand"
};

int main(int, char**)
{
    const long int day_zero = 2443309;
    //const long int start_day = day_zero + 10427;
    //const long int start_day = day_zero + 10553;
    const long int start_day = day_zero + 11000;
    const long int duration = 31;

    for(int i = 0 ; i < duration ; i++ ) {
        long int jdn = start_day + i;
        long int serial_day = jdn - day_zero;

        // Every third day is special.
        bool third_day;
        third_day = ((serial_day % 3) == 0);

        // Find out the (Gregorian) day of week.
        int dow;
        dow = DayOfWeek(jdn);

        // Find the Gregorian calendar date.
        int g_year, g_month, g_day;
        SdnToGregorian(jdn, &g_year, &g_month, &g_day);

        // Find the Persian calendar date.
	long p_year; int p_month, p_day;
        day_to_dmy(jdn, &p_day, &p_month, &p_year, CALENDAR_PERSIAN);

        // Output the TeX format sections.
        cout << "%----------------------------------------------------------------------" << endl;
        cout << "\\setcounter{page}{" << (serial_day-1) << "}" << endl;
        cout << "\\setcounter{section}{" << (serial_day-1) << "}" << endl;
        cout << "\\newpage" << endl;

//#define PERSONAL
#ifdef PERSONAL // Include Persian calendar date
        cout << "\\section{[0x" << hex << serial_day << dec << "]";
        if( third_day ) cout << "*";
        cout << " - " << DayNameLong[dow] << ", " << MonthNameLong[g_month]
             << " " << g_day << ", " << g_year << " / <"
             << PersianMonthName[p_month] << " " << p_day << ", "
             << p_year << ">} % " << serial_day << endl;
        cout << endl;
#else // Regular (Gregorian) date only
        cout << "\\section{";
        cout << DayNameLong[dow] << ", " << MonthNameLong[g_month]
             << " " << g_day << ", " << g_year
             << "} % " << serial_day << endl;
        cout << endl;
#endif

        // List of tasks.
        cout << "\\begin{itemize}" << endl;
#ifdef PERSONAL
        cout << "\\item (personal log entry)" << endl;
        cout << "\\item Lesson Of The Day: " << endl;
#else
        //if( serial_day < 9770 )
        //    cout << "\\item CS 882 Project." << endl;
        //else if( serial_day == 9770 )
        //    cout << "\\item {\\bf Finish CS 882 Project!}" << endl;
        cout << "\\item (Ph.D. research)" << endl;
#endif
        /*if( third_day ) {
            // A day for repeating stuff.
            cout << "\\item Repeat Days " << serial_day - 5 << ", "
                 << serial_day - 4 << ", " << serial_day - 2
                 << " \\& " << serial_day - 1 << "." << endl;
        }*/
        cout << "\\end{itemize}" << endl;
        //cout << endl;
        //cout << "\\begin{tabular}{rcl}" << endl;
        //cout << " & & \\\\" << endl;
        //cout << "\\end{tabular}" << endl;

        cout << endl;
    }
}
