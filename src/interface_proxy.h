#ifndef INTERFACE_PROXY_H
#define INTERFACE_PROXY_H

#include "command.h"
#include "concurrent_queue.h"

#include <atomic>
#include <future>
#include <memory>
#include <string>
#include <thread>


namespace active_object
{
    using CommandQ = ConcurrentQueue<std::unique_ptr<CommandInterface>>;
    using AsyncResult = std::future<Result>;

    class Proxy
    {
        public:
            Proxy();
            AsyncResult GetPrediction(std::string inp_data);
            AsyncResult GetRecommendation(std::string inp_data);
            ~Proxy();

        private:
            CommandQ cmd_q;
            std::atomic<bool> running;
            std::thread cmd_executor;

    };

}

#endif
