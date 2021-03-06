#include <mbgl/util/timer.hpp>

#include <mbgl/util/run_loop.hpp>

#include <uv.h>

#if UV_VERSION_MAJOR == 0 && UV_VERSION_MINOR <= 10
#define UV_TIMER_PARAMS(timer) uv_timer_t *timer, int
#else
#define UV_TIMER_PARAMS(timer) uv_timer_t *timer
#endif

namespace mbgl {
namespace util {

class Timer::Impl {
public:
    Impl() : timer(new uv_timer_t) {
        uv_loop_t* loop = reinterpret_cast<uv_loop_t*>(RunLoop::getLoopHandle());
        if (uv_timer_init(loop, timer) != 0) {
            throw std::runtime_error("Failed to initialize timer.");
        }

        handle()->data = this;
    }

    ~Impl() {
        uv_close(handle(), [](uv_handle_t* h) {
            delete reinterpret_cast<uv_timer_t*>(h);
        });
    }

    void start(uint64_t timeout, uint64_t repeat, std::function<void ()>&& cb_) {
        cb = std::move(cb_);
        if (uv_timer_start(timer, timerCallback, timeout, repeat) != 0) {
            throw std::runtime_error("Failed to start timer.");
        }
    }

    void stop() {
        cb = nullptr;
        if (uv_timer_stop(timer) != 0) {
            throw std::runtime_error("Failed to stop timer.");
        }
    }

    void unref() {
        uv_unref(handle());
    }

private:
    static void timerCallback(UV_TIMER_PARAMS(handle)) {
        reinterpret_cast<Impl*>(handle->data)->cb();
    }

    uv_handle_t* handle() {
        return reinterpret_cast<uv_handle_t*>(timer);
    }

    uv_timer_t* timer;

    std::function<void()> cb;
};

Timer::Timer()
    : impl(std::make_unique<Impl>()) {
}

Timer::~Timer() = default;

void Timer::start(Duration timeout, Duration repeat, std::function<void()>&& cb) {
    impl->start(std::chrono::duration_cast<std::chrono::milliseconds>(timeout).count(),
                std::chrono::duration_cast<std::chrono::milliseconds>(repeat).count(),
                std::move(cb));
}

void Timer::stop() {
    impl->stop();
}

void Timer::unref() {
    impl->unref();
}

} // namespace util
} // namespace mbgl
