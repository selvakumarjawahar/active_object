#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <mutex>
#include <optional>
#include <queue>

namespace active_object {
/*!
 * @brief this is a thread safe Queue which is used to hold the Commands.We are using coarse grained
 * locking to keep the example simple. If better performance is needed one can implement a thread safe
 * Queue with more fine grained locking or use a thirdparty implementation of a Concurrent Queue
 */
template <typename T>
class ConcurrentQueue {
public:
    void enqueue(T data) noexcept
    {
        std::lock_guard<std::mutex> guard(mtx);
        queue.push(std::move(data));
    }
    std::optional<T> dequeue() noexcept
    {
        std::lock_guard<std::mutex> guard(mtx);
        if (queue.empty()) {
            return std::nullopt;
        }
        auto data = std::move(queue.front());
        queue.pop();
        return data;
    }

private:
    std::queue<T> queue;
    std::mutex mtx;
};
}
#endif
