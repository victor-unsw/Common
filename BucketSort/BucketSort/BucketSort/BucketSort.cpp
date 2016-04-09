//
//  BucketSort.cpp
//  BucketSort
//
//  Created by Demon on 10/04/16.
//  Copyright © 2016 victor choudhary. All rights reserved.
//

#include "BucketSort.hpp"

/*
 
 a = array
 l = array length
 */
template <typename t>
void showBucket(std::list<t> b){
    for(auto it=b.begin();it!=b.end();it++)
        std::cout << *it << " ";
}

template <typename t>
void bucket_sort<t>::bsort(t*  a,int l,const t min,const t max,const double load) {
    
    std::cout << "started\n";
    
    int s = std::ceil((max-min+1)*load);                                       // size of array
    
    // construct base array<list>
    std::list<t> *buckets = new std::list<t>[s];
    std::cout << "size : "<< s ;
    
    // fill each element in its own bucket
    for (int i=0; i<l; i++) {
        t   e = a[i];
        if (e == '\0')
            std::cout << "caught newline";
        int b = ((e-min)*load);                                     // bucket position
        //std::cout << "pushed : " << e << " in " << b << std::endl;
        buckets[b].push_back(e);
    }
    
    //std::cout << "bucketd\n";
    //std::cin.get();
    /*
    for (int i=0; i<s; i++) {
        //std::cout << "bucket["<<i<<"]:";
        showBucket<t>(buckets[i]);
        std::cout << "\n";
    }*/
    
    std::list<t> *answer = NULL;
    // retrieve each element
    for (int i=0; i<s; i++) {
        buckets[i].sort();
        if (answer == NULL) {
            answer = new std::list<t>(buckets[i]);
        }else{
        if (buckets[i].size() >= 1)
            answer->merge(buckets[i]);
        }
        //std::cout << "answer : ";
        //showBucket<t>(*answer);
        //std::cout << "\n";
    }
    int i=0;
    for (auto it=answer->begin(); it!=answer->end(); it++,i++)
        a[i] = *it;
    
    std::cout << std::endl;
    delete [] buckets;
    std::cout << "done\n";
}