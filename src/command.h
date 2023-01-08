#ifndef COMMAND_H
#define COMMAND_H

#include <future>
#include <string>

namespace active_object {
/*!
 * @brief Result struct which holds the result of the async operation.
 */
struct Result {
    std::string data;
    bool valid = false;
    std::string err_reason;
};

/*!
 * @brief Abstract class which defines the Command interface.
 * Concrete commands will implement this interface.
 */
struct CommandInterface {
    virtual std::future<Result> GetFuture() = 0;
    virtual void Execute() = 0;
    virtual ~CommandInterface() = default;
};

/*!
 * @brief Concrete implementation of the CommandInterface.
 * This class will hold all the information needed to get the
 * recommendation data from the cloud service.
 */
class RecommendationCmd : public CommandInterface {
public:
    explicit RecommendationCmd(std::string inp)
        : input(std::move(inp))
    {
    }
    std::future<Result> GetFuture() override;
    void Execute() override;

private:
    // Some other methods and data to help generate the results.
    std::promise<Result> async_result;
    std::string input;
};

/*!
 * @brief Another concerete implementation of CommandInterface.
 */
class PredictionCmd : public CommandInterface {
public:
    explicit PredictionCmd(std::string inp)
        : input(std::move(inp))
    {
    }
    std::future<Result> GetFuture() override;
    void Execute() override;

private:
    // Some other methods and data to help generate the results.
    std::promise<Result> async_result;
    std::string input;
};
}

#endif
