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

class RecommendationCmd : public CommandInterface {
public:
    explicit RecommendationCmd(std::string inp) :
        input(std::move(inp)){}
    std::future<Result> GetFuture() override;
    void Execute() override;

private:
    // Some other methods and data to help generate the results.
    std::promise<Result> async_result;
    std::string input;
};

class PredictionCmd : public CommandInterface {
public:
    explicit PredictionCmd(std::string inp):
        input(std::move(inp))
    {}
    std::future<Result> GetFuture() override;
    void Execute() override;

private:
    // Some other methods and data to help generate the results.
    std::promise<Result> async_result;
    std::string input;
};
}

#endif
