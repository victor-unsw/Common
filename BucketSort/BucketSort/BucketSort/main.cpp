//
//  main.cpp
//  BucketSort
//
//  Created by Demon on 10/04/16.
//  Copyright © 2016 victor choudhary. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

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

min_max getMinMax(char* array,int l){
    int max = 0;
    int min = INT_MAX;
    for (int i=0; i<l; i++) {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min){
            min =  array[i];
        }
    }
    min_max r;
    r.min = min;
    r.max = max;
    return r;
}

int main(int argc, const char * argv[]) {
    
    bool write = false;
    
    ifstream input("/Users/victorchoudhary/Documents/DOC0.txt");
    ofstream output("/Users/victorchoudhary/Documents/Sort.txt");
    clock_t tt = clock();
    
    streampos begin,end;
    begin   = input.tellg();    input.seekg(0,ios::end);
    end     = input.tellg();    input.seekg(0,ios::beg);
    long size = end-begin;
    cout << "file size : " << size/1000 << " KB"<< endl;
    
    char* buffer = new char[size];
    
    clock_t it = clock();
    int c = 0;
    int i = 0;
    while ((c = input.get())!=EOF) {
        if (isspace(c))
            while (isspace(c = input.get()));
        buffer[i++] = c;
    }
    it = clock() - it;
    cout << "[reading time] \t: ";printf("%-5.3f sec.\n",double(it)/CLOCKS_PER_SEC);
    input.close();
    
    min_max mm = getMinMax(buffer,int(size));
    
    bucket_sort<char> b;
    clock_t st = clock();
    b.bsort(buffer, int(size), mm.min, mm.max,1);
    st = clock() - st;
    cout << "[sorting time] \t: ";printf("%-5.3f sec.\n",double(st)/CLOCKS_PER_SEC);
    

    if (write) {
        clock_t ot = clock();
        for (int i=0; i<size; i++)
            output <<buffer[i];
        ot = clock() - ot;
        cout << "[writing time] \t: ";printf("%-5.3f sec.\n",double(ot)/CLOCKS_PER_SEC);
    }
    
    delete [] buffer;

    tt = clock() - tt;
    cout << "[total time] \t: ";printf("%-5.3f sec.\n",double(tt)/CLOCKS_PER_SEC);
    //cin.get();
    return 0;
}


