#include <algorithm>
#include <vector>

struct IntegerPoint {
  long long x;
  long long y;

  bool operator<(const IntegerPoint& other) const {
    return x != other.x ? x < other.x : y < other.y;
  }

  bool operator==(const IntegerPoint& other) const {
    return x == other.x && y == other.y;
  }
};

long long cross(const IntegerPoint& origin, const IntegerPoint& first,
                const IntegerPoint& second) {
  return (first.x - origin.x) * (second.y - origin.y) -
         (first.y - origin.y) * (second.x - origin.x);
}

std::vector<IntegerPoint> convex_hull(std::vector<IntegerPoint> points) {
  std::sort(points.begin(), points.end());
  points.erase(std::unique(points.begin(), points.end()), points.end());
  if (points.size() <= 2) {
    return points;
  }
  std::vector<IntegerPoint> hull;
  for (const IntegerPoint& point : points) {
    while (hull.size() >= 2 &&
           cross(hull[hull.size() - 2], hull.back(), point) <= 0) {
      hull.pop_back();
    }
    hull.push_back(point);
  }
  const std::size_t lower_size = hull.size();
  for (int index = static_cast<int>(points.size()) - 2; index >= 0; --index) {
    while (hull.size() > lower_size &&
           cross(hull[hull.size() - 2], hull.back(), points[index]) <= 0) {
      hull.pop_back();
    }
    hull.push_back(points[index]);
  }
  hull.pop_back();
  return hull;
}
