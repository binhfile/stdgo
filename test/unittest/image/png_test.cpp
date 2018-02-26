#if defined(STDGO_UNITTEST)
#if defined(STDGO_UNITTEST_ALL) || defined(STDGO_UNITTEST_IMAGE)
#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <stdgo/image/png.hpp>

TEST(image, png) {
    std::error_code ec;

    auto img = std::make_shared<stdgo::image::Image>();
    ASSERT_NE(nullptr, img);

    std::ofstream file;
    file.open("output.png");
    ASSERT_TRUE(file.good());

    stdgo::image::png::Encode(&file, *img.get(), &ec);
}

#endif
#endif
