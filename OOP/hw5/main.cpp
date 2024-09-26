#include"frac.h"
#include"frac.cpp"
#include<sstream>
int main(){
    cout << "##############################   Test    ############################" << endl;
    cout << "###################### Test of constructor and to_string #####################" << endl;
    cout <<endl;
    Frac f1;
    Frac f2;
    ifstream in1("frac.txt");
    in1 >> f1;
    in1 >> f2;
    in1.close();
    cout << "The first fraction is: " << f1.to_string() << endl;
    cout << "The second fraction is: " << f2.to_string() << endl;
    cout << "######################## Test of copy constructor ########################" << endl;
    cout << endl;
    Frac f3 = f1;
    cout << "The copy of fraction1 is: " << f3.to_string() << endl;
    cout << "###################### Test of Arithmetic operators #######################" << endl;
    cout << endl;
    cout << "The sum of the two fractions is: " << (f1+f2).to_string() << " or " << (f1+f2).to_double() << endl; 
    cout << "The difference of the two fractions is: " << (f1-f2).to_string() << " or " << (f1-f2).to_double() << endl;
    cout << "The product of the two fractions is: " << (f1*f2).to_string() << " or " << (f1*f2).to_double() << endl;
    cout << "The division of the two fractions is: " << (f1/f2).to_string() << " or " << (f1/f2).to_double() << endl;
    Frac f0 = 1.414 + f1;
    cout << "The sum of 1.414 and the first fraction  "<<f1<< "  is: " << f0.to_string() << " or " << f0.to_double() << endl;
    f0 = 1.414 - f1;
    cout << "The difference of 1.414 and the first fraction  "<<f1<< "  is: " << f0.to_string() << " or " << f0.to_double() << endl;
    f0 = 1.414 * f1;
    cout << "The product of 1.414 and the first fraction  "<<f1<< "  is: " << f0.to_string() << " or " << f0.to_double() << endl;
    f0 = 1.414 / f1;
    cout << "The division of 1.414 and the first fraction  "<<f1<< "  is: " << f0.to_string() << " or " << f0.to_double() << endl;
    cout << "######################### Test of Comparison operators #######################" << endl;
    cout << endl;
    cout << "The first fraction is equal to the second fraction: " << (f1==f2) << endl;
    cout << "The first fraction is not equal to the second fraction: " << (f1!=f2) << endl;
    cout << "The first fraction is less than the second fraction: " << (f1<f2) << endl;
    cout << "The first fraction is greater than the second fraction: " << (f1>f2) << endl;
    cout << "The first fraction is less than or equal to the second fraction: " << (f1<=f2) << endl;
    cout << "The first fraction is greater than or equal to the second fraction: " << (f1>=f2) << endl;
    cout << "1.414 is equal to the first fraction: " << (1.414==f1) << endl;
    cout << "1.414 is not equal to the first fraction: " << (1.414!=f1) << endl;
    cout << "1.414 is less than the first fraction: " << (1.414<f1) << endl;
    cout << "1.414 is greater than the first fraction: " << (1.414>f1) << endl;
    cout << "1.414 is less than or equal to the first fraction: " << (1.414<=f1) << endl;
    cout << "1.414 is greater than or equal to the first fraction: " << (1.414>=f1) << endl;


    cout << "##################### Test of Inserter and extractor for streams ##################" << endl;
    cout << endl;
    ofstream out("output.txt");
    out << f1 << endl;
    out << f2 << endl;
    out << f0;
    out.close();
    cout << "The fractions are written to the file output.txt" << endl;

    cout << "##################### Test of Conversion from a finite decimal string ##################" << endl;
    cout << endl;
    Frac f4;
    f4.from_decimal("1.414");
    Frac f5 = 2.718; //Type conversion by the constructor!
    cout << "The fraction from the decimal number 2.718 is: " << f5.to_string() << endl;
    cout << "The fraction from the decimal number 1.414 is: " << f4.to_string() << endl;

    
    
    return 0;
}