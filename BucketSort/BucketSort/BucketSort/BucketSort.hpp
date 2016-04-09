//
//  BucketSort.hpp
//  BucketSort
//
//  Created by Demon on 10/04/16.
//  Copyright © 2016 victor choudhary. All rights reserved.
//

#ifndef BucketSort_hpp
#define BucketSort_hpp

#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>

template <typename t>
class bucket_sort {
    
public:
    void bsort(t *  array,int l,const t min,const t max,const double load);

};



#endif /* BucketSort_hpp */
