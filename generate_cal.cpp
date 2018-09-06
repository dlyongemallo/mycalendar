// generate_cal.cpp
// Generate the serial calendar.
// D. L. Yonge-Mallo

#include<iostream>

#include"lunar/watdefs.h"
#include"lunar/date.h"
#include"sdncal.h"

using namespace std;


const char *PersianMonthName[13] = {
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

const char *PersianDayName[7] = {
    "yek^sanbeh",
    "dO^sanbeh",
    "seh\"|^sanbeh",
    "^cahAr^sanbeh",
    "panj\"|^sanbeh",
    "juma`ah",
    "^sanbeh"
};

void print_header(void)
{
    cout << "\\documentclass[18pt]{article}" << endl;
    cout << "\\pagestyle{empty}" << endl;
    cout << "\\usepackage{arabtex}" << endl;
    //cout << "\\usepackage{color}" << endl;
    //cout << "\\usepackage{epsfig}" << endl;
    //cout << "\\usepackage{array}" << endl;
    cout << "\\usepackage{geometry}" << endl;
    //cout << "\\usepackage[left=2cm,top=1cm,right=3cm,nohead,nofoot]{geometry}" <<endl;
    //cout << "\\geometry{letterpaper, width=8in, height=10.5in, nohead, nofoot}" << endl;
    //cout << "\\geometry{letterpaper, width=8in, height=10.5in, nohead, nofoot}" << endl;
    cout << "\\geometry{letterpaper, width=8in}" << endl;
    cout << "\\usepackage{setspace}" << endl;
    //cout << "\\title{Calendar}" << endl;
    //cout << "\\date{}" << endl;
    cout << "\\begin{document} " << endl;
    cout << "\\setfarsi   % set the language" << endl;
    cout << "\\novocalize % no short vowel marks" << endl;
    cout << "\\transfalse % no transliteration" << endl;
    cout << "\\arabtrue   % print Arabic text (on by default)" << endl;
    //cout << "\\maketitle" << endl;
    cout << "\\begin{center}" << endl;

    // hack to make things align
    cout << "~\\\\" << endl;
    cout << "~\\\\" << endl;
    cout << "~\\\\" << endl;

    cout << "\\begin{tabular}{|c|c|c|c|c|c|c|}" << endl;
    //cout << "\\begin{tabular}{|m{1in}|m{1in}|m{1in}|m{1in}|m{1in}|m{1in}|m{1in}|}" << endl;
    cout << "\\hline" << endl;
    cout << "Sun & Mon & Tue & Wed & Thu & Fri & Sat\\\\" << endl;
    cout << "<yek^sanbeh> & <dO^sanbeh> & <seh\"|^sanbeh> & <^cahAr^sanbeh> & <panj\"|^sanbeh> & <juma`ah> & <^sanbeh>\\\\" << endl;
    cout << "\\hline" << endl;
    cout << "\\hline" << endl;
}

void print_footer(void)
{
    cout << "\\end{tabular}" << endl;

    cout << "\\end{center}" << endl;
    cout << "\\end{document}" << endl;
}



int main(int, char**)
{
    const long int day_zero = 2443309;
    //const int start_day = 10806; // add 56 per page
    const int start_day = 10648; // add 56 per page
    const int end_day = start_day + 55;

    // Begin LaTeX document.
    print_header();

    // Print dates.
    for(int serial_day = start_day ; serial_day <= end_day ; serial_day++ )
    {
        // Calculate JDN.
        long int jdn = day_zero + serial_day;
        //int days_remaining = 10000 - serial_day;

        // Find out the (Gregorian) day of week.
        int dow;
        dow = DayOfWeek(jdn);

        // Find the Gregorian calendar date.
        int g_year, g_month, g_day;
        SdnToGregorian(jdn, &g_year, &g_month, &g_day);

        // Find the Persian calendar date.
        long p_year; int p_month, p_day;
        day_to_dmy(jdn, &p_day, &p_month, &p_year, CALENDAR_PERSIAN);

        // Print info for current day in a calendar box.
        cout << "\\begin{minipage}{0.95in}"; // Open the box.
        cout << "\\begin{center}" << endl;
        cout << "~\\\\" << endl;
        cout << "~\\\\" << endl;
        //cout << "{\\huge{" << days_remaining << "}}\\\\" << endl;
        //if( serial_day < 10000) cout << "0";
        //cout << serial_day << "\\\\" << endl;
        cout << "{\\huge{" << serial_day << "}}\\\\" << endl;
        cout << MonthNameLong[g_month] << " " << g_day << "\\\\" << endl;
        cout << "<" << p_day << " " << PersianMonthName[p_month] << ">" << "\\\\" << endl;
        cout << "~\\\\" << endl;
        cout << "~\\\\" << endl;
        cout << "~\\\\" << endl;
        //cout << "~\\\\" << endl;
        cout << "\\end{center}" << endl;
        cout << "\\end{minipage}"; // Close the box.
        if( dow == 6 ) {
            cout << "\\\\" << endl;
            cout << "\\hline" << endl;
        } else {
            cout << " & ";
        }

    }

    // End LaTeX document.
    print_footer();
}

