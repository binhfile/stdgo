/**
 * @author binhfile
 * @brief Chart2D backend by QT
 */
#if defined(GO_HAS_CONFIG_H)
#include <go_config.hpp>
#endif

#if defined(GO_ENABLE_ALL) || defined(GO_ENABLE_CHART)
#if defined(GO_ENABLE_CHART_BACKEND_QT)
#include <go/chart/chart_2d.hpp>

#include <list>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

#ifndef UNUSED
#define UNUSED(x) (void)x
#endif

namespace go {
namespace chart {

class Chart2DImpl {
  private:
    std::list<std::shared_ptr<PointSeries2D>> lst_line_;
    std::list<std::shared_ptr<Axis>> lst_axis_;
    std::string title_;
    Chart2D::Type type_;
    QtCharts::QChartView *chart_;

  public:
    Chart2DImpl() : type_{Chart2D::Type::kLine}, chart_{nullptr} {}
    Chart2DImpl(const Chart2DImpl &rhs) : type_{Chart2D::Type::kLine}, chart_{nullptr} {
        // copy constructor
        for (const auto &src : rhs.lst_line_) {
            lst_line_.push_back(std::make_shared<PointSeries2D>(*src));
        }
        for (const auto &src : rhs.lst_axis_) {
            lst_axis_.push_back(std::make_shared<Axis>(*src));
        }
    }
    Chart2DImpl(Chart2DImpl &&rhs) noexcept : type_{Chart2D::Type::kLine}, chart_{nullptr} {
        // move constructor
        lst_line_ = std::move(rhs.lst_line_);
        lst_axis_ = std::move(rhs.lst_axis_);
    }
    Chart2DImpl &operator=(const Chart2DImpl &rhs) {
        // copy assigment
        for (const auto &src : rhs.lst_line_) {
            lst_line_.push_back(std::make_shared<PointSeries2D>(*src));
        }
        for (const auto &src : rhs.lst_axis_) {
            lst_axis_.push_back(std::make_shared<Axis>(*src));
        }
        return *this;
    }
    Chart2DImpl &operator=(Chart2DImpl &&rhs) noexcept {
        // move assigment
        this->lst_line_ = std::move(rhs.lst_line_);
        this->lst_axis_ = std::move(rhs.lst_axis_);
        return *this;
    }
    virtual ~Chart2DImpl() = default;
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
    void Save(const std::string &image_path, std::size_t width, std::size_t height,
              std::error_code *ec) {
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
            if (width == 0 || height == 0) {
                width = 1280;
                height = 720;
            }
            chart_->resize(width, height);
            QPixmap p = chart_->grab();
            p.save(QString(image_path.c_str()));
        }
    }
    void SetTitle(const std::string &val) { title_ = val; }

