/**
 * @author binhfile
 * @brief Plot backend by QT
 */
#if defined(STDGO_HAS_CONFIG_H)
#include <stdgo_config.hpp>
#endif

#if (defined(STDGO_ENABLE_ALL) || defined(STDGO_ENABLE_PLOT)) && defined(STDGO_ENABLE_PLOT_BACKEND_QT)
#include "../include/stdgo/plot/line.hpp"

#include <list>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_CHARTS_USE_NAMESPACE

namespace stdgo {
namespace plot {
namespace line {

class PlotImpl {
  private:
    std::list<std::shared_ptr<Line>> lst_line_;
    std::list<std::shared_ptr<Axis>> lst_axis_;
    std::string title_;

  public:
    PlotImpl() {}
    virtual ~PlotImpl() {}
    void Show(std::error_code *ec) {
        char *argv[] = {"plot.qt"};
        int argc = 1;
        QApplication a(argc, argv);
        QChart *chart = new QChart();

        for (const auto &axis : lst_axis_) {
            switch (axis->position()) {
            case Axis::Position::X: {
                setAxis(chart, axis, Qt::AlignBottom);
                break;
            }
            case Axis::Position::Y: {
                setAxis(chart, axis, Qt::AlignLeft);
                break;
            }
            default:
                break;
            }
        }

        for (const auto &line : lst_line_) {
            QLineSeries *series = new QLineSeries();
            for (const auto &point : *(line->points())) {
                series->append(point.x() + 1, point.y() + 10);
            }
            series->setName(QString(line->title().c_str()));
            chart->addSeries(series);

            auto lst_axis = chart->axes();
            for (const auto &axis : lst_axis) {
                series->attachAxis(axis);
            }
        }
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setTitle(QString(title_.c_str()));

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QPixmap p = chartView->grab();
        p.save("output.png", "PNG");

        QMainWindow window;
        window.setCentralWidget(chartView);
        window.resize(400, 300);
        window.show();

        a.exec();
    }
    void Save(const std::string &image_path, std::error_code *ec) {}
    void SetTitle(const std::string &val) { title_ = val; }

    virtual void AddLine(const std::shared_ptr<Line> &line, std::error_code *ec = nullptr) { lst_line_.push_back(line); }
    virtual void AddAxis(const std::shared_ptr<Axis> &axis, std::error_code *ec = nullptr) { lst_axis_.push_back(axis); }

    void setAxis(QChart *chart, const std::shared_ptr<Axis> &axis, Qt::Alignment alignment) {
        if (axis->is_logarithm()) {
            auto obj = new QLogValueAxis();
            obj->setTitleText(QString(axis->title().c_str()));
            chart->addAxis(obj, alignment);
        } else {
            auto obj = new QValueAxis();
            obj->setTitleText(QString(axis->title().c_str()));
            chart->addAxis(obj, alignment);
        }
    }
};

Plot::Plot() : impl_(std::unique_ptr<PlotImpl>(new PlotImpl)) {}
Plot::~Plot() {}
void Plot::Show(std::error_code *ec) { impl_->Show(ec); }
void Plot::Save(const std::string &image_path, std::error_code *ec) { impl_->Save(image_path, ec); }
void Plot::SetTitle(const std::string &val) { impl_->SetTitle(val); }

void Plot::AddLine(const std::shared_ptr<Line> &line, std::error_code *ec) { impl_->AddLine(line, ec); }
void Plot::AddAxis(const std::shared_ptr<Axis> &axis, std::error_code *ec) { impl_->AddAxis(axis, ec); }

std::shared_ptr<Plot> New() {
    auto plot = std::make_shared<Plot>();

    return plot;
}

} // namespace line
} // namespace plot
} // namespace stdgo

#endif // STDGO_ENABLE_PLOT
