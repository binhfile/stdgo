#if defined(GO_UNITTEST) && defined(GO_UNITTEST_CHART)
#include <gtest/gtest.h>

#include <math.h>
#include <go/chart.hpp>
#ifndef PI
#define PI 3.1416f
#endif

TEST(chart, polar) {
    std::error_code ec;
    std::size_t T = 10;
    std::size_t N = T * 5;

    auto chart = std::make_shared<go::chart::Chart2D>();
    ASSERT_EQ(0, ec.value());
    ASSERT_NE(nullptr, chart);
    chart->SetTitle("Polar");
    chart->SetType(go::chart::Chart2D::Type::kPolar);

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
            points->at(i).set_angle(x);
            points->at(i).set_radius(y + 1);
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
            points->at(i).set_angle(x);
            points->at(i).set_radius(y + 1);
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
            points->at(i).set_angle(x);
            points->at(i).set_radius(y + 1);
        }
    }

    {
        auto *axis = chart->AddAxis(&ec);
        ASSERT_EQ(0, ec.value());
        axis->set_title("angular");
        axis->set_position(go::chart::Axis::Position::kAngular);
        axis->set_minimum(0);
        axis->set_maximum((float)N / T * 1.2);
    }
    {
        auto *axis = chart->AddAxis(&ec);
        ASSERT_EQ(0, ec.value());
        axis->set_title("radial");
        axis->set_position(go::chart::Axis::Position::kRadial);
        axis->set_tick_count(10);
        axis->set_minor_tick_count(5);
        axis->set_minimum(0);
        axis->set_maximum(2.2);
    }

    chart->Save("output.png");
    chart->Show();
}

#endif // GO_UNITTEST_CHART
