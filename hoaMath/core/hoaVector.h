#pragma once

#include <cmath>
#include <cassert>
#include <iostream>
#include <compare>
#include <span>
#include <concepts>
#include <format>
#include <algorithm>
#include "hoaMathExport.h"

class HOA_MATH_API hoaVector {
public:
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	constexpr hoaVector() = default;
	constexpr hoaVector(double x, double y, double z) noexcept
		: x(x), y(y), z(z) {
	}
	constexpr hoaVector(const hoaVector&) = default;
	constexpr hoaVector(hoaVector&&) = default;
	explicit constexpr hoaVector(std::span<const double, 3> data) noexcept
		: x(data[0]), y(data[1]), z(data[2]) {
	}
	constexpr hoaVector& operator=(const hoaVector&) = default;
	constexpr hoaVector& operator=(hoaVector&&) = default;
	constexpr auto operator<=>(const hoaVector&) const = default;

	constexpr hoaVector operator+(const hoaVector& other) const noexcept {
		return hoaVector(x + other.x, y + other.y, z + other.z);
	}
	constexpr hoaVector operator-(const hoaVector& other) const noexcept {
		return hoaVector(x - other.x, y - other.y, z - other.z);
	}
	constexpr hoaVector operator*(double scalar) const noexcept {
		return hoaVector(x * scalar, y * scalar, z * scalar);
	}
	constexpr hoaVector operator/(double scalar) const {
		assert(scalar != 0.0 && "Division by zero!");
		return hoaVector(x / scalar, y / scalar, z / scalar);
	}
	constexpr hoaVector& operator+=(const hoaVector& other) noexcept {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	constexpr hoaVector& operator-=(const hoaVector& other) noexcept {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	constexpr hoaVector& operator*=(double scalar) noexcept {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	constexpr hoaVector& operator/=(double scalar) {
		assert(scalar != 0.0 && "Division by zero!");
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	constexpr hoaVector operator+() const noexcept {
		return *this;
	}
	constexpr hoaVector operator-() const noexcept {
		return hoaVector(-x, -y, -z);
	}

	constexpr std::span<double, 3> as_span() noexcept {
		return std::span<double, 3>(&x, 3);
	}
	constexpr std::span<const double, 3> as_span() const noexcept {
		return std::span<const double, 3>(&x, 3);
	}

	double length() const {
		return std::sqrt(lengthSquared());
	}
	constexpr double lengthSquared() const noexcept {
		return x * x + y * y + z * z;
	}
	hoaVector& normalize() {
		if (auto len = length(); len > 0.0) [[likely]] {
			*this /= len;
		}
		return *this;
	}
	hoaVector normalized() const {
		hoaVector result = *this;
		return result.normalize();
	}

	bool is_zero(double epsilon = 1e-10) const noexcept {
		return std::abs(x) < epsilon &&
			std::abs(y) < epsilon &&
			std::abs(z) < epsilon;
	}
	bool is_normalized(double epsilon = 1e-10) const noexcept {
		return std::abs(lengthSquared() - 1.0) < epsilon;
	}

	constexpr double dot(const hoaVector& v) noexcept {
		return x * v.x + y * v.y + z * v.z;
	}

	constexpr hoaVector cross(const hoaVector& v) noexcept {
		return {y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x};
	}

	double distance(const hoaVector& v) {
		return (*this - v).length();
	}

	constexpr double distanceSquared(const hoaVector& v) noexcept {
		return (*this - v).lengthSquared();
	}

	double angle(const hoaVector& v) {
		if (auto lenProduct = length() * v.length(); lenProduct > 0.0) [[likely]] {
			double cosAngle = dot(v) / lenProduct;
			cosAngle = std::clamp(cosAngle, -1.0, 1.0);
			return std::acos(cosAngle);
		}
		return 0.0;
	}

	constexpr hoaVector project(const hoaVector& v) noexcept {
		if (auto lenSq = v.lengthSquared(); lenSq > 0.0) [[likely]] {
			return v * (dot(v) / lenSq);
		}
		return hoaVector::zero;
	}

	constexpr hoaVector reject(const hoaVector& v) noexcept {
		return *this - project(v);
	}

	constexpr hoaVector reflect(const hoaVector& n) noexcept {
		return *this - n * (2.0 * dot(n));
	}

	constexpr hoaVector lerp(const hoaVector& v, double t) noexcept {
		return *this + (v - *this) * t;
	}

	static const hoaVector zero;
	static const hoaVector one;
	static const hoaVector unitX;
	static const hoaVector unitY;
	static const hoaVector unitZ;

	[[nodiscard]] constexpr const double* data() const noexcept {
		return &x;
	}

	[[nodiscard]] constexpr double* data() noexcept {
		return &x;
	}
};

constexpr hoaVector operator*(double scalar, const hoaVector& v) noexcept {
	return v * scalar;
}
