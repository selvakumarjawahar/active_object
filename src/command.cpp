#include "command.h"
#include <future>

namespace active_object {
std::future<Result> RecommendationCmd::GetFuture()
{
    return async_result.get_future();
}

void RecommendationCmd::Execute()
{
    Result result;
    // Do whatever needed to get the results.
    // This could be a rpc call, or REST API or any other processsing
    result.data = "Recommendations";
    result.valid = true;
    async_result.set_value(result);
}

std::future<Result> PredictionCmd::GetFuture()
{
    return async_result.get_future();
}

void PredictionCmd::Execute()
{
    Result result;
    // Do whatever needed to get the results.
    // This could be a rpc call, or REST API or any other processsing
    result.data = "Predictions";
    result.valid = true;
    async_result.set_value(result);
}

}
