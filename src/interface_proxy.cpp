#include "interface_proxy.h"
#include <memory>

namespace active_object
{
    Proxy::Proxy()
    {

    }

    AsyncResult Proxy::GetPrediction(std::string inp_data)
    {
        auto recommendation_cmd = std::make_unique<RecommendationCmd>(std::move(inp_data));
        AsyncResult result = recommendation_cmd->GetFuture();
        cmd_q.enqueue(std::move(recommendation_cmd));
        return result;
    }

    AsyncResult Proxy::GetRecommendation(std::string inp_data)
    {

    }

    Proxy::~Proxy()
    {

    }
}
