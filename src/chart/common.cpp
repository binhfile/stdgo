/**
 * @author binhfile
 */
#include "../../include/stdgo/chart/common.hpp"

namespace stdgo {
namespace chart {

Point2D::Point2D(float _x, float _y) : x_(_x), y_(_y) {}
float Point2D::x() const { return x_; }
float Point2D::y() const { return y_; }
void Point2D::set_x(float _x) { x_ = _x; }
void Point2D::set_y(float _y) { y_ = _y; }

} // namespace chart
} // namespace stdgo
