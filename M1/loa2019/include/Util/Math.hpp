#ifndef UTIL_MATH_HPP_
#define UTIL_MATH_HPP_

struct Math {

    static long pow(long n, unsigned long exp)
    {
        if (exp == 0)
            return 1;
        if (exp == 1)
            return n;
        if (exp % 2 == 0)
            return pow(n, exp / 2) * pow(n, exp / 2);
        return pow(n, exp / 2) * pow(n, exp / 2) * n;
    }

}; // namespace Math

#endif // !UTIL_MATH_HPP_