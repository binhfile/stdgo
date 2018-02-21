#ifndef STDGO_PLOT_IPLOT_H
#define STDGO_PLOT_IPLOT_H
/**
 * @author binhfile
 * @brief Plotting and visualizing data
 */

#include <cstdint>
#include <memory>
#include <system_error>
#include <vector>

namespace stdgo {
namespace plot {
using LineId = uint64_t;
class Point {
  public:
    Point(float _x = 0, float _y = 0, float _z = 0) : x_(_x), y_(_y), z_(_z) {}
    virtual ~Point() = default;
    float x() const { return x_; }
    float y() const { return y_; }
    float z() const { return z_; }
    void set_x(float _x) { x_ = _x; }
    void set_y(float _y) { y_ = _y; }
    void set_z(float _z) { z_ = _z; }

  protected:
    float x_;
    float y_;
    float z_;
};
class IPlot {
  public:
    virtual ~IPlot() = default;
    virtual void Show(std::error_code *ec = nullptr) = 0;
    virtual void Save(const std::string &image_path, std::error_code *ec = nullptr) = 0;
    virtual LineId AddLine(const std::shared_ptr<std::vector<Point>> &line, std::error_code *ec = nullptr) = 0;
};

} // namespace plot
} // namespace stdgo

#endif // STDGO_PLOT_H