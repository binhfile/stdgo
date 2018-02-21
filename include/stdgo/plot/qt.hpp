#ifndef STDGO_PLOT_QT_H
#define STDGO_PLOT_QT_H
/**
 * @author binhfile
 * @brief Plotting and visualizing data with QT backend
 */

#include "iplot.hpp"
#include <memory>

namespace stdgo {
namespace plot {
namespace qt {

class PlotImpl;
class Plot : public IPlot {
  public:
    Plot();
    virtual ~Plot();
    virtual void Show(std::error_code *ec = nullptr);
    virtual void Save(const std::string &image_path, std::error_code *ec = nullptr);
    virtual LineId AddLine(const std::shared_ptr<std::vector<Point>> &line, std::error_code *ec = nullptr);

  protected:
    std::unique_ptr<PlotImpl> impl_;
};

std::shared_ptr<Plot> New();
} // namespace qt
} // namespace plot
} // namespace stdgo

#endif // STDGO_PLOT_QT_H