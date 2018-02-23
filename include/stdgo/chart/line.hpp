#ifndef STDGO_CHART_LINE_H
#define STDGO_CHART_LINE_H
/**
 * @author binhfile
 * @brief Plotting and visualizing data
 */

#include "common.hpp"
#include <memory>

namespace stdgo {
namespace chart {

class Line2DImpl;
class Line2D : public stdgo::chart::Chart {
  public:
    Line2D();
    Line2D(const Line2D &rhs);
    Line2D(Line2D &&rhs) noexcept;
    Line2D &operator=(const Line2D &rhs);
    Line2D &operator=(Line2D &&rhs) noexcept;
    virtual ~Line2D() = default;
    /* IPlot API */
    void Show(std::error_code *ec = nullptr) override;
    void Save(const std::string &image_path, std::error_code *ec = nullptr) override;
    void SetTitle(const std::string &val) override;
    /* Line API only */
    PointSeries2D *AddLine(std::error_code *ec = nullptr);
    Axis *AddAxis(std::error_code *ec = nullptr);

  protected:
    std::unique_ptr<Line2DImpl> impl_;
};

std::shared_ptr<Line2D> NewLine2D(std::error_code *ec = nullptr);

} // namespace chart
} // namespace stdgo

#endif // STDGO_CHART_LINE_H
