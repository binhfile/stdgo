/**
 * @author binhfile
 * @brief Plot backend by QT
 */
#include "../include/stdgo/plot/qt.hpp"

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
namespace qt {

class PlotImpl {
  private:
    struct Line {
        std::shared_ptr<std::vector<Point>> points;
        LineId id;
    };
    std::list<struct Line> lst_line_;

  public:
    PlotImpl() {}
    virtual ~PlotImpl() {}
    void Show(std::error_code *ec) {
        char *argv[] = {"plot.qt"};
        int argc = 1;
        QApplication a(argc, argv);
        QChart *chart = new QChart();

        QLogValueAxis *axisX = new QLogValueAxis();
        axisX->setTitleText("Data point");
        // axisX->setLabelFormat("%i");
        // axisX->setTickCount(128);
        axisX->setMinorTickCount(-1);
        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Values");
        // axisY->setLabelFormat("%g");
        // axisY->setMinorTickCount(-1);
        // axisY->setTickCount(128);
        chart->addAxis(axisY, Qt::AlignLeft);

        for (const auto &line : lst_line_) {
            QLineSeries *series = new QLineSeries();
            for (const auto &point : *line.points) {
                series->append(point.x() + 1, point.y() + 10);
            }
            chart->addSeries(series);
            series->attachAxis(axisX);
            series->attachAxis(axisY);
        }
        chart->legend()->hide();
        // chart->createDefaultAxes();
        chart->setTitle("Simple line chart example");
        chart->axisX()->setTitleText("X");
        chart->axisY()->setTitleText("Y");

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
    LineId AddLine(const std::shared_ptr<std::vector<Point>> &line, std::error_code *ec) {
        struct Line _line;
        _line.points = line;
        lst_line_.push_back(_line);
        return _line.id;
    }
};

Plot::Plot() : impl_(std::unique_ptr<PlotImpl>(new PlotImpl)) {}
Plot::~Plot() {}
void Plot::Show(std::error_code *ec) { impl_->Show(ec); }
void Plot::Save(const std::string &image_path, std::error_code *ec) { impl_->Save(image_path, ec); }
LineId Plot::AddLine(const std::shared_ptr<std::vector<Point>> &line, std::error_code *ec) { return impl_->AddLine(line, ec); }

std::shared_ptr<Plot> New() {
    auto plot = std::make_shared<Plot>();

    return plot;
}
} // namespace qt
} // namespace plot
} // namespace stdgo
