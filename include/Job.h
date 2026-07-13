#pragma once

#include <optional>
#include <string>

#include "JobState.h"
#include "Clock.h"

class Job
{
private:

    // Identity
    int jobId;
    std::string jobName;

    // Scheduling
    int priority;
    long long sequenceNumber;

    // Execution
    int executionTime;
    int remainingExecutionTime;
    int retryCount;

    // Timing
    Time scheduledTime;
    Time nextEligibleTime;

    std::optional<Time> firstStartTime;
    std::optional<Time> lastStartTime;
    std::optional<Time> completionTime;

    // State
    JobState state;

public:

    Job(
        int id,
        const std::string& name,
        int priority,
        int executionTime,
        const Time& scheduledTime
    );

    // Identity
    int getJobId() const;
    const std::string& getJobName() const;

    // Scheduling
    int getPriority() const;
    long long getSequenceNumber() const;
    void setSequenceNumber(long long sequence);

    // Execution
    int getExecutionTime() const;
    int getRemainingExecutionTime() const;

    bool executeOneTick();
    bool isFinished() const;
    void resetExecution();

    // Retry
    int getRetryCount() const;

    // Timing
    const Time& getScheduledTime() const;
    const Time& getNextEligibleTime() const;

    const std::optional<Time>& getFirstStartTime() const;
    const std::optional<Time>& getLastStartTime() const;
    const std::optional<Time>& getCompletionTime() const;

    // State
    JobState getState() const;

    // Lifecycle
    void markWaiting();
    void markReady();
    void markRunning(const Time& currentTime);
    void markCompleted(const Time& currentTime);

    void scheduleRetry(const Time& retryTime);

    void markCancelled();
    void markRetryLimitExceeded();
};