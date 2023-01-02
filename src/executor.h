#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "concurrent_queue.h"
#include <atomic>
#include <chrono>
#include <optional>
#include <thread>
#include <type_traits>

namespace active_object
{

template<typename T>
class Executor
{
    public:
        Executor(ConcurrentQueue<T>& cq, std::atomic<bool>& running):
            queue_ref{cq},
            keep_running{running}
        {}
        void Run()
        {
            while(keep_running)
            {
                std::optional<T> command = queue_ref.dequeue();
                if (!command)
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(5ms);
                    continue;
                }
                auto value = command.value();
                if (std::is_pointer_v<decltype(value)>)
                {
                    value->Execute();
                }
                else
                {
                    value.Execute();
                }
            }
        }
    private:
        ConcurrentQueue<T>& queue_ref;
        std::atomic<bool>& keep_running;
        
};
}
#endif
