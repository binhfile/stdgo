#ifndef STDGO_CHART_COMMON_H
#define STDGO_CHART_COMMON_H
/**
 * @author binhfile
 * @brief Common defs
 */
#include <string>
#include <system_error>

namespace stdgo {
namespace chart {

class Point2D {
  public:
    explicit Point2D(float _x = 0, float _y = 0);
    Point2D(const Point2D &rhs) = default;
    Point2D(Point2D &&rhs) = default;
    Point2D &operator=(const Point2D &rhs) = default;
    Point2D &operator=(Point2D &&rhs) = default;
    virtual ~Point2D() = default;

    float x() const;
    float y() const;
    void set_x(float _x);
    void set_y(float _y);

  protected:
    float x_;
    float y_;
};

class Chart {
  public:
    Chart() = default;
    Chart(const Chart &rhs) = default;
    Chart(Chart &&rhs) = default;
    Chart &operator=(const Chart &rhs) = default;
    Chart &operator=(Chart &&rhs) = default;
    virtual ~Chart() = default;
    virtual void SetTitle(const std::string &val) = 0;

    virtual void Show(std::error_code *ec = nullptr) = 0;
    virtual void Save(const std::string &image_path,
                      std::error_code *ec = nullptr) = 0;
};

} // namespace chart
} // namespace stdgo

#endif // STDGO_PLOT_COMMON_H