    PointSeries2D *AddLine(std::error_code *ec = nullptr) {
        UNUSED(ec);
        auto line = std::make_shared<PointSeries2D>();
        lst_line_.push_back(line);
        return line.get();
    }
    Axis *AddAxis(std::error_code *ec = nullptr) {
        UNUSED(ec);
        auto axis = std::make_shared<Axis>();
        lst_axis_.push_back(axis);
        return axis.get();
    }
    void SetType(Chart2D::Type _type) { type_ = _type; }
    Chart2D::Type GetType() const { return type_; }
    void render() {
        QtCharts::QChart *ch;
        switch (type_) {
        case Chart2D::Type::kPolar: {
            ch = new QtCharts::QPolarChart();
            break;
        }
        default:
            ch = new QtCharts::QChart();
            break;
        }

        for (const auto &axis : lst_axis_) {
            switch (axis->position()) {
            case Axis::Position::kBottom:
            case Axis::Position::kX: {
                setAxis(ch, axis.get(), Qt::AlignBottom);
                break;
            }
            case Axis::Position::kLeft:
            case Axis::Position::kY: {
                setAxis(ch, axis.get(), Qt::AlignLeft);
                break;
            }
            case Axis::Position::kAngular: {
                if (type_ == Chart2D::Type::kPolar) {
                    setAxis(static_cast<QtCharts::QPolarChart *>(static_cast<void *>(ch)),
                            axis.get(), QtCharts::QPolarChart::PolarOrientationAngular);
                }
                break;
            }
            case Axis::Position::kRadial: {
                if (type_ == Chart2D::Type::kPolar) {
                    setAxis(static_cast<QtCharts::QPolarChart *>(static_cast<void *>(ch)),
                            axis.get(), QtCharts::QPolarChart::PolarOrientationRadial);
                }
                break;
            }
            default:
                break;
            }
        }

        for (const auto &line : lst_line_) {
            QtCharts::QXYSeries *series = nullptr;
            switch (line->type()) {
            case PointSeries2D::Type::kLine: {
                series = new QtCharts::QLineSeries();
                break;
            }
            case PointSeries2D::Type::kSmooth: {
                series = new QtCharts::QSplineSeries();
                break;
            }
            default:
                series = new QtCharts::QScatterSeries();
                break;
            }
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
            if (axis->minimum() < axis->maximum()) {
                obj->setMin(axis->minimum());
                obj->setMax(axis->maximum());
            }
            ch->addAxis(obj, alignment);
        } else {
            auto *obj = new QtCharts::QValueAxis();
            obj->setTitleText(QString(axis->title().c_str()));
            obj->setTickCount(axis->tick_count());
            obj->setMinorTickCount(axis->minor_tick_count());
            if (axis->minimum() < axis->maximum()) {
                obj->setMin(axis->minimum());
                obj->setMax(axis->maximum());
            }
            ch->addAxis(obj, alignment);
        }
    }
    void setAxis(QtCharts::QPolarChart *ch, const Axis *axis,
                 QtCharts::QPolarChart::PolarOrientation alignment) {
        auto *obj = new QtCharts::QValueAxis();
        obj->setTitleText(QString(axis->title().c_str()));
        obj->setTickCount(axis->tick_count());
        obj->setMinorTickCount(axis->minor_tick_count());
        if (axis->minimum() < axis->maximum()) {
            obj->setMin(axis->minimum());
            obj->setMax(axis->maximum());
        }
        ch->addAxis(obj, alignment);
    }
};

Chart2D::Chart2D() : impl_(std::unique_ptr<Chart2DImpl>(new Chart2DImpl)) {}
Chart2D::Chart2D(const Chart2D &rhs) : go::chart::Chart() {
    // copy constructor
    auto *impl = new Chart2DImpl;
    *impl = *(rhs.impl_);
    impl_ = std::unique_ptr<Chart2DImpl>(impl);
}
Chart2D::Chart2D(Chart2D &&rhs) noexcept {
    // move constructor
    impl_ = std::move(rhs.impl_);
}
Chart2D &Chart2D::operator=(const Chart2D &rhs) {
    // copy assigment
    auto *impl = new Chart2DImpl;
    *impl = *(rhs.impl_);
    impl_ = std::unique_ptr<Chart2DImpl>(impl);
    return *this;
}
Chart2D &Chart2D::operator=(Chart2D &&rhs) noexcept {
    // move assigment
    impl_ = std::move(rhs.impl_);
    return *this;
}
Chart2D::~Chart2D() {}
void Chart2D::Show(std::error_code *ec) { impl_->Show(ec); }
void Chart2D::Save(const std::string &image_path, std::size_t width, std::size_t height,
                   std::error_code *ec) {
    impl_->Save(image_path, width, height, ec);
}
void Chart2D::SetTitle(const std::string &val) { impl_->SetTitle(val); }

void Chart2D::SetType(Type _type) { impl_->SetType(_type); }
Chart2D::Type Chart2D::GetType() const { return impl_->GetType(); }
PointSeries2D *Chart2D::AddLine(std::error_code *ec) { return impl_->AddLine(ec); }
Axis *Chart2D::AddAxis(std::error_code *ec) { return impl_->AddAxis(ec); }

} // namespace chart
} // namespace go

#endif // GO_ENABLE_CHART_BACKEND_QT
#endif // GO_ENABLE_CHART
