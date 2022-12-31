#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <mutex>
#include <optional>
#include <queue>

namespace active_object {
template <typename T>
class ConcurrentQueue {
public:
    void enqueue(T data) noexcept
    {
        std::lock_guard<std::mutex> guard(mtx);
        queue.push(data);
    }
    std::optional<T> dequeue() noexcept
    {
        std::lock_guard<std::mutex> guard(mtx);
        if (queue.empty()) {
            return std::nullopt;
        }
        auto data = queue.front;
        queue.pop();
        return data;
    }

private:
    std::queue<T> queue;
    std::mutex mtx;
};
}
#endif
