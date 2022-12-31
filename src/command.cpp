#include "command.h"
#include <future>

namespace active_object {
std::future<Result> GetRecommendations::GetFuture()
{
    return async_result.get_future();
}

void GetRecommendations::Execute()
{
    Result result;
    // Do whatever needed to get the results.
    // This could be a rpc call, or REST API or any other processsing
    result.data = "Recommendations";
    result.valid = true;
    async_result.set_value(result);
}

std::future<Result> GetPredictions::GetFuture()
{
    return async_result.get_future();
}

void GetPredictions::Execute()
{
    Result result;
    // Do whatever needed to get the results.
    // This could be a rpc call, or REST API or any other processsing
    result.data = "Predictions";
    result.valid = true;
    async_result.set_value(result);
}

}
