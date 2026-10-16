#include "delynoi/utilities/poisson_sampler.h"

// width, height: bounding box
// r: required distance
// k: max attempts to find a candidate

std::vector<Point>
poisson_disk_sampling(double width, double height, double r, int k,
    unsigned int seed )
{
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> unit(0.0, 1.0);

    // Grid cell size: at most one point per cell.
    const double cellSize = r / std::sqrt(2.0);
    const int nx = static_cast<int>(std::ceil(width / cellSize));
    const int ny = static_cast<int>(std::ceil(height / cellSize));

    // Each grid cell stores a point index, or -1 if empty.
    std::vector<int> grid(nx * ny, -1);

    std::vector<Point> points;
    std::vector<int> active;

    auto cellIndex = [&](const Point& p) {
        int gx = std::min(static_cast<int>(p.getX() / cellSize), nx - 1);
        int gy = std::min(static_cast<int>(p.getY() / cellSize), ny - 1);
        return std::pair<int, int>{gx, gy};
    };

    auto isValid = [&](const Point& p) {
        if (p.getX() < 0 || p.getX() >= width ||
            p.getY() < 0 || p.getY() >= height)
            return false;

        auto [gx, gy] = cellIndex(p);

        // Check nearby grid cells.
        for (int i = std::max(0, gx - 2);
             i <= std::min(nx - 1, gx + 2); ++i) {
            for (int j = std::max(0, gy - 2);
                 j <= std::min(ny - 1, gy + 2); ++j) {

                int idx = grid[i * ny + j];
                if (idx == -1)
                    continue;

                const Point& q = points[idx];
                double dx = p.getX() - q.getX();
                double dy = p.getY() - q.getY();

                if (dx * dx + dy * dy < r * r)
                    return false;
            }
        }

        return true;
    };

    auto addPoint = [&](const Point& p) {
        int idx = static_cast<int>(points.size());
        points.push_back(p);
        active.push_back(idx);

        auto [gx, gy] = cellIndex(p);
        grid[gx * ny + gy] = idx;
    };

    // Start with one random point.
    addPoint({unit(rng) * width, unit(rng) * height});

    while (!active.empty()) {
        // Choose a random active point.
        std::uniform_int_distribution<int> pick(
            0, static_cast<int>(active.size()) - 1
        );
        int activePos = pick(rng);
        Point p = points[active[activePos]];

        bool found = false;

        for (int attempt = 0; attempt < k; ++attempt) {
            // Generate a random candidate in the annulus [r, 2r].
            double angle = unit(rng) * 2.0 * M_PI;
            double radius = r * std::sqrt(1.0 + 3.0 * unit(rng));

            Point candidate {
                p.getX() + radius * std::cos(angle),
                p.getY() + radius * std::sin(angle)
            };

            if (isValid(candidate)) {
                addPoint(candidate);
                found = true;
                break;
            }
        }

        // Retire this active point if no candidate succeeded.
        if (!found) {
            active[activePos] = active.back();
            active.pop_back();
        }
    }

    return points;
}
