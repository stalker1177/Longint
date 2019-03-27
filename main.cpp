#include <iostream>
#include <vector>
#include <math.h>
#include <functional>

using namespace std;

class Longint {
private:

    vector<int> num;
    bool sign;    // true - minus, false - plus

    Longint subtraction(Longint a, const Longint &b) {
        Longint c;
        int size;
        if (abs(a) == abs(b)) {
            c = 0;
            return c;
        }
        if (a.num.size() < b.num.size())
            size = a.num.size();
        else
            size = b.num.size();
        for (int i = 0; i < size; i++) {
            if (a.num[i] < b.num[i]) {
                c.num.push_back(a.num[i] + 10 - b.num[i]);
                a.num[i + 1] -= 1;
            } else {
                c.num.push_back(a.num[i] - b.num[i]);
            }
        }
        if (a.num.size() != b.num.size()) {
            for (int i = b.num.size(); i < a.num.size(); i++)
                c.num.push_back(a.num[i]);
        }
        for (int i = c.num.size() - 1; i >= 0; i--) {
            if (c.num[i] == 0)
                c.num.erase(c.num.begin() + i);
            else
                break;
        }
        return c;
    }

    Longint sum(Longint a, Longint b) {
        Longint c;
        bool one = false;

        if (a.num.size() <= b.num.size()) {
            for (int i = 0; i < a.num.size(); i++) {
                if (c.num.size() > i) {
                    if (a.num[i] + b.num[i] + c.num[i] >= 10) {
                        c.num[i] = (a.num[i] + b.num[i] + c.num[i]) % 10;
                        c.num.push_back(1);
                    } else {
                        c.num[i] += (a.num[i] + b.num[i]);
                    }
                } else {
                    if (a.num[i] + b.num[i] >= 10) {
                        c.num.push_back((a.num[i] + b.num[i]) % 10);
                        c.num.push_back(1);
                    } else
                        c.num.push_back((a.num[i] + b.num[i]));
                }
            }
            for (int i = a.num.size(); i < b.num.size(); i++) {
                if (c.num.size() > i) {
                    if ((c.num[i] + b.num[i]) >= 10) {
                        c.num[i] = (c.num[i] + b.num[i]) % 10;
                        c.num.push_back(1);
                    } else
                        c.num[i] += b.num[i];

                } else {
                    c.num.push_back(b.num[i]);
                }
            }
        } else {
            c = sum(b, a);
        }

        return c;
    }

    Longint addition(Longint a, Longint b) {
        Longint res;
        if (a.sign == b.sign) {
            res = sum(a, b);
            res.sign = a.sign;
        } else {
            if (abs(a) == abs(b)) {
                res = 0;
                return res;
            }
            if (a.sign) {
                res = subtraction(a, b);
                res.sign = abs(a) > abs(b) != 0;

            } else {
                res = subtraction(b, a);
                res.sign = abs(a) > abs(b) == 0;

            }
        }

        return res;
    }

    Longint sub(const Longint &a, const Longint &b) {
        Longint c;
        if (a == b) {
            c.num.push_back(0);
            return c;
        }
        if (a > b) {
            if (a.sign && !b.sign) {
                c = sum(a, b);
                c.sign = true;
                return c;
            }
            if (!a.sign && b.sign) {
                c = sum(a, b);
                return c;
            }
            if (!a.sign && !b.sign) {
                c = subtraction(a, b);
                return c;
            }
            if (a.sign && b.sign) {
                c = subtraction(b, a);
                return c;
            }
        } else {
            c = sub(b, a);
            c.sign = true;
            return c;
        }


        return c;
    }

    void push_front(const int &in) {
        num.insert(num.begin(), in);
    }

    Longint multi0(Longint &a) {
        a = 0;
        return a;
    }

    Longint multi1(Longint &a) {
        return a;
    }

    Longint multi2(Longint &a) {
        return a + a;
    }

    Longint multi3(Longint &a) {
        return a + a + a;
    }

