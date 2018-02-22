#ifndef STDGO_CHART_COMMON_H
#define STDGO_CHART_COMMON_H
/**
 * @author binhfile
 * @brief Common defs
 */
#include <string>
#include <system_error>
#include <vector>

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

template <typename Point>
class LineData {
  public:
    LineData() = default;
    LineData(const LineData &rhs) = default;
    LineData(LineData &&rhs) noexcept {
        this->points_ = std::move(rhs.points_);
        this->title_ = std::move(rhs.title_);
    }
    LineData &operator=(const LineData &rhs) = default;
    LineData &operator=(LineData &&rhs) noexcept {
        this->points_ = std::move(rhs.points_);
        this->title_ = std::move(rhs.title_);
        return *this;
    }
    virtual ~LineData() = default;
    std::vector<Point> *mutable_points() { return &points_; }
    void set_title(const std::string &val) { title_ = val; }

    std::string title() const { return title_; }
    const std::vector<Point2D> &points() const { return points_; }

  protected:
    std::vector<Point> points_;
    std::string title_;
};
using LineData2D = LineData<Point2D>;

class Axis {
  public:
    enum class Position {
        Bottom = 0,
        Top,
        Left,
        Right,
        X,
        Y,
        Z,
        Angular,
        Radial,
    };
    Axis() : position_{Position::Bottom}, is_logarithm_{false}, tick_count_{1}, minor_tick_count_{-1} {}
    Axis(const Axis &rhs) = default;
    Axis(Axis &&rhs) = default;
    Axis &operator=(const Axis &rhs) = default;
    Axis &operator=(Axis &&rhs) = default;
    virtual ~Axis() = default;
    void set_title(const std::string &val) { title_ = val; }
    void set_logarithm(bool val) { is_logarithm_ = val; }
    void set_position(Position pos) { position_ = pos; }
    void set_tick_count(int val) { tick_count_ = val; }
    void set_minor_tick_count(int val) { minor_tick_count_ = val; }

    std::string title() const { return title_; }
    bool is_logarithm() const { return is_logarithm_; }
    Position position() const { return position_; }
    int tick_count() const { return tick_count_; }
    int minor_tick_count() const { return minor_tick_count_; }

  protected:
    Position position_;
    std::string title_;
    bool is_logarithm_;
    int tick_count_;
    int minor_tick_count_;
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
    virtual void Save(const std::string &image_path, std::error_code *ec = nullptr) = 0;
};

} // namespace chart
} // namespace stdgo

#endif // STDGO_PLOT_COMMON_H
