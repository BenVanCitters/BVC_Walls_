//
//  JSONThread.cpp
//  example-flickr
//
//  Created by Ben Van CItters on 10/4/13.
//
//

#include "JSONThread.h"
// the thread function
void JSONThread::threadedFunction()
{
    lock();
    std::string url;
    // start
    
    
    
    // done
    unlock();
    //call the completion callback with our url
    (*callBack)(url);
}
