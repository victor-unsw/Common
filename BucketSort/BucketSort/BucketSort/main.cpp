//
//  main.cpp
//  BucketSort
//
//  Created by Demon on 10/04/16.
//  Copyright © 2016 victor choudhary. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <fstream>

#include "BucketSort.hpp"
#include "BucketSort.cpp"

using namespace std;

void show(char* arr,int l){
    for (int i=0; i<l; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

struct min_max{
    int min;
    int max;
};

min_max getMinMax(string array){
    int max = 0;
    int min = INT_MAX;
    
    for (auto it=array.begin(); it!=array.end(); it++) {
        if (*it > max) {
            max = *it;
        }
        if (*it < min) {
            min = *it;
        }
    }
    min_max r;
    r.min = min;
    r.max = max;
    return r;
}

int main(int argc, const char * argv[]) {
    string array;
    
    char buffer[1000];
    ifstream input("/Users/victorchoudhary/Documents/Email.txt");
    ofstream output("/Users/victorchoudhary/Documents/Sort.txt");
    
    while (input >> buffer)
        //array.append("\n");
        array.append(buffer);
    cout << array.size() << endl;
    min_max r = getMinMax(array);
    cout << "min : " << r.min << "\nmax : " << r.max << endl;
    char * pt = new char[array.size()];
    for (int i=0; i<array.size(); i++) {
        pt[i] = array[i];
    }
    
    bucket_sort<char> b;
    b.bsort(pt, int(array.size()), r.min, r.max, 0.3);
    
    for (int i=0; i<array.size(); i++) {
        cout << pt[i];
        output <<pt[i];
    }
    
    return 0;
}
