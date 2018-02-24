#if defined(GO_UNITTEST) && defined(GO_UNITTEST_CHART)
#include <gtest/gtest.h>

#include <math.h>
#include <go/chart.hpp>
#ifndef PI
#define PI 3.1416f
#endif

TEST(chart, line) {
    std::error_code ec;
    std::size_t T = 10;
    std::size_t N = T * 5;

    auto chart = std::make_shared<go::chart::Chart2D>();
    ASSERT_EQ(0, ec.value());
    ASSERT_NE(nullptr, chart);
    chart->SetTitle("Line 2D");
    chart->SetType(go::chart::Chart2D::Type::kLine);

    {
        auto *line = chart->AddLine(&ec);
        ASSERT_EQ(0, ec.value());
        ASSERT_NE(nullptr, line);

        line->set_title("point");
        line->set_type(go::chart::PointSeries2D::Type::kPoint);
        auto *points = line->mutable_points();
        points->resize(N);
        for (std::size_t i = 0; i < N; i++) {
            float x = (float)i / T;
            float y = sin(2 * PI * x);
            points->at(i).set_x(x + 1);
            points->at(i).set_y(y + 2);
        }
    }
    {
        auto *line = chart->AddLine(&ec);
        ASSERT_EQ(0, ec.value());
        ASSERT_NE(nullptr, line);

        line->set_title("smooth");
        line->set_type(go::chart::PointSeries2D::Type::kSmooth);
        auto *points = line->mutable_points();
        points->resize(N);
        for (std::size_t i = 0; i < N; i++) {
            float x = (float)i / T;
            float y = sin(2 * PI * x);
            points->at(i).set_x(x + 1);
            points->at(i).set_y(y + 2);
        }
    }
    {
        auto *line = chart->AddLine(&ec);
        ASSERT_EQ(0, ec.value());
        ASSERT_NE(nullptr, line);

        line->set_title("line");
        line->set_type(go::chart::PointSeries2D::Type::kLine);
        auto *points = line->mutable_points();
        points->resize(N);
        for (std::size_t i = 0; i < N; i++) {
            float x = (float)i / T;
            float y = ((float)i / N);
            points->at(i).set_x(x + 1);
            points->at(i).set_y(y + 2);
        }
    }

    {
        auto *axis = chart->AddAxis(&ec);
        ASSERT_EQ(0, ec.value());
        axis->set_title("logarithm");
        axis->set_position(go::chart::Axis::Position::kBottom);
        axis->set_logarithm(true);
    }
    {
        auto *axis = chart->AddAxis(&ec);
        ASSERT_EQ(0, ec.value());
        axis->set_title("linear");
        axis->set_position(go::chart::Axis::Position::kLeft);
        axis->set_tick_count(10);
        axis->set_minor_tick_count(5);
        axis->set_minimum(0.5);
        axis->set_maximum(3.5);
    }

    chart->Save("output.png");
    chart->Show();
}

#endif // GO_UNITTEST_CHART
