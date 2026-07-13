#pragma once

#include "Job.h"

class ExecutionPolicy
{
public:
    virtual bool execute(const Job& job) = 0;
    virtual ~ExecutionPolicy() = default;
};

class AlwaysSuccessPolicy : public ExecutionPolicy
{
public:
    bool execute(const Job& job) override;
};

class AlwaysFailPolicy : public ExecutionPolicy
{
public:
    bool execute(const Job& job) override;
};

class RandomExecutionPolicy : public ExecutionPolicy
{
private:
    int successRate;

public:
    explicit RandomExecutionPolicy(int successRate = 80);

    bool execute(const Job& job) override;
};