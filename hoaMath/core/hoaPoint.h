#pragma once
#include "hoaVector.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include <compare>
#include <span>
#include <format>
#include <concepts>

class __declspec(dllexport) hoaPoint {
public:
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	constexpr hoaPoint() = default;
	constexpr hoaPoint(double x, double y, double z) noexcept
		: x(x), y(y), z(z) {
	}
	constexpr hoaPoint(const hoaPoint&) = default;
	constexpr hoaPoint(hoaPoint&&) = default;
	explicit constexpr hoaPoint(const hoaVector& vec) noexcept
		: x(vec.x), y(vec.y), z(vec.z) {
	}
	explicit constexpr hoaPoint(std::span<const double, 3> data) noexcept
		: x(data[0]), y(data[1]), z(data[2]) {
	}
	constexpr hoaPoint& operator=(const hoaPoint&) = default;
	constexpr hoaPoint& operator=(hoaPoint&&) = default;

	constexpr operator hoaVector() const noexcept {
		return hoaVector(x, y, z);
	}
	constexpr auto operator<=>(const hoaPoint&) const = default;

	constexpr hoaPoint operator+(const hoaVector& vec) const noexcept {
		return hoaPoint(x + vec.x, y + vec.y, z + vec.z);
	}

	constexpr hoaPoint operator-(const hoaVector& vec) const noexcept {
		return hoaPoint(x - vec.x, y - vec.y, z - vec.z);
	}
	constexpr hoaVector operator-(const hoaPoint& other) const noexcept {
		return hoaVector(x - other.x, y - other.y, z - other.z);
	}
	constexpr hoaPoint& operator+=(const hoaVector& vec) noexcept {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	constexpr hoaPoint& operator-=(const hoaVector& vec) noexcept {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	constexpr hoaPoint operator*(double scalar) const noexcept {
		return hoaPoint(x * scalar, y * scalar, z * scalar);
	}

	constexpr hoaPoint operator/(double scalar) const {
		assert(scalar != 0.0 && "Division by zero!");
		return hoaPoint(x / scalar, y / scalar, z / scalar);
	}

	constexpr hoaPoint& operator*=(double scalar) noexcept {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	constexpr hoaPoint& operator/=(double scalar) {
		assert(scalar != 0.0 && "Division by zero!");
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	constexpr hoaVector vector_to(const hoaPoint& other) const noexcept {
		return hoaVector(other.x - x, other.y - y, other.z - z);
	}

	constexpr hoaVector vector_from(const hoaPoint& other) const noexcept {
		return hoaVector(x - other.x, y - other.y, z - other.z);
	}

	constexpr hoaPoint& move(const hoaVector& vec) noexcept {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	constexpr hoaPoint moved(const hoaVector& vec) const noexcept {
		return hoaPoint(x + vec.x, y + vec.y, z + vec.z);
	}

	double distance_to(const hoaPoint& other) const {
		return std::sqrt(distance_squared_to(other));
	}

	constexpr double distance_squared_to(const hoaPoint& other) const noexcept {
		double dx = x - other.x;
		double dy = y - other.y;
		double dz = z - other.z;
		return dx * dx + dy * dy + dz * dz;
	}

	double distance_from_origin() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	constexpr hoaPoint lerp_to(const hoaPoint& other, double t) const noexcept {
		return hoaPoint(
			x + (other.x - x) * t,
			y + (other.y - y) * t,
			z + (other.z - z) * t
		);
	}

	constexpr hoaPoint midpoint_with(const hoaPoint& other) const noexcept {
		return hoaPoint(
			(x + other.x) * 0.5,
			(y + other.y) * 0.5,
			(z + other.z) * 0.5
		);
	}

	constexpr std::span<double, 3> as_span() noexcept {
		return std::span<double, 3>(&x, 3);
	}

	constexpr std::span<const double, 3> as_span() const noexcept {
		return std::span<const double, 3>(&x, 3);
	}

	[[nodiscard]] constexpr double get_x() const noexcept { return x; }
	[[nodiscard]] constexpr double get_y() const noexcept { return y; }
	[[nodiscard]] constexpr double get_z() const noexcept { return z; }

	constexpr void set_x(double new_x) noexcept { x = new_x; }
	constexpr void set_y(double new_y) noexcept { y = new_y; }
	constexpr void set_z(double new_z) noexcept { z = new_z; }

	bool is_coincident_with(const hoaPoint& other, double epsilon = 1e-10) const noexcept {
		return std::abs(x - other.x) < epsilon &&
			std::abs(y - other.y) < epsilon &&
			std::abs(z - other.z) < epsilon;
	}

	bool is_origin(double epsilon = 1e-10) const noexcept {
		return std::abs(x) < epsilon &&
			std::abs(y) < epsilon &&
			std::abs(z) < epsilon;
	}

	constexpr hoaPoint projected_xy() const noexcept {
		return hoaPoint(x, y, 0.0);
	}

	constexpr hoaPoint projected_xz() const noexcept {
		return hoaPoint(x, 0.0, z);
	}

	constexpr hoaPoint projected_yz() const noexcept {
		return hoaPoint(0.0, y, z);
	}

	[[nodiscard]] constexpr const double* data() const noexcept {
		return &x;
	}

	[[nodiscard]] constexpr double* data() noexcept {
		return &x;
	}

	static const hoaPoint origin;
	static const hoaPoint invalid;
};

// Глобальные операторы
constexpr hoaPoint operator+(const hoaVector& vec, const hoaPoint& point) noexcept {
	return point + vec;
}

constexpr hoaPoint operator*(double scalar, const hoaPoint& point) noexcept {
	return point * scalar;
}
