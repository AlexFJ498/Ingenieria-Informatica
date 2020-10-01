/*
 * util.h
 *
 *  Created on: 06/03/2015
 *      Author: pedroa
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()

namespace util{
static int * integerRandomVectoWithoutRepeating(int min, int max, int howMany){
        int total = max-min+1;
        int* numbersToBeSelected = new int[total];
        int* numbersSelected = new int[howMany];
        // Initialize the list of possible selections
        for(int i = 0; i < total; i++)
                numbersToBeSelected[i] = min+i;

        for(int i=0; i < howMany; i++)
        {
                int selectedNumber = rand() % (total-i);
                // Store the selected number
                numbersSelected[i]=numbersToBeSelected[selectedNumber];
                // We include the last valid number in numbersToBeSelected, in this way
                // all numbers are valid until total-i-1
                numbersToBeSelected[selectedNumber]=numbersToBeSelected[total-i-1];
        }
        delete [] numbersToBeSelected;
        return numbersSelected;

};

}


#endif /* UTIL_H_ */
