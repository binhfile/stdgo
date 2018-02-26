#ifndef STDGO_IMAGE_PNG_H
#define STDGO_IMAGE_PNG_H
/**
 * @author binhfile
 * @brief Encode, decode PNG image format
 */

#include "common.hpp"
#include <ostream>
#include <system_error>

namespace stdgo {
namespace image {
namespace png {
void Encode(std::ostream *os, const Image &img, std::error_code *ec = nullptr);
}
} // namespace image
} // namespace stdgo

#endif
