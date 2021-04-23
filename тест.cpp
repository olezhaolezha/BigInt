#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

class BigInt {

private:

    vector <int> a;
    int sign = 0;

    void cleaning () {
        if (a.size() != 0){
            while (a[a.size() - 1] == 0){
                a.pop_back ();
            }
        }
        if (a.size() == 0){
            sign = 0;
        }
    }

    BigInt plus (const BigInt& x, const BigInt& y) const{
        BigInt z;
        int delta = 0;
        for (int i = 0; i < max (x.a.size(), y.a.size()); ++ i) {
            if (i < x.a.size()){
                delta += x.a[i];
            }
            if (i < y.a.size()){
                delta += y.a[i];
            }
            z.a.push_back(delta%10);
            delta /= 10;
        }
        if (delta > 0){
            z.a.push_back(delta);
        }
        z.cleaning ();
        return z;
    }

    BigInt minus (const BigInt a, const BigInt b) const{
        BigInt z;
        BigInt x, y;
        if (a > b){
            y = a;
            x = b;
            z.sign = 1;
        }
        else {
            y = b;
            x = a;
            z.sign = -1;
        }
        int delta = 0;
        for (int i = 0; i < y.a.size(); ++ i){
            if (i < x.a.size()){
                if (y.a[i] - delta < x.a[i]){
                    z.a.push_back(y.a[i] + 10 - delta - x.a[i]);
                    delta = 1;
                }
                else {
                    z.a.push_back(y.a[i] - delta - x.a[i]);
                    delta = 0;
                }
            }
            else {
                if (y.a[i] - delta < 0){
                    z.a.push_back(y.a[i] + 10 - delta);
                    delta = 1;
                }
                else {
                    z.a.push_back(y.a[i] - delta);
                    delta = 0;
                }
            }
        }

        z.cleaning ();
        return z;
    }

    BigInt multiply (const BigInt x, const int y) const{
        BigInt z;
        if (x.sign == 0 || y == 0){
            return z;
        }
        z.sign = 1;
        int delta = 0;
        for (int i = 0; i < x.a.size(); ++ i) {
            z.a.push_back((x.a[i] * y + delta) % 10);
            delta = (x.a[i] * y + delta) / 10;
        }
        if (delta > 0){
            z.a.push_back(delta);
        }
        z.cleaning ();
        return z;
    }

    int divide (const BigInt x, BigInt y) const{
        BigInt templat(y);
        int k = 0;
        while (y <= x){
            y = y + templat;
            ++ k;
        }
        y = y - templat;
        -- k;
        y.cleaning();
        return k;
    }

    void add (int x) {
        a.push_back(1);
        for (int i = a.size() - 1; i >= 1; -- i){
            a[i] = a[i - 1];
        }
        a[0] = x;
    }

    BigInt ten (const BigInt x, int k) const{
        BigInt z;
        if (x.sign == 0){
            return z;
        }
        while (k--) {
            z.a.push_back(0);
        }
        z.sign = x.sign;
        for (int i = 0; i < x.a.size(); ++ i){
            z.a.push_back(x.a[i]);
        }
        z.cleaning();
        return z;
    }


public:

    BigInt () {
    }

    BigInt (const long long y) {
        a.resize(0);
        long long x = abs(y);
        if (y < 0){
            sign = -1;
        }
        if (y > 0){
            sign = 1;
        }
        while (x != 0){
            a.push_back(x%10);
            x -= x%10;
            x /= 10;
        }
        cleaning();
    }

    BigInt (const BigInt &copied){
        a.resize(0);
        a.resize(copied.a.size());
        for (int i = 0; i < copied.a.size (); ++ i){
            a[i] = copied.a[i];
        }
        sign = copied.sign;
        cleaning();
    }

    BigInt& operator= (const long long y){
        a.resize (0);
        long long x = abs(y);
        if (y < 0){
            sign = -1;
        }
        if (y > 0){
            sign = 1;
        }
        while (x != 0){
            a.push_back(x%10);
            x -= x%10;
            x /= 10;
        }
        cleaning();
        return (*this);
    }

