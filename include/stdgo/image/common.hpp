#ifndef STDGO_IMAGE_COMMON_H
#define STDGO_IMAGE_COMMON_H
/**
 * @author binhfile
 * @brief Command define
 */

namespace stdgo {
namespace image {

class Image {
  public:
    Image() = default;
    Image(const Image &rhs) = default;
    Image(Image &&rhs) = default;
    Image &operator=(const Image &rhs) = default;
    Image &operator=(Image &&rhs) = default;
};

} // namespace image
} // namespace stdgo

#endif // STDGO_IMAGE_COMMON_H
