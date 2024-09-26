#ifndef FRAC_HEADER
#define FRAC_HEADER
#include <iostream>
#include <fstream>
using namespace std;
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
using namespace std;
class Frac {
    private:
        int domi;
        int frac;
    public:
        //Default constructor
        Frac(){};
        //Constructor with parameters
        Frac(int domi, int frac): domi(domi), frac(frac) {}
        //Copy constructor
        Frac (const Frac &f) : domi(f.domi), frac(f.frac) {}
        //Constructor from a decimal number
        Frac (double d) {
            from_decimal(std::to_string(d));
        }
        
        //Assignment operator
        friend bool operator==(const Frac &l, const Frac &r);
        friend bool operator!=(const Frac &l, const Frac &r);
        friend bool operator<(const Frac &l, const Frac &r);
        friend bool operator>(const Frac &l, const Frac &r);
        friend bool operator<=(const Frac &l, const Frac &r);
        friend bool operator>=(const Frac &l, const Frac &r);
        //Arithmetic operators
        friend const Frac operator+(const Frac &l, const Frac &r);
        friend const Frac operator-(const Frac &l, const Frac &r);
        friend const Frac operator*(const Frac &l, const Frac &r);
        friend const Frac operator/(const Frac &l, const Frac &r);
        friend ostream &operator<<(ostream &os, const Frac &f);
        friend ifstream &operator>>(ifstream &is, Frac &f);

        string to_string() const;
        double to_double() const;
        //Conversion from a finite decimal string like: 1.414
        void from_decimal(const string &s);
        //inserter and extractor for streams
};

#endif