#ifndef STDGO_FMT_SPRINTF_H
#define STDGO_FMT_SPRINTF_H
/**
 * @author binhfile
 * @brief Format string
 */
#include <string>

namespace stdgo {
namespace fmt {

template <typename Fmt, typename T, typename... Args>
std::string Sprintf(Fmt &&format, T &&t, Args &&... args) {}

template <typename Fmt, typename... Args>
std::string Sprintf(Fmt &&format, Args &&... args) {
    return Sprintf(std::forward<Fmt>(format), std::forward<Args>(args)...);
}

} // namespace fmt
} // namespace stdgo

#endif // STDGO_FMT_SPRINTF_H
