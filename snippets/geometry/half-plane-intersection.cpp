#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>

struct HalfPlanePoint {
  long double x;
  long double y;

  HalfPlanePoint operator+(const HalfPlanePoint& other) const {
    return {x + other.x, y + other.y};
  }

  HalfPlanePoint operator-(const HalfPlanePoint& other) const {
    return {x - other.x, y - other.y};
  }

  HalfPlanePoint operator*(long double factor) const { return {x * factor, y * factor}; }
};

long double cross(const HalfPlanePoint& first, const HalfPlanePoint& second) {
  return first.x * second.y - first.y * second.x;
}

struct HalfPlane {
  HalfPlanePoint point;
  HalfPlanePoint direction;

  long double angle() const { return std::atan2(direction.y, direction.x); }

  bool excludes(const HalfPlanePoint& candidate, long double epsilon = 1e-12L) const {
    return cross(direction, candidate - point) < -epsilon;
  }
};

HalfPlanePoint intersection(const HalfPlane& first, const HalfPlane& second) {
  const long double scale =
      cross(second.point - first.point, second.direction) /
      cross(first.direction, second.direction);
  return first.point + first.direction * scale;
}

std::vector<HalfPlanePoint> half_plane_intersection(std::vector<HalfPlane> planes) {
  std::sort(planes.begin(), planes.end(), [](const HalfPlane& first,
                                             const HalfPlane& second) {
    return first.angle() < second.angle();
  });
  std::deque<HalfPlane> active;
  for (const HalfPlane& plane : planes) {
    while (active.size() > 1 &&
           plane.excludes(intersection(active[active.size() - 2], active.back()))) {
      active.pop_back();
    }
    while (active.size() > 1 && plane.excludes(intersection(active[0], active[1]))) {
      active.pop_front();
    }
    if (!active.empty() && std::fabs(cross(active.back().direction, plane.direction)) <= 1e-12L) {
      if (plane.excludes(active.back().point)) {
        active.back() = plane;
      }
      continue;
    }
    active.push_back(plane);
  }
  while (active.size() > 2 &&
         active.front().excludes(intersection(active[active.size() - 2], active.back()))) {
    active.pop_back();
  }
  while (active.size() > 2 &&
         active.back().excludes(intersection(active[0], active[1]))) {
    active.pop_front();
  }
  if (active.size() < 3) {
    return {};
  }
  std::vector<HalfPlanePoint> polygon;
  for (int index = 0; index < static_cast<int>(active.size()); ++index) {
    polygon.push_back(intersection(active[index], active[(index + 1) % active.size()]));
  }
  return polygon;
}
