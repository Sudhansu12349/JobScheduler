#pragma once

#include "Job.h"

class ReadyComparator
{
public:
    bool operator()(const Job* a, const Job* b) const;
};

class WaitingComparator
{
public:
    bool operator()(const Job* a, const Job* b) const;
};