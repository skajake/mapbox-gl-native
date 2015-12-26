#ifndef MBGL_STORAGE_HTTP_REQUEST_BASE
#define MBGL_STORAGE_HTTP_REQUEST_BASE

#include <mbgl/storage/request_base.hpp>
#include <mbgl/util/chrono.hpp>

namespace mbgl {

    class HTTPRequestBase : public RequestBase {
public:
    HTTPRequestBase(const std::string& url_, Callback notify_)
        : RequestBase(url_, notify_)
        , cancelled(false) {
    }

    virtual ~HTTPRequestBase() = default;
    virtual void cancel() override { cancelled = true; };

protected:
    static Seconds parseCacheControl(const char *value);

    bool cancelled;
};

} // namespace mbgl

#endif // MBGL_STORAGE_HTTP_REQUEST_BASE
