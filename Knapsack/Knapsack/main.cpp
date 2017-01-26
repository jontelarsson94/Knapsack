//
//  main.cpp
//  Knapsack
//
//  Created by Jonathan Larsson on 2017-01-26.
//  Copyright © 2017 Jonathan Larsson. All rights reserved.
//

#include <iostream>
using namespace std;

void sortByRatio(float benefit[], float weight[], float ratio[], int size)
{
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(ratio[i] > ratio[j]) {
                float save = ratio[j];
                ratio[j] = ratio[i];
                ratio[i] = save;
                save = benefit[j];
                benefit[j] = benefit[i];
                benefit[i] = save;
                save = weight[j];
                weight[j] = weight[i];
                weight[i] = save;
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    
    float benefit[] = {20, 40, 50, 36, 25, 64, 54, 18, 46, 28};
    float weight[] = {15, 32, 60, 80, 43, 120, 77, 6, 93, 35};
    int W = 420;
    int n = sizeof(benefit)/sizeof(float);
    float ratio[n];
    
    for(int i = 0; i < n; i++) {
        ratio[i] = benefit[i] / weight[i];
    }
    
    sortByRatio(benefit, weight, ratio, n);
    
    for(int i = 0; i < n; i++)
    {
        cout << benefit[i] << endl;
    }
    
    int currentW = 0;
    int maxProf = 0;
    for(int i = 0; i < n; i++) {
        if(currentW + weight[i] < W) {
            currentW += weight[i];
            maxProf += benefit[i];
        }
    }
    
    cout << currentW << endl;
    cout << maxProf;
    
    return 0;
}
