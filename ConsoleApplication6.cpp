#include<iostream>
#include<ctime>
#include<string>

using namespace std;

// create the clock class
class Clock {
private:
    // variables to store alarm data
    bool alarm_on = false;
    int alarm_hours;
    int alarm_minutes;
public:
    // constructor
    Clock() {}
    // function to get hour
    virtual int get_hours() {
        time_t current_time = time(0);
        tm* local_time = localtime(&current_time);
        return local_time->tm_hour;
    }
    // function to get minute
    virtual int get_minutes() {
        time_t current_time = time(0);
        tm* local_time = localtime(&current_time);
        return local_time->tm_min;
    }
    // function to get time
    string get_time() {
        int hours = get_hours();
        int minutes = get_minutes();
        // combine them into a string
        string TEEtime = to_string(hours) + ":" + to_string(minutes);
        // alarm checker
        if (alarm_on && alarm_hours <= hours && alarm_minutes <= minutes) {
            //add alarm to the string
            TEEtime += " Alarm";
            alarm_on = false;
        }
        //return string
        return TEEtime;
    }
    // function to set an alarm
    void set_alarm(int hours, int minutes) {
        alarm_on = true;
        alarm_hours = hours;
        alarm_minutes = minutes;
    }
};

// WorldClock class from 10.1

class WorldClock : public Clock 
{
private:
    int time_offset;
public:
    WorldClock(int offset) {
        time_offset = offset;
    }
    // offsetting the hours function to adjust to world clock
    int get_hours() {
        // get hours from clock class
        int hours = Clock::get_hours();
        return hours + time_offset;
    }
};

// main function to test code
int main() {
    Clock clk;
    WorldClock wclk(1);
    int alarm_h = 21;
    int alarm_m = 15;
    cout << clk.get_time() << endl;
    cout << wclk.get_time() << endl;
    cout << "Alarm is set for " << alarm_h << ":" << alarm_m << endl;
    wclk.set_alarm(alarm_h, alarm_m);
    cout << wclk.get_time() << endl;
    return 0;
}