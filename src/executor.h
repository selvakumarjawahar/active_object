#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "concurrent_queue.h"
#include <chrono>
#include <optional>
#include <thread>

namespace active_object
{
template<typename T>
class Executor
{
    public:
        explicit Executor(ConcurrentQueue<T>& cq):
            queue_ref{cq}
        {}
        void Run()
        {
            while(true)
            {
                std::optional<T> command = queue_ref.dequeue();
                if (!command)
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(5ms);
                    continue;
                }
                command.value()->Execute();
            }
        }
    private:
        ConcurrentQueue<T>& queue_ref;
};
}
#endif
