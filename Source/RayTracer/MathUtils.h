#pragma once

class MathUtils
{
public:
    template <typename T>
    static T lerp(const T& a, const T& b, float t) {
        return a + t * (b - a);
    }
};