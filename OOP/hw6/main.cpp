#include"vector.h"
#include"vector.cpp"
int main(){
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    int a;
    cin >> a;
    cout << "########  Test for push_back(constructor to create an empty vector) #######" << endl;
    cout << "v[0] = " << v[0] << endl;
    cout << "v[1] = " << v[1] << endl;
    cout << "v[2] = " << v[2] << endl;
    cout << "#############  Test for operator []  ############" << endl;
    v[0] = 2;
    v[1] = 3;
    v[2] = 4;
    cout << "v[0] = " << v[0] << endl;
    cout << "v[1] = " << v[1] << endl;
    cout << "v[2] = " << v[2] << endl;
    cout << "#############  Test for clear() and empty()  ############" << endl;
    v.clear();
    cout << "Whether the vector is empty after clear operation: " << v.empty() << endl;
    v.push_back(1);
    cout << "Whether the vector is empty after push_back " << v.empty() << endl;

    cout << "#############  Test for at  ############" << endl;
    try {
        cout << v.at(1) << endl;
    } catch (std::out_of_range& e) {
        cout << e.what() << endl;
    }
    cout << "#############  Test for ctor(and size and inflate)  ############" << endl;
    Vector<int> v2(5);
    cout << "size: " << v2.size() << endl;
    v2.push_back(1);
    cout << "size after push_back(1): " << v2.size() << endl;
    v2.push_back(2);
    v2.push_back(3);
    v2.push_back(4);
    v2.push_back(5);
    cout << "v2[0] = " << v2[0] << endl;
    cout << "v2[1] = " << v2[1] << endl;
    cout << "v2[2] = " << v2[2] << endl;
    cout << "v2[3] = " << v2[3] << endl;
    cout << "v2[4] = " << v2[4] << endl;
    cout << "v2[5] = " << v2[5] << endl;
    cout << "v2[6] = " << v2[6] << endl;
    cout << "v2[7] = " << v2[7] << endl;
    cout << "v2[8] = " << v2[8] << endl;
    cout << "v2[9] = " << v2[9] << endl;   
    cout << endl;
    Vector<int> v3 = v2;
    cout << "v3 is a copy of v2" << endl;
    cout << "v3[0] = " << v3[0] << endl;
    cout << "v3[1] = " << v3[1] << endl;
    cout << "v3[2] = " << v3[2] << endl;
    cout << "v3[3] = " << v3[3] << endl;
    cout << "v3[4] = " << v3[4] << endl;
    cout << "v3[5] = " << v3[5] << endl;
    cout << "v3[6] = " << v3[6] << endl;
    cout << "v3[7] = " << v3[7] << endl;
    cout << "v3[8] = " << v3[8] << endl;
    cout << "v3[9] = " << v3[9] << endl;

    cout << "#############  Test for dtor  ############" << endl;
    cout << "Destructor will be called after this line" << endl;
    
    return 0;
}