//
//  JSONThread.h
//  example-flickr
//
//  Created by Ben Van Citters on 10/4/13.
//
//

#include "ofMain.h"

#ifndef __example_flickr__JSONThread__
#define __example_flickr__JSONThread__

#include <iostream>
class JSONThread : public ofThread {
    

    // the thread function
    void threadedFunction();
    
    void (*callBack)(std::string);
    ofVideoGrabber cam;  // the cam
    ofImage image;
};
#endif /* defined(__example_flickr__JSONThread__) */
