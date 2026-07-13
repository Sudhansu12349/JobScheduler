#include "Job.h"

#include <stdexcept>

Job::Job(
    int id,
    const std::string& name,
    int priority,
    int executionTime,
    const Time& scheduledTime)
    : jobId(id),
      jobName(name),
      priority(priority),
      sequenceNumber(0),
      executionTime(executionTime),
      remainingExecutionTime(executionTime),
      retryCount(0),
      scheduledTime(scheduledTime),
      nextEligibleTime(scheduledTime),
      state(JobState::CREATED)
{
    if (id <= 0)
        throw std::invalid_argument("Invalid Job ID.");

    if (name.empty())
        throw std::invalid_argument("Job name cannot be empty.");

    if (priority < 0)
        throw std::invalid_argument("Invalid priority.");

    if (executionTime <= 0)
        throw std::invalid_argument("Execution time must be positive.");
}

//--------------------
// Identity
//--------------------

int Job::getJobId() const
{
    return jobId;
}

const std::string& Job::getJobName() const
{
    return jobName;
}

//--------------------
// Scheduling
//--------------------

int Job::getPriority() const
{
    return priority;
}

long long Job::getSequenceNumber() const
{
    return sequenceNumber;
}

void Job::setSequenceNumber(long long sequence)
{
    sequenceNumber = sequence;
}

//--------------------
// Execution
//--------------------

int Job::getExecutionTime() const
{
    return executionTime;
}

int Job::getRemainingExecutionTime() const
{
    return remainingExecutionTime;
}

bool Job::executeOneTick()
{
    if (remainingExecutionTime > 0)
        remainingExecutionTime--;

    return remainingExecutionTime == 0;
}

bool Job::isFinished() const
{
    return remainingExecutionTime == 0;
}

void Job::resetExecution()
{
    remainingExecutionTime = executionTime;
}

//--------------------
// Retry
//--------------------

int Job::getRetryCount() const
{
    return retryCount;
}

//--------------------
// Timing
//--------------------

const Time& Job::getScheduledTime() const
{
    return scheduledTime;
}

const Time& Job::getNextEligibleTime() const
{
    return nextEligibleTime;
}

const std::optional<Time>& Job::getFirstStartTime() const
{
    return firstStartTime;
}

const std::optional<Time>& Job::getLastStartTime() const
{
    return lastStartTime;
}

const std::optional<Time>& Job::getCompletionTime() const
{
    return completionTime;
}

//--------------------
// State
//--------------------

JobState Job::getState() const
{
    return state;
}

//--------------------
// Lifecycle
//--------------------

void Job::markWaiting()
{
    state = JobState::WAITING;
}

void Job::markReady()
{
    state = JobState::READY;
}

void Job::markRunning(const Time& currentTime)
{
    state = JobState::RUNNING;

    if (!firstStartTime.has_value())
        firstStartTime = currentTime;

    lastStartTime = currentTime;
}

void Job::markCompleted(const Time& currentTime)
{
    state = JobState::COMPLETED;
    completionTime = currentTime;
}

void Job::scheduleRetry(const Time& retryTime)
{
    retryCount++;
    nextEligibleTime = retryTime;
    state = JobState::WAITING;
}

void Job::markCancelled()
{
    state = JobState::CANCELLED;
}

void Job::markRetryLimitExceeded()
{
    state = JobState::RETRY_LIMIT_EXCEEDED;
}