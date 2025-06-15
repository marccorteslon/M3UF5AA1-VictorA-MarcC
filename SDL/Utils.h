#pragma once
#include <cmath>

class Vector2 {
public:
    float x;
    float y;

    Vector2() : x(0), y(0) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    float Magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2 Normalized() const {
        float mag = Magnitude();
        return mag == 0 ? Vector2(0, 0) : Vector2(x / mag, y / mag);
    }
};

class Vector2Int {
public:
    int x;
    int y;

    Vector2Int() : x(0), y(0) {}
    Vector2Int(int _x, int _y) : x(_x), y(_y) {}

    Vector2Int operator+(const Vector2Int& other) const {
        return Vector2Int(x + other.x, y + other.y);
    }
};
