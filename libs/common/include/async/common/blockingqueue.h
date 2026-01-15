#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

namespace async::common {

    template<typename T>
    class BlockingQueue {
    public:
        void push(T value) {
            {
                std::lock_guard lock(m_mutex);
                m_queue.push(std::move(value));
            }
            m_cv.notify_one();
        }

        std::optional<T> pop() {
            std::unique_lock lock(m_mutex);
            m_cv.wait(lock, [&] {
                return m_stopped || !m_queue.empty();
            });

            if (m_queue.empty())
                return std::nullopt;

            T value = std::move(m_queue.front());
            m_queue.pop();
            return value;
        }

        void stop() {
            {
                std::lock_guard lock(m_mutex);
                m_stopped = true;
            }
            m_cv.notify_all();
        }

    private:
        std::queue<T> m_queue;
        std::mutex m_mutex;
        std::condition_variable m_cv;
        bool m_stopped{false};
    };

}
