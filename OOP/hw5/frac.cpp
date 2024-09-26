#include"frac.h"
const Frac operator+(const Frac &l, const Frac &r) {
    int new_domi = l.domi*r.frac + l.frac*r.domi;
    int new_frac = l.frac*r.frac;
    //Find the greatest common divisor
    int a = new_domi, b = new_frac;
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return Frac(new_domi/a, new_frac/a);
}
const Frac operator-(const Frac &l, const Frac &r) {
    int new_domi = l.domi*r.frac - l.frac*r.domi;
    int new_frac = l.frac*r.frac;
    //Find the greatest common divisor
    int a = new_domi, b = new_frac;
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return Frac(new_domi/a, new_frac/a);
}
const Frac operator*(const Frac &l, const Frac &r) {
    int new_domi = l.domi*r.domi;
    int new_frac = l.frac*r.frac;
    //Find the greatest common divisor
    int a = new_domi, b = new_frac;
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return Frac(new_domi/a, new_frac/a);
}
const Frac operator/(const Frac &l, const Frac &r) {
    int new_domi = l.domi*r.frac;
    int new_frac = l.frac*r.domi;
    //Find the greatest common divisor
    int a = new_domi, b = new_frac;
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return Frac(new_domi/a, new_frac/a);
}
bool operator==(const Frac &l, const Frac &r) {
    return l.domi*r.frac == l.frac*r.domi;
}
bool operator!=(const Frac &l, const Frac &r) {
    return l.domi*r.frac != l.frac*r.domi;
}
bool operator<(const Frac &l, const Frac &r) {
    return l.domi*r.frac < l.frac*r.domi;
}
bool operator>(const Frac &l, const Frac &r) {
    return l.domi*r.frac > l.frac*r.domi;
}
bool operator<=(const Frac &l, const Frac &r) {
    return l.domi*r.frac <= l.frac*r.domi;
}
bool operator>=(const Frac &l, const Frac &r) {
    return l.domi*r.frac >= l.frac*r.domi;
}

string Frac::to_string() const {
    return std::to_string(domi) + "/" + std::to_string(frac);
}
double Frac::to_double() const {
    return (double)domi/frac;
}
ostream &operator<<(ostream &os, const Frac &f) {
    os << f.to_string();
    return os;
}
ifstream &operator>>(ifstream &is, Frac &f) {
            string s;
            is >> s;
            int pos = s.find("/");
            f.domi = stoi(s.substr(0, pos));
            f.frac = stoi(s.substr(pos+1));
            return is;
}
void Frac::from_decimal(const string &s){
    double decimal = std::stod(s);
    int precision = 1000000; 
    int numerator = round(decimal * precision); 
    int denominator = precision; 
    // Find the greatest common divisor
    int commonDivisor = gcd(numerator, denominator);
    numerator /= commonDivisor;
    denominator /= commonDivisor;
    this->domi = numerator;
    this->frac = denominator;
}
