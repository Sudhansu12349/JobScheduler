#pragma once

enum class JobState
{
    CREATED,
    WAITING,
    READY,
    RUNNING,
    COMPLETED,
    FAILED,
    CANCELLED,
    RETRY_LIMIT_EXCEEDED
};