#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "concurrent_queue.h"
#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <optional>
#include <thread>
#include <type_traits>

namespace active_object
{

template<typename T> struct is_smart_ptr : std::false_type {};
template<typename T> struct is_smart_ptr<std::shared_ptr<T>> : std::true_type{};
template<typename T> struct is_smart_ptr<std::unique_ptr<T>> : std::true_type{};

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
                std::optional<T> cmd_opt = queue_ref.dequeue();
                if (!cmd_opt.has_value())
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(5ms);
                    continue;
                }
                auto cmd = std::move(cmd_opt.value());
                if constexpr (std::is_pointer<T>::value  || is_smart_ptr<T>::value)
                {
                    cmd->Execute();
                }
                else
                {
                    cmd.Execute();
                }
            }
        }
    private:
        ConcurrentQueue<T>& queue_ref;
        std::atomic<bool>& keep_running;
        
};
}
#endif