    Longint multi4(Longint &a) {
        a = multi2(a);
        return a + a;
    }

    Longint multi5(Longint &a) {
        return multi3(a) + multi2(a);
    }

    Longint multi6(Longint &a) {
        a = multi3(a);
        return a + a;
    }

    Longint multi7(Longint &a) {
        return multi5(a) + multi2(a);
    }

    Longint multi8(Longint &a) {
        a = multi4(a);
        return a + a;
    }

    Longint multi9(Longint &a) {
        a = multi3(a);
        return a + a + a;
    }

    Longint multi(Longint a, int m, int nulls = 0) {
        Longint(Longint::*
        mult[10])(Longint &) =
                         {&Longint::multi0, &Longint::multi1, &Longint::multi2, &Longint::multi3, &Longint::multi4,
                          &Longint::multi5, &Longint::multi6, &Longint::multi7, &Longint::multi8, &Longint::multi9};
        if (nulls != 0) {
            Longint b;
            for (int i = 0; i < nulls; i++)
                b.num.push_back(0);
            for (int i : a.num)
                b.num.push_back(i);
            b.sign = a.sign;
            return (this->*mult[m])(b);
        }
        return (this->*mult[m])(a);
    }

    void vednull(Longint &a) {
        int i = a.num.size() - 1;
        while (i != 0) {
            if (a.num[i] == 0)
                a.num.erase(a.num.begin() + (i--));
            else
                break;

        }

    }

    Longint multiplication(const Longint &a, const Longint &b) {
        Longint res = 0;
        if (abs(a) >= abs(b)) {
            for (int i = 0; i < b.num.size(); i++) {
                res = res + abs(multi(a, b.num[i], i));
            }
        } else {
            return multiplication(b, a);
        }
        res.sign = a.sign != b.sign;
        return res;
    }

    Longint multiplication(const Longint &a, const int &in) {
        Longint b(in);
        return multiplication(a, b);
    }

    Longint division(Longint a, Longint b, bool ostatok = false) {
        Longint res;
        res.sign = a.sign != b.sign;
        if (abs(a) >= abs(b)) {
            if (b == 0) {
                return -1;
            }
            Longint partup, partd(abs(b));
            int i = 1;
            do {
                partup.push_front(a.num[a.num.size() - (i++)]);
            } while (partup < partd);

            do {
                int del = 0;

                do {
                    partd = abs(b) * (++del);
                } while (partup >= partd);

                res.push_front(--del);
                partup = partup - (abs(b) * (del));

                do {
                    if (i <= a.num.size()) {
                        partup.push_front(a.num[a.num.size() - (i++)]);
                        vednull(partup);
                        if (partup < abs(b))
                            res.push_front(0);
                    } else {
                        if (ostatok) {
                            return partup;
                        }
                        break;
                    }
                } while (partup < abs(b));

            } while (partup > abs(b));


        } else {
            if (ostatok)
                return b-a;
            return res = 0;
        }

        return res;
    }

public:
    vector<int> get() { return num; }

    Longint() { sign = false; }

    Longint(const string &a) {
        num.clear();
        sign = a[0] == '-';
        for (int i = a.length() - 1; i >= sign; i--) {
            num.push_back((a[i] - 48));
        }
    }

    Longint(const Longint &a) {
        num = a.num;
        sign = a.sign;
    }

    Longint(int a) {
        num.clear();
        if (a < 0) {
            sign = true;
            a = -a;
        } else {
            sign = false;
        }
        do {
            this->num.push_back(a % 10);
            a /= 10;
        } while (a > 0);
    }

    bool isneg() { return sign; }

    Longint abs(const Longint &a) {
        Longint b = a;
        b.sign = false;
        return b;
    }

    Longint &operator=(int a) {
        num.clear();
        if (a == 0) {
            num.push_back(0);
            return *this;
        }
        if (a < 0) {
            sign = true;
            a = -a;
        }
        while (a > 0) {
            this->num.push_back(a % 10);
            a /= 10;
        }
        return *this;
    }