    BigInt& operator= (const BigInt &copied){
        a.resize(0);
        a.resize(copied.a.size());
        for (int i = 0; i < copied.a.size (); ++ i){
            a[i] = copied.a[i];
        }
        sign = copied.sign;
        cleaning();
        return (*this);
    }

    bool operator== (const BigInt &other){
        if (a.size() != other.a.size()){
            return false;
        }
        if (sign != other.sign){
            return false;
        }
        for (int i = 0; i < a.size (); ++ i){
            if (a[i] != other.a[i]){
                return false;
            }
        }
        return true;
    }

    bool operator!= (const BigInt &other){
        if (a.size() != other.a.size()){
            return true;
        }
        if (sign != other.sign){
            return true;
        }
        for (int i = 0; i < a.size (); ++ i){
            if (a[i] != other.a[i]){
                return true;
            }
        }
        return false;
    }

    bool operator< (const BigInt &other) const{
        if (sign < other.sign){
            return true;
        }
        if (sign > other.sign){
            return false;
        }
        if (sign == 1){
            if (a.size() < other.a.size()){
                return true;
            }
            if (a.size() > other.a.size()){
                return false;
            }
            for (int i = a.size() - 1; i >= 0; -- i){
                if (a[i] < other.a[i]){
                    return true;
                }
                if (a[i] > other.a[i]){
                    return false;
                }
            }
        }
        if (sign == -1){
            if (a.size() < other.a.size()){
                return false;
            }
            if (a.size() > other.a.size()){
                return true;
            }
            for (int i = a.size() - 1; i >= 0; -- i){
                if (a[i] < other.a[i]){
                    return false;
                }
                if (a[i] > other.a[i]){
                    return true;
                }
            }
        }
        return false;
    }

    bool operator> (const BigInt &other) const{
        if (sign < other.sign){
            return false;
        }
        if (sign > other.sign){
            return true;
        }
        if (sign == 1){
            if (a.size() < other.a.size()){
                return false;
            }
            if (a.size() > other.a.size()){
                return true;
            }
            for (int i = a.size() - 1; i >= 0; -- i){
                if (a[i] < other.a[i]){
                    return false;
                }
                if (a[i] > other.a[i]){
                    return true;
                }
            }
        }
        if (sign == -1){
            if (a.size() < other.a.size()){
                return true;
            }
            if (a.size() > other.a.size()){
                return false;
            }
            for (int i = a.size() - 1; i >= 0; -- i){
                if (a[i] < other.a[i]){
                    return true;
                }
                if (a[i] > other.a[i]){
                    return false;
                }
            }
        }
        return false;
    }

    bool operator<= (const BigInt &other) {
        if (sign < other.sign){
            return true;
        }
        if (sign > other.sign){
            return false;
        }
        if (sign == 1){
            if (a.size() < other.a.size()){
                return true;
            }
            if (a.size() > other.a.size()){
                return false;
            }
            for (int i = a.size() - 1; i >= 0; -- i){
                if (a[i] < other.a[i]){
                    return true;
                }
                if (a[i] > other.a[i]){
                    return false;
                }
            }
        }
        if (sign == -1){
            if (a.size() < other.a.size()){
                return false;
            }
            if (a.size() > other.a.size()){
                return true;
            }
            for (int i = a.size() - 1; i >= 0; -- i){
                if (a[i] < other.a[i]){
                    return false;
                }
                if (a[i] > other.a[i]){
                    return true;
                }
            }
        }
        return true;
    }

    bool operator>= (const BigInt &other) const {
        if (sign < other.sign){
            return false;
        }
        if (sign > other.sign){
            return true;
        }
        if (sign == 1){
            if (a.size() < other.a.size()){
                return false;
            }
            if (a.size() > other.a.size()){
                return true;
            }
            for (int i = a.size() - 1; i >= 0; -- i){
                if (a[i] < other.a[i]){
                    return false;
                }
                if (a[i] > other.a[i]){
                    return true;
                }
            }
        }
        if (sign == -1){
            if (a.size() < other.a.size()){
                return true;
            }
            if (a.size() > other.a.size()){
                return false;
            }
            for (int i = a.size() - 1; i >= 0; -- i){
                if (a[i] < other.a[i]){
                    return true;
                }
                if (a[i] > other.a[i]){
                    return false;
                }
            }
        }
        return true;
    }

