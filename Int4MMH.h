#pragma once

#include <string>

using namespace std;

class Int4MMH
{
public:
    int data;

    Int4MMH() { data = 0; };
    Int4MMH(int n) : data(n){};

    ~Int4MMH() {};

    string toString()
    {
        return to_string(data);
    };

    friend int compare(const Int4MMH& n1);
};

int compare(const Int4MMH& n1, const Int4MMH& n2)
{
    if (n1.data < n2.data) return -1;
    if (n1.data > n2.data) return 1;
    return 0;
}
