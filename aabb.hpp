#pragma once

#include "interval.hpp"

class aabb {
public:
	interval x, y, z;

	aabb() 
		: x(interval::empty)
		, y(interval::empty)
		, z(interval::empty) 
	{}

	aabb(const interval& ix, const interval& iy, const interval& iz)
		: x(ix)
		, y(iy)
		, z(iz)
	{}

	aabb(const point3& a, const point3& b) {
		//create AABB from two points
		x = interval(fmin(a[0], b[0]), fmax(a[0], b[0]));
		y = interval(fmin(a[1], b[1]), fmax(a[1], b[1]));
		z = interval(fmin(a[2], b[2]), fmax(a[2], b[2]));
	}

	aabb(const aabb& box0, const aabb& box1) {
		x = interval(box0.x, box1.x);
		y = interval(box0.y, box1.y);
		z = interval(box0.z, box1.z);
	}

	const interval& axis(int n) const {
		if (n == 1) {
			return y;
		} else if (n == 2) {
			return z;
		} else {
			return x;
		}
	}

	bool hit(const ray& r, interval& ray_t) const {
		for (int a = 0; a < 3; a++) {
			auto invD = 1.0 / r.direction()[a];
			auto origin = r.origin()[a];

			auto t0 = (axis(a).min - origin) * invD;
			auto t1 = (axis(a).max - origin) * invD;

			if (invD < 0.0) {
				std::swap(t0, t1);
			}
			if (t0 > ray_t.min) {
				ray_t.min = t0;
			}
			if (t1 < ray_t.max) {
				ray_t.max = t1;
			}
			if (ray_t.max <= ray_t.min) {
				return false;
			}
		}
		return true;
	}

	bool is_on_edge(const point3& p, double thickness) const {
		//check the distance between point and all 6 walls
		bool x_low = std::abs(p.x() - x.min) < thickness;
		bool x_high = std::abs(p.x() - x.max) < thickness;
		bool y_low = std::abs(p.y() - y.min) < thickness;
		bool y_high = std::abs(p.y() - y.max) < thickness;
		bool z_low = std::abs(p.z() - z.min) < thickness;
		bool z_high = std::abs(p.z() - z.max) < thickness;

		// point is on the edge if its close enough at least 2 planes
		int proximity_count = (x_low || x_high) + (y_low || y_high) + (z_low || z_high);

		//if we hit corner (3) or edge (2)
		if (proximity_count >= 2) return true;

		return false;
	}
};

//translate bounding box by offset vector
inline aabb operator+(const aabb& bbox, const vec3& offset) {
	return aabb(bbox.x + offset.x(), bbox.y + offset.y(), bbox.z + offset.z());
}

//vector + bounding box
inline aabb operator+(const vec3& offset, const aabb& bbox) {
	return bbox + offset;
}
