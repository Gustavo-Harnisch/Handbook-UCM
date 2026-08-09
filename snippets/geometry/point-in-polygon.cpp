#include <cmath>
#include <vector>

struct RealPoint {
  long double x;
  long double y;
};

enum class PointLocation { kOutside, kBoundary, kInside };

long double cross(const RealPoint& first, const RealPoint& second,
                  const RealPoint& third) {
  return (second.x - first.x) * (third.y - first.y) -
         (second.y - first.y) * (third.x - first.x);
}

bool on_segment(const RealPoint& first, const RealPoint& second,
                const RealPoint& point, long double epsilon = 1e-12L) {
  return std::fabs(cross(first, second, point)) <= epsilon &&
         point.x >= std::min(first.x, second.x) - epsilon &&
         point.x <= std::max(first.x, second.x) + epsilon &&
         point.y >= std::min(first.y, second.y) - epsilon &&
         point.y <= std::max(first.y, second.y) + epsilon;
}

PointLocation point_in_polygon(const std::vector<RealPoint>& polygon,
                               const RealPoint& point) {
  bool inside = false;
  for (int current = 0, previous = static_cast<int>(polygon.size()) - 1;
       current < static_cast<int>(polygon.size()); previous = current++) {
    const RealPoint& first = polygon[previous];
    const RealPoint& second = polygon[current];
    if (on_segment(first, second, point)) {
      return PointLocation::kBoundary;
    }
    const bool crosses_horizontal_ray = (first.y > point.y) != (second.y > point.y);
    if (crosses_horizontal_ray &&
        point.x < (second.x - first.x) * (point.y - first.y) /
                      (second.y - first.y) + first.x) {
      inside = !inside;
    }
  }
  return inside ? PointLocation::kInside : PointLocation::kOutside;
}