    friend ostream& operator<< (ostream& out, const BigInt& those);

    BigInt operator- () const {
        BigInt result(*this);
        result.sign *= -1;
        return result;
    }

    BigInt operator- (const BigInt &other) const {
        BigInt our(*this);
        BigInt a = our, b = other, result;
        a.sign = 1;
        b.sign = 1;
        a.cleaning();
        b.cleaning();
        int actual_sign = our.sign;
        if (our.sign == 0){
            actual_sign = 1;
        }
        if ((actual_sign == -1 && other.sign == 1) || (actual_sign == 1 && other.sign == -1)){
            result = plus(a, b);
            result.sign = actual_sign;
            result.cleaning();
            return result;
        }
        else {
            result = minus(a, b);
            result.sign = actual_sign * result.sign;
            result.cleaning();
            return result;
        }
    }

    BigInt operator+ (const BigInt &other) const{
        BigInt our(*this);
        BigInt a = our, b = other, result;
        a.sign = 1;
        b.sign = 1;
        a.cleaning();
        b.cleaning();
        int actual_sign = our.sign;
        if (our.sign == 0){
            actual_sign = 1;
        }
        if ((actual_sign == -1 && other.sign == 1) || (actual_sign == 1 && other.sign == -1)){
            result = minus(a, b);
            result.sign = actual_sign * result.sign;
            result.cleaning();
            return result;
        }
        else {
            result = plus(a, b);
            result.sign  = actual_sign;
            result.cleaning();
            return result;
        }
    }

    BigInt operator* (const BigInt &other) const {
        BigInt our(*this), those(other), result(0);
        if (our.sign == 0 || other.sign == 0){
            return result;
        }
        for (int i = 0; i < other.a.size(); ++ i){
            result = result + ten(multiply(our, those.a[i]), i);
        }
        result.sign = our.sign * other.sign;
        result.cleaning();
        return result;
    }
/*
    BigInt operator/ (const BigInt &other) const {
        BigInt delta(0), result;
        int i = a.size() - 1;
        while (i >= 0){
            delta.add(a[i]);
            BigInt fake(other);
            if (delta >= fake){
                result.add(divide(delta, fake));
                delta = delta - fake;
            }
            -- i;
        }
        result.cleaning();
        return result;
    }

    BigInt operator% (const BigInt &other) const {
        BigInt delta = 0, result;
        int i = a.size() - 1;
        while (i >= 0){
            delta.add(a[i]);
            BigInt fake(other);
            if (delta >= fake){
                result.add(divide(delta, fake));
                delta = delta - fake;
            }
            -- i;
        }
        delta.cleaning();
        return delta;
    }
*/
};


ostream& operator<< (ostream& out, const BigInt& those) {
    if (those.sign == 0){
        out << 0;
    }
    if (those.sign == -1){
        out << '-';
    }
    for (int i = those.a.size() - 1; i >= 0; -- i){
        out << those.a[i];
    }
    return out;
}

std::string toString(const BigInt& value)
{
    std::stringstream buf;
    buf << value;
    return buf.str();
}

void check(int64_t x, int64_t y)
{
    const BigInt bigX = x;
    const BigInt bigY = y;

    if (bigX + bigY != BigInt(x + y))
    {
        std::cout << x << " + " << y << " != " << x + y << " got " << bigX + bigY << '\n';
    }

    if (bigX - bigY != BigInt(x - y))
    {
        std::cout << x << " - " << y << " != " << x - y << " got " << bigX - bigY << '\n';
    }

    if (bigX * bigY != BigInt(x * y))
    {
        std::cout << x << " * " << y << " != " << x * y << " got " << bigX * bigY << '\n';
    }

    if (x != 0 && y != 0)
    {
        if (bigX / bigY != BigInt(x / y))
        {
            std::cout << x << " / " << y << " != " << x / y << " got " << bigX / bigY << '\n';
        }
        if (bigX % bigY != BigInt(x % y))
        {
            std::cout << x << " % " << y << " != " << x % y << " got " << bigX % bigY << '\n';
        }
    }
}

