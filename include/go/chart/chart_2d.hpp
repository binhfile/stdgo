#ifndef GO_CHART_CHART_2D_H
#define GO_CHART_CHART_2D_H
/**
 * @author binhfile
 * @brief Plotting and visualizing data
 */

#include "common.hpp"
#include <memory>

namespace go {
namespace chart {

class Chart2DImpl;
class Chart2D : public go::chart::Chart {
  public:
    enum class Type {
        kLine = 0,
        kPolar,
    };
    Chart2D();
    Chart2D(const Chart2D &rhs);
    Chart2D(Chart2D &&rhs) noexcept;
    Chart2D &operator=(const Chart2D &rhs);
    Chart2D &operator=(Chart2D &&rhs) noexcept;
    virtual ~Chart2D();
    /* IPlot API */
    void Show(std::error_code *ec = nullptr) override;
    void Save(const std::string &image_path, std::size_t width = 0, std::size_t height = 0,
              std::error_code *ec = nullptr) override;
    void SetTitle(const std::string &val) override;
    /* Line API only */
    void SetType(Type _type);
    Type GetType() const;
    PointSeries2D *AddLine(std::error_code *ec = nullptr);
    Axis *AddAxis(std::error_code *ec = nullptr);

  protected:
    std::unique_ptr<Chart2DImpl> impl_;
};

} // namespace chart
} // namespace go

#endif // GO_CHART_CHART_2D_H
