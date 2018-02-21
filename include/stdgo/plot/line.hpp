#ifndef STDGO_PLOT_LINE_H
#define STDGO_PLOT_LINE_H
/**
 * @author binhfile
 * @brief Plotting and visualizing data
 */

#include "plot.hpp"
#include <memory>

namespace stdgo {
namespace plot {
namespace line {

class Line {
  public:
    Line(const std::shared_ptr<std::vector<Point>> &_points, const std::string &_title) : points_(_points), title_(_title) {}
    virtual ~Line() = default;
    void set_points(const std::shared_ptr<std::vector<Point>> &val) { points_ = val; }
    void set_title(const std::string &val) { title_ = val; }

    std::string title() const { return title_; }
    std::shared_ptr<std::vector<Point>> points() const { return points_; }

  protected:
    std::shared_ptr<std::vector<Point>> points_;
    std::string title_;
};
class Axis {
  public:
    enum class Position {
        X = 0,
        Y,
        Z,
    };
    Axis(Position _pos, const std::string &_title, bool _is_logarithm = false) : position_(_pos), title_(_title), is_logarithm_(_is_logarithm) {}
    virtual ~Axis() = default;
    void set_title(const std::string &val) { title_ = val; }
    void set_logarithm(bool val) { is_logarithm_ = val; }
    void set_position(Position pos) { position_ = pos; }

    std::string title() const { return title_; }
    bool is_logarithm() const { return is_logarithm_; }
    Position position() const { return position_; }

  protected:
    Position position_;
    std::string title_;
    bool is_logarithm_;
};

class PlotImpl;
class Plot : public IPlot {
  public:
    Plot();
    virtual ~Plot();
    /* IPlot API */
    virtual void Show(std::error_code *ec = nullptr) override;
    virtual void Save(const std::string &image_path, std::error_code *ec = nullptr) override;
    virtual void SetTitle(const std::string &val) override;
    /* Line API only */
    virtual void AddLine(const std::shared_ptr<Line> &line, std::error_code *ec = nullptr);
    virtual void AddAxis(const std::shared_ptr<Axis> &axis, std::error_code *ec = nullptr);

  protected:
    std::unique_ptr<PlotImpl> impl_;
};

std::shared_ptr<Plot> New();

} // namespace line
} // namespace plot
} // namespace stdgo

#endif // STDGO_PLOT_QT_H