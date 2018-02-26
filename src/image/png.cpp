#include "../../include/stdgo/image/png.hpp"

#include <cstdint>
#include <type_traits>

namespace {

template <typename T, typename I>
inline T static_cast_pointer(I &&i) {
    return static_cast<T>(static_cast<const void *>(std::forward<I>(i)));
}

class Header {
  public:
    Header() {}
    virtual ~Header() = default;

    constexpr static uint64_t magic = (uint64_t)0x0A1A0D0A504E4789;
};
std::ostream &operator<<(std::ostream &os, const Header &hdr) {
    uint64_t magic = Header::magic;
    os.write(static_cast_pointer<const char *>(&magic), sizeof(magic));
    return os;
}

} // namespace

namespace stdgo {
namespace image {
namespace png {
void Encode(std::ostream *os, const Image &img, std::error_code *ec) {
    // write header
    Header hdr;
    *os << hdr;
}

} // namespace png
} // namespace image
} // namespace stdgo
