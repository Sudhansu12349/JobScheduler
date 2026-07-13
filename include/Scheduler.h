#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "Job.h"
#include "Clock.h"

class Scheduler {
private:

    // Current simulated time
    Time currentTime;
    // Jobs waiting for their scheduled time
    struct WaitingCompare {
    bool operator()(const Job* a, const Job* b) const {

        if (a->getScheduledTime() == b->getScheduledTime())
            return a->getSequenceNumber() > b->getSequenceNumber();

        return a->getScheduledTime() > b->getScheduledTime();
    }
};

    std::priority_queue<
        Job*,
        std::vector<Job*>,
        WaitingCompare
    > waitingQueue;

    // Ready queue (Higher priority first)
    struct ReadyCompare {
    bool operator()(const Job* a, const Job* b) const {

        if (a->getPriority() == b->getPriority())
            return a->getSequenceNumber() > b->getSequenceNumber();

        return a->getPriority() < b->getPriority();
    }
};

    std::priority_queue<
        Job*,
        std::vector<Job*>,
        ReadyCompare
    > readyQueue;

    // Currently executing job
    Job* runningJob;

    // Completed jobs
    std::vector<Job*> completedJobs;

    // All jobs by ID
    std::unordered_map<int, Job*> jobTable;

    // Lazy deletion for cancelled jobs
    std::unordered_set<int> cancelledJobs;

public:

    Scheduler();
    ~Scheduler();

    // Add a new job
    bool addJob(Job* job);

    // Cancel a job
    bool cancelJob(int jobId);

    // Execute one scheduler tick
    void tick();

    // Move waiting jobs whose time has arrived
    void moveWaitingToReady();

    // Select next job to execute
    void dispatchJob();

    // Finish currently running job
    void completeRunningJob();

    // Print information
    void displayReadyQueue();
    void displayWaitingQueue();
    void displayCompletedJobs();
    void displayAllJobs();

    // Time functions
    void setCurrentTime(const Time& time);
    Time getCurrentTime() const;

    // Lookup
    Job* getJob(int jobId) const;

    // Statistics
    int totalJobs() const;
    int completedCount() const;
};

#endif