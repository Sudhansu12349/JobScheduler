#include "Clock.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>

Time::Time() : totalMinutes(0)
{
}

Time::Time(int hours, int minutes)
{
    setTime(hours, minutes);
}

Time::Time(int totalMinutes)
{
    if (totalMinutes < 0 || totalMinutes >= 24 * 60)
        throw std::invalid_argument("Invalid time.");

    this->totalMinutes = totalMinutes;
}

void Time::setTime(int hours, int minutes)
{
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
        throw std::invalid_argument("Invalid time.");

    totalMinutes = hours * 60 + minutes;
}

void Time::addMinutes(int minutes)
{
    if (minutes < 0)
        throw std::invalid_argument("Negative minutes not allowed.");

    totalMinutes = (totalMinutes + minutes) % (24 * 60);
}

int Time::getHour() const
{
    return totalMinutes / 60;
}

int Time::getMinute() const
{
    return totalMinutes % 60;
}

int Time::getTotalMinutes() const
{
    return totalMinutes;
}

std::string Time::toString() const
{
    std::ostringstream out;

    out << std::setw(2) << std::setfill('0') << getHour()
        << ":"
        << std::setw(2) << std::setfill('0') << getMinute();

    return out.str();
}

bool Time::operator<(const Time& other) const
{
    return totalMinutes < other.totalMinutes;
}

bool Time::operator>(const Time& other) const
{
    return totalMinutes > other.totalMinutes;
}

bool Time::operator<=(const Time& other) const
{
    return totalMinutes <= other.totalMinutes;
}

bool Time::operator>=(const Time& other) const
{
    return totalMinutes >= other.totalMinutes;
}

bool Time::operator==(const Time& other) const
{
    return totalMinutes == other.totalMinutes;
}

bool Time::operator!=(const Time& other) const
{
    return totalMinutes != other.totalMinutes;
}