#ifndef COMMAND_H
#define COMMAND_H

#include <future>
#include <string>

namespace active_object {
struct Result {
    std::string data;
    bool valid = false;
    std::string err_reason;
};

struct CommandInterface {
    virtual std::future<Result> GetFuture() = 0;
    virtual void Execute() = 0;
    virtual ~CommandInterface() = default;
};

class GetRecommendations : public CommandInterface {
public:
    std::future<Result> GetFuture() override;
    void Execute() override;

private:
    // Some other methods and data to help generate the results.
    std::promise<Result> async_result;
};

class GetPredictions : public CommandInterface {
public:
    std::future<Result> GetFuture() override;
    void Execute() override;

private:
    // Some other methods and data to help generate the results.
    std::promise<Result> async_result;
};
}

#endif
