#ifndef STDGO_CHART_LINE_H
#define STDGO_CHART_LINE_H
/**
 * @author binhfile
 * @brief Plotting and visualizing data
 */

#include "common.hpp"
#include <memory>
#include <vector>

namespace stdgo {
namespace chart {
namespace line {

class Line {
  public:
    Line() = default;
    Line(const Line &rhs) = default;
    Line(Line &&rhs) noexcept {
        this->points_ = std::move(rhs.points_);
        this->title_ = std::move(rhs.title_);
    }
    Line &operator=(const Line &rhs) = default;
    Line &operator=(Line &&rhs) noexcept {
        this->points_ = std::move(rhs.points_);
        this->title_ = std::move(rhs.title_);
        return *this;
    }
    virtual ~Line() = default;
    std::vector<Point2D> *mutable_points() { return &points_; }
    void set_title(const std::string &val) { title_ = val; }

    std::string title() const { return title_; }
    const std::vector<Point2D> &points() const { return points_; }

  protected:
    std::vector<Point2D> points_;
    std::string title_;
};
class Axis {
  public:
    enum class Position {
        Bottom = 0,
        Top,
        Left,
        Right,
    };
    Axis()
        : position_{Position::Bottom}, is_logarithm_{false}, tick_count_{1},
          minor_tick_count_{-1} {}
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

class ChartImpl;
class Chart : public stdgo::chart::Chart {
  public:
    Chart();
    Chart(const Chart &rhs);
    Chart(Chart &&rhs) noexcept;
    Chart &operator=(const Chart &rhs);
    Chart &operator=(Chart &&rhs) noexcept;
    virtual ~Chart() = default;
    /* IPlot API */
    void Show(std::error_code *ec = nullptr) override;
    void Save(const std::string &image_path,
              std::error_code *ec = nullptr) override;
    void SetTitle(const std::string &val) override;
    /* Line API only */
    Line *AddLine(std::error_code *ec = nullptr);
    Axis *AddAxis(std::error_code *ec = nullptr);

  protected:
    std::unique_ptr<ChartImpl> impl_;
};

std::shared_ptr<Chart> New(std::error_code *ec = nullptr);

} // namespace line
} // namespace chart
} // namespace stdgo

#endif // STDGO_CHART_LINE_H
