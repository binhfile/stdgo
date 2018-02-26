/**
 * @author binhfile
 */
#include <go/chart/common.hpp>

namespace go {
namespace chart {

Point2D::Point2D(float _x, float _y) : x_(_x), y_(_y) {}
float Point2D::x() const { return x_; }
float Point2D::y() const { return y_; }
void Point2D::set_x(float _x) { x_ = _x; }
void Point2D::set_y(float _y) { y_ = _y; }
float Point2D::angle() const { return x_; }
float Point2D::radius() const { return y_; }
void Point2D::set_angle(float _x) { x_ = _x; }
void Point2D::set_radius(float _y) { y_ = _y; }

Point3D::Point3D(float _x, float _y, float _z) : Point2D(_x, _y), z_(_z) {}
float Point3D::z() const { return z_; }
void Point3D::set_z(float _z) { z_ = _z; }

} // namespace chart
} // namespace go
