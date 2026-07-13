#include <iostream>

#include "Scheduler.h"
#include "Job.h"
#include "Clock.h"

int main()
{
    Scheduler scheduler;

    scheduler.addJob(new Job(
        1,
        "Email Service",
        3,
        4,
        Time(9, 0)
    ));

    scheduler.addJob(new Job(
        2,
        "Database Backup",
        5,
        2,
        Time(9, 1)
    ));

    scheduler.addJob(new Job(
        3,
        "Log Cleanup",
        2,
        5,
        Time(9, 3)
    ));

    scheduler.addJob(new Job(
        4,
        "Notification Service",
        4,
        3,
        Time(9, 0)
    ));

    // Cancel one job to test lazy deletion
    scheduler.cancelJob(3);

    scheduler.setCurrentTime(Time(9,0));

    for (int i = 0; i < 10; i++)
    {
        std::cout << "\n=====================================\n";
        std::cout << "Current Time : "
                  << scheduler.getCurrentTime().getHour()
                  << ":";

        if (scheduler.getCurrentTime().getMinute() < 10)
            std::cout << "0";

        std::cout << scheduler.getCurrentTime().getMinute()
                  << "\n";

        scheduler.displayWaitingQueue();

        scheduler.displayReadyQueue();

        scheduler.displayCompletedJobs();

        scheduler.tick();
    }

    std::cout << "\n=========== FINAL STATUS ===========\n";

    scheduler.displayAllJobs();

    return 0;
}