/**
 * @author binhfile
 * @brief Line2D backend by QT
 */
#if defined(STDGO_HAS_CONFIG_H)
#include <stdgo_config.hpp>
#endif

#if (defined(STDGO_ENABLE_ALL) || defined(STDGO_ENABLE_CHART)) && defined(STDGO_ENABLE_CHART_BACKEND_QT)
#include "../include/stdgo/chart/line.hpp"

#include <list>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

#ifndef UNUSED
#define UNUSED(x) (void)x
#endif

namespace stdgo {
namespace chart {

class Line2DImpl {
  private:
    std::list<std::shared_ptr<LineData2D>> lst_line_;
    std::list<std::shared_ptr<Axis>> lst_axis_;
    std::string title_;
    QtCharts::QChartView *chart_;

  public:
    Line2DImpl() : chart_{nullptr} {}
    Line2DImpl(const Line2DImpl &rhs) : chart_{nullptr} {
        // copy constructor
        for (const auto &src : rhs.lst_line_) {
            lst_line_.push_back(std::make_shared<LineData2D>(*src));
        }
        for (const auto &src : rhs.lst_axis_) {
            lst_axis_.push_back(std::make_shared<Axis>(*src));
        }
    }
    Line2DImpl(Line2DImpl &&rhs) noexcept : chart_{nullptr} {
        // move constructor
        lst_line_ = std::move(rhs.lst_line_);
        lst_axis_ = std::move(rhs.lst_axis_);
    }
    Line2DImpl &operator=(const Line2DImpl &rhs) {
        // copy assigment
        for (const auto &src : rhs.lst_line_) {
            lst_line_.push_back(std::make_shared<LineData2D>(*src));
        }
        for (const auto &src : rhs.lst_axis_) {
            lst_axis_.push_back(std::make_shared<Axis>(*src));
        }
        return *this;
    }
    Line2DImpl &operator=(Line2DImpl &&rhs) noexcept {
        // move assigment
        this->lst_line_ = std::move(rhs.lst_line_);
        this->lst_axis_ = std::move(rhs.lst_axis_);
        return *this;
    }
    virtual ~Line2DImpl() = default;
    void Show(std::error_code *ec) {
        UNUSED(ec);
        int argc = 1;
        uint8_t argv0[32] = {0};
        memmove(&argv0[0], "qt", 2);
        char *argv[] = {static_cast<char *>(static_cast<void *>(&argv0[0]))};
        QApplication a(argc, &argv[0]);
        QMainWindow window;
        if (chart_ == nullptr) {
            render();
        }
        if (chart_ != nullptr) {
            window.setCentralWidget(chart_);
            QScreen *screen = QGuiApplication::primaryScreen();
            QRect screenGeometry = screen->geometry();
            window.resize(screenGeometry.width() / 2, screenGeometry.height() / 2);
            window.show();
            a.exec();
        }
    }
    void Save(const std::string &image_path, std::error_code *ec) {
        UNUSED(ec);
        int argc = 1;
        uint8_t argv0[32] = {0};
        memmove(&argv0[0], "qt", 2);
        char *argv[] = {static_cast<char *>(static_cast<void *>(&argv0[0]))};
        QApplication a(argc, &argv[0]);
        if (chart_ == nullptr) {
            render();
        }
        if (chart_ != nullptr) {
            QPixmap p = chart_->grab();
            p.save(QString(image_path.c_str()));
        }
    }
    void SetTitle(const std::string &val) { title_ = val; }

    LineData2D *AddLine(std::error_code *ec = nullptr) {
        UNUSED(ec);
        auto line = std::make_shared<LineData2D>();
        lst_line_.push_back(line);
        return line.get();
    }
    Axis *AddAxis(std::error_code *ec = nullptr) {
        UNUSED(ec);
        auto axis = std::make_shared<Axis>();
        lst_axis_.push_back(axis);
        return axis.get();
    }
    void render() {
        auto *ch = new QtCharts::QChart();

        for (const auto &axis : lst_axis_) {
            switch (axis->position()) {
            case Axis::Position::Bottom:
            case Axis::Position::X: {
                setAxis(ch, axis.get(), Qt::AlignBottom);
                break;
            }
            case Axis::Position::Left:
            case Axis::Position::Y: {
                setAxis(ch, axis.get(), Qt::AlignLeft);
                break;
            }
            default:
                break;
            }
        }

        for (const auto &line : lst_line_) {
            auto *series = new QtCharts::QLineSeries();
            for (const auto &point : line->points()) {
                series->append(point.x(), point.y());
            }
            series->setName(QString(line->title().c_str()));
            ch->addSeries(series);

            auto lst_axis = ch->axes();
            for (const auto &axis : lst_axis) {
                series->attachAxis(axis);
            }
        }
        ch->legend()->setAlignment(Qt::AlignBottom);
        ch->setTitle(QString(title_.c_str()));

        if (chart_ != nullptr) {
            delete chart_;
            chart_ = nullptr;
        }
        chart_ = new QtCharts::QChartView(ch);
        chart_->setRenderHint(QPainter::Antialiasing);
    }
    void setAxis(QtCharts::QChart *ch, const Axis *axis, Qt::Alignment alignment) {
        if (axis->is_logarithm()) {
            auto *obj = new QtCharts::QLogValueAxis();
            obj->setTitleText(QString(axis->title().c_str()));
            obj->setMinorTickCount(axis->minor_tick_count());
            ch->addAxis(obj, alignment);
        } else {
            auto *obj = new QtCharts::QValueAxis();
            obj->setTitleText(QString(axis->title().c_str()));
            obj->setTickCount(axis->tick_count());
            obj->setMinorTickCount(axis->minor_tick_count());
            ch->addAxis(obj, alignment);
        }
    }
};

Line2D::Line2D() : impl_(std::unique_ptr<Line2DImpl>(new Line2DImpl)) {}
Line2D::Line2D(const Line2D &rhs) : stdgo::chart::Chart() {
    // copy constructor
    auto *impl = new Line2DImpl;
    *impl = *(rhs.impl_);
    impl_ = std::unique_ptr<Line2DImpl>(impl);
}
Line2D::Line2D(Line2D &&rhs) noexcept {
    // move constructor
    impl_ = std::move(rhs.impl_);
}
Line2D &Line2D::operator=(const Line2D &rhs) {
    // copy assigment
    auto *impl = new Line2DImpl;
    *impl = *(rhs.impl_);
    impl_ = std::unique_ptr<Line2DImpl>(impl);
    return *this;
}
Line2D &Line2D::operator=(Line2D &&rhs) noexcept {
    // move assigment
    impl_ = std::move(rhs.impl_);
    return *this;
}
void Line2D::Show(std::error_code *ec) { impl_->Show(ec); }
void Line2D::Save(const std::string &image_path, std::error_code *ec) { impl_->Save(image_path, ec); }
void Line2D::SetTitle(const std::string &val) { impl_->SetTitle(val); }

LineData2D *Line2D::AddLine(std::error_code *ec) { return impl_->AddLine(ec); }
Axis *Line2D::AddAxis(std::error_code *ec) { return impl_->AddAxis(ec); }

std::shared_ptr<Line2D> NewLine2D(std::error_code *ec) {
    UNUSED(ec);
    auto plot = std::make_shared<Line2D>();

    return plot;
}

} // namespace chart
} // namespace stdgo

#endif // STDGO_ENABLE_CHART_BACKEND_QT