void doCheckEqual(const BigInt& actual, const char* expected, size_t line)
{
    const auto str = toString(actual);
    if (str != expected)
    {
        std::cout << "at line " << line << ": " << str << " != " << expected << '\n';
    }
}

#define checkEqual(x, y) do { doCheckEqual((x), (y), __LINE__); } while(0)
#define checkTrue(cond) do { if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; } while(0)

int main()
{

    BigInt x = 3;
    checkEqual(x, "3");
    BigInt y = x;
    checkEqual(y, "3");
    BigInt z;
    checkEqual(z, "0");

    checkEqual(BigInt(-10), "-10");

    checkTrue(x == y);
    checkTrue(y == x);
    checkTrue(x != z);
    checkTrue(z != x);

    z = y;
    checkEqual(z, "3");

    x = 100;
    checkEqual(x, "100");

    checkTrue(!(x < x));
    checkTrue(x < 200);
    checkTrue(BigInt(50) < x);
    checkTrue(BigInt(-500) < x);
    checkTrue(BigInt(-500) < BigInt(-200));

    checkTrue(!(x > x));
    checkTrue(BigInt(200) > x);
    checkTrue(x > BigInt(50));
    checkTrue(x > BigInt(-500));
    checkTrue(BigInt(-200) > BigInt(-500));

    checkTrue(x <= x);
    checkTrue(x <= 200);
    checkTrue(BigInt(50) <= x);
    checkTrue(BigInt(-500) <= x);
    checkTrue(BigInt(-500) <= BigInt(-200));

    checkTrue(x >= x);
    checkTrue(BigInt(200) >= x);
    checkTrue(x >= BigInt(50));
    checkTrue(x >= BigInt(-500));
    checkTrue(BigInt(-200) >= BigInt(-500));
    checkTrue(BigInt(0) == -BigInt(0));

    checkEqual(BigInt(10) + BigInt(10), "20");
    checkEqual(BigInt(-10) + BigInt(10), "0");
    checkEqual(BigInt(10) + BigInt(-10), "0");
    checkEqual(BigInt(-10) + BigInt(-10), "-20");

    checkEqual(BigInt(10) - BigInt(10), "0");
    checkEqual(BigInt(-10) - BigInt(10), "-20");
    checkEqual(BigInt(10) - BigInt(-10), "20");
    checkEqual(BigInt(-10) - BigInt(-10), "0");

    checkEqual(BigInt(0) + BigInt(-1), "-1");
    checkEqual(BigInt(0) - BigInt(1), "-1");

    checkEqual(BigInt(100) - BigInt(100), "0");
    checkEqual(BigInt(99) - BigInt(100), "-1");
    checkEqual(BigInt(10) - BigInt(11), "-1");
    checkEqual(BigInt(20) - BigInt(19), "1");

    for (int i = -21; i <= 21; ++i)
    {
        for (int j = -21; j <= 21; ++j)
        {
            check(i, j);
        }
    }

    cout << BigInt (100);

    const int64_t step = std::numeric_limits<uint32_t>::max() / 99;
    const int64_t lower = std::numeric_limits<int32_t>::min() + step;
    const int64_t upper = std::numeric_limits<int32_t>::max() - step;

    for (int64_t i = lower; i < upper; i += step)
    {
        for (int64_t j = -99; j < 99; ++j)
        {
            check(i, j);
       }
    }
    const BigInt big1 = std::numeric_limits<int64_t>::max();
    checkEqual(big1, "9223372036854775807");

    const BigInt big2 = big1 * big1;
    std::cout << "9223372036854775807 * 9223372036854775807\n";
    checkEqual(big2, "85070591730234615847396907784232501249");

    const BigInt big3 = big2 * big2;
    std::cout << "85070591730234615847396907784232501249 * 85070591730234615847396907784232501249\n";
    checkEqual(big3, "7237005577332262210834635695349653859421902880380109739573089701262786560001");

    std::cout << "done\n";

    return 0;
}
