#include "Scheduler.h"
#include<iostream>

// =====================================================
// Constructor / Destructor
// =====================================================

Scheduler::Scheduler()
    : currentTime(), runningJob(nullptr)
{
}

Scheduler::~Scheduler() {

    for (auto &it : jobTable) {
        delete it.second;
    }

    jobTable.clear();
}

// =====================================================
// Job Management
// =====================================================

bool Scheduler::addJob(Job* job) {

    if (job == nullptr)
        return false;

    int id = job->getJobId();

    // Duplicate Job ID
    if (jobTable.count(id))
        return false;

    jobTable[id] = job;
    job->markWaiting();

    // Initially every job waits for its scheduled time
    static long long sequence = 0;
    job->setSequenceNumber(sequence++);

     waitingQueue.push(job);

    return true;
}

bool Scheduler::cancelJob(int jobId)
{
    auto it = jobTable.find(jobId);

    // Job doesn't exist
    if (it == jobTable.end())
        return false;

    // If already cancelled
    if (cancelledJobs.count(jobId))
        return false;

    // If already completed
    if (it->second->isFinished())
        return false;

    cancelledJobs.insert(jobId);

    return true;
}

// =====================================================
// Scheduler Logic
// =====================================================

void Scheduler::tick()
{
    // Move eligible jobs to ready queue
    moveWaitingToReady();

    // If CPU is idle, schedule next job
    if (runningJob == nullptr)
        dispatchJob();

    // Execute current job
    if (runningJob != nullptr)
    {
        runningJob->executeOneTick();

        if (runningJob->isFinished())
        {
            completeRunningJob();
        }
    }

    // Advance simulation time by one minute
    currentTime = Time(currentTime.getTotalMinutes() + 1);
}

void Scheduler::moveWaitingToReady()
{
    while (!waitingQueue.empty())
    {
        Job* job = waitingQueue.top();

        // Remove cancelled jobs
        if (cancelledJobs.count(job->getJobId()))
        {
            waitingQueue.pop();
            continue;
        }

        // Stop if the next job is not yet scheduled
        if (job->getScheduledTime() > currentTime)
            break;

        waitingQueue.pop();
        job->markReady();
        readyQueue.push(job);
    }
}

void Scheduler::dispatchJob()
{
    while (!readyQueue.empty())
    {
        Job* job = readyQueue.top();
        readyQueue.pop();

        // Skip cancelled jobs
        if (cancelledJobs.count(job->getJobId()))
            continue;
        job->markRunning(currentTime);
        runningJob = job;
        return;
    }
     
    // No ready job available
    runningJob = nullptr;
}

void Scheduler::completeRunningJob()
{
    if (runningJob == nullptr)
        return;
    runningJob->markCompleted(currentTime);
    completedJobs.push_back(runningJob);

    runningJob = nullptr;
}

// =====================================================
// Display Functions
// =====================================================

void Scheduler::displayReadyQueue()
{
    std::priority_queue<Job*, std::vector<Job*>, ReadyCompare> temp = readyQueue;

    std::cout << "\n===== Ready Queue =====\n";

    if (temp.empty())
    {
        std::cout << "Empty\n";
        return;
    }

    while (!temp.empty())
    {
        Job* job = temp.top();
        temp.pop();

        if (cancelledJobs.count(job->getJobId()))
            continue;

        std::cout << "ID: " << job->getJobId()
                  << "  Name: " << job->getJobName()
                  << "  Priority: " << job->getPriority()
                  << "  Remaining: " << job->getRemainingExecutionTime()
                  << '\n';
    }
}

void Scheduler::displayWaitingQueue()
{
    std::priority_queue<Job*, std::vector<Job*>, WaitingCompare> temp = waitingQueue;

    std::cout << "\n===== Waiting Queue =====\n";

    if (temp.empty())
    {
        std::cout << "Empty\n";
        return;
    }

    while (!temp.empty())
    {
        Job* job = temp.top();
        temp.pop();

        if (cancelledJobs.count(job->getJobId()))
            continue;

        std::cout << "ID: " << job->getJobId()
          << "  Name: " << job->getJobName()
          << "  Priority: " << job->getPriority()
          << "  Scheduled: "
          << job->getScheduledTime().getHour() << ":";

        if (job->getScheduledTime().getMinute() < 10)
           std::cout << "0";

        std::cout << job->getScheduledTime().getMinute() << '\n';
    }
}

void Scheduler::displayCompletedJobs()
{
    std::cout << "\n===== Completed Jobs =====\n";

    if (completedJobs.empty())
    {
        std::cout << "None\n";
        return;
    }

    for (Job* job : completedJobs)
    {
        std::cout << "ID: " << job->getJobId()
                  << "  Name: " << job->getJobName()
                  << "  Priority: " << job->getPriority()
                  << '\n';
    }
}
void Scheduler::displayAllJobs()
{
    std::cout << "\n===== All Jobs =====\n";

    if (jobTable.empty())
    {
        std::cout << "No Jobs\n";
        return;
    }

    for (const auto& entry : jobTable)
    {
        Job* job = entry.second;

        std::cout << "ID: " << job->getJobId()
                  << "  Name: " << job->getJobName()
                  << "  Priority: " << job->getPriority()
                  << "  Remaining: " << job->getRemainingExecutionTime();

        if (cancelledJobs.count(job->getJobId()))
            std::cout << " [Cancelled]";
        else if (job->isFinished())
            std::cout << " [Completed]";
        else
            std::cout << " [Active]";

        std::cout << '\n';
    }
}

// =====================================================
// Time Functions
// =====================================================

void Scheduler::setCurrentTime(const Time& time) {
    currentTime = time;
}

Time Scheduler::getCurrentTime() const {
    return currentTime;
}

// =====================================================
// Utility Functions
// =====================================================

Job* Scheduler::getJob(int jobId) const {
    auto it = jobTable.find(jobId);

    if (it == jobTable.end())
        return nullptr;

    return it->second;
}

int Scheduler::totalJobs() const {
    return static_cast<int>(jobTable.size());
}

int Scheduler::completedCount() const {
    return static_cast<int>(completedJobs.size());
}
