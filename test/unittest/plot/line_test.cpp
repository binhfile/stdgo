#if defined(STDGO_UNITTEST) && (defined(STDGO_UNITTEST_PLOT) || defined(STDGO_UNITTEST_ALL))
#include <gtest/gtest.h>

#include <math.h>
#include <stdgo/plot.hpp>
TEST(plot, qt_line) {
    auto plot = stdgo::plot::qt::New();
    ASSERT_NE(plot, nullptr);
    const std::size_t X_COUNT = 128;
    auto x1 = std::make_shared<std::vector<stdgo::plot::Point>>();
    auto x2 = std::make_shared<std::vector<stdgo::plot::Point>>();
    x1->resize(X_COUNT);
    x2->resize(X_COUNT);
    const float PI_CONST = 3.1416f;
    for (std::size_t x = 0; x < X_COUNT; x++) {
        float y = sin(2 * PI_CONST * ((float)x) / (X_COUNT));
        x1->at(x).set_x(((float)x) / (X_COUNT - 1));
        x1->at(x).set_y(y);
        y = sin(2 * PI_CONST * ((float)x) / (X_COUNT)*2);
        x2->at(x).set_x(((float)x) / (X_COUNT - 1));
        x2->at(x).set_y(y);
    }
    plot->AddLine(x1);
    plot->AddLine(x2);
    plot->Show();
}

#endif // STDGO_UNITTEST_PLOT