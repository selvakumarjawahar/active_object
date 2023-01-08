#include "interface_proxy.h"
#include <memory>

namespace active_object {
Proxy::Proxy()
    : running(true)
    , executor(cmd_q, running)
{
    executor_task = std::thread(&CommandExecutor::Run, &executor);
}

AsyncResult Proxy::GetPrediction(std::string inp_data)
{
    auto prediction_cmd = std::make_unique<PredictionCmd>(std::move(inp_data));
    AsyncResult result = prediction_cmd->GetFuture();
    cmd_q.enqueue(std::move(prediction_cmd));
    return result;
}

AsyncResult Proxy::GetRecommendation(std::string inp_data)
{
    auto recommendation_cmd = std::make_unique<RecommendationCmd>(std::move(inp_data));
    AsyncResult result = recommendation_cmd->GetFuture();
    cmd_q.enqueue(std::move(recommendation_cmd));
    return result;
}
Proxy::~Proxy()
{
    running = false;
    if (executor_task.joinable()) {
        executor_task.join();
    }
}
}