    Longint &operator=(string a) {
        num.clear();
        if (a[0] == '-') {
            sign = true;
        }
        for (int i = a.length() - 1; i >= sign; i--) {
            num.push_back((a[i] - 48));
        }
        return *this;
    }

    Longint &operator=(const Longint &a) {
        if (&a == this)
            return *this;
        num = a.num;
        sign = a.sign;
        return *this;
    }

    Longint &operator-() {
        if (num.size() != 1 && num[0] != 0)
            sign = !sign;
        return *this;
    }

    Longint &operator+() {
        return *this;
    }

    friend const bool operator<(const Longint &a, const Longint &b) {
        if (a.sign && !b.sign)
            return true;
        else if (!a.sign && b.sign)
            return false;
        else if (a.sign && b.sign) {
            if (a.num.size() > b.num.size())
                return true;
            else if (a.num.size() < b.num.size())
                return false;
            else {
                for (int i = a.num.size() - 1; i >= 0; i--) {
                    if (b.num[i] != a.num[i])
                        return a.num[i] > b.num[i];
                }
            }
        }
        if (a.num.size() < b.num.size())
            return true;
        else if (a.num.size() > b.num.size())
            return false;
        else {
            for (int i = a.num.size() - 1; i >= 0; i--) {
                if (b.num[i] != a.num[i])
                    return a.num[i] < b.num[i];
            }
        }
        return false;
    }

    friend const bool operator<(const int &a, const Longint &b) {
        Longint al(a);
        return al < b;
    }

    friend const bool operator>(const Longint &a, const Longint &b) {
        return b < a;
    }

    friend const bool operator==(const Longint &a, const Longint &b) {
        return !(a > b || a < b);
    }

    friend const bool operator<=(const Longint &a, const Longint &b) {
        return (a < b || a == b);
    }

    friend const bool operator>=(const Longint &a, const Longint &b) {
        return (a > b || a == b);
    }

    Longint operator+(const Longint &a) {
        return *this = addition(*this, a);
    }

    Longint operator+(const int &a) {
        Longint b(a);
        return *this = addition(*this, b);
    }

    Longint operator-(const Longint &a) {
        return sub(*this, a);
    }

    Longint operator*(const Longint &a) {
        return multiplication(*this, a);
    }

    Longint operator*(const int &a) {
        return multiplication(*this, a);
    }

    Longint operator/(const Longint &a) {
        return division(*this, a, false);
    }

    Longint operator%(const Longint &a) {
        return division(*this, a, true);
    }

    Longint operator*=(const Longint &a) {
        return *this=*this * a;
    }

    Longint operator+=(const Longint &a) {
        return *this=*this + a;
    }

    Longint operator/=(const Longint &a) {
        return *this=*this/a;
    }

    Longint operator-=(const Longint &a) {
        return *this =*this - a;
    }

    Longint operator--(int) {
        return --(*this);
    }

    Longint &operator--() {
        *this = *this - 1;
        return *this;
    }

    Longint operator++(int) {
        return ++(*this);
    }

    Longint &operator++() {
        *this = *this + 1;
        return *this;
    }

    Longint pow(Longint a, Longint n){
        Longint res = 1;
        while (n>0){
            if (n%2 == 1)
                res *= a;
            a *= a;
            n /= 2;
        }
        return res;
    }

    friend ostream &operator<<(ostream &s, const Longint &a) {
        Longint b = a;
        if (b.isneg())
            s << '-';
        for (int i = b.get().size() - 1; i >= 0; i--)
            s << b.get()[i];
        return s;
    }

};



Longint fact(const Longint &N) {
    Longint res = 1;
    if (N == 0)
        return res = 1;
    for (Longint i(1); i <= N; i = i + 1) {
        res = res * i;
    }
    return res;
}

Longint comb(Longint &N, Longint &K) {
    return fact(N) / (fact(K) * fact(N - K));
}

int main() {
    Longint a=1;

    int c = a>0;
    cout << c;
    return 0;
}