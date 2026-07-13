#pragma once

#include <string>

class Time
{
private:
    int totalMinutes;

public:
    Time();
    Time(int hours, int minutes);
    explicit Time(int totalMinutes);

    void setTime(int hours, int minutes);
    void addMinutes(int minutes);

    int getHour() const;
    int getMinute() const;
    int getTotalMinutes() const;

    std::string toString() const;

    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
};