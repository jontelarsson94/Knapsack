//
//  main.cpp
//  Knapsack
//
//  Created by Jonathan Larsson on 2017-01-26.
//  Copyright © 2017 Jonathan Larsson. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

void sortByRatio(float benefit[], float weight[], float ratio[], int size);

class Node{
    
public:
    Node *parent;
    int benefitFromStart;
    int weightFromStart;
    int id;
    bool taken;
    
    Node(Node *parent, int benefitFromStart, int weightFromStart, int id, bool taken)
    {
        this->id = id;
        this->parent = parent;
        this->benefitFromStart = benefitFromStart;
        this->weightFromStart = weightFromStart;
        this->taken = taken;
    }
    
    void changeValues(Node *parent, int benefitFromStart, int weightFromStart, int id, bool taken)
    {
        this->id = id;
        this->parent = parent;
        this->benefitFromStart = benefitFromStart;
        this->weightFromStart = weightFromStart;
        this->taken = taken;
    }
};

void KnapsackBFS(Node *bestNode, Node *node, int benefit[], int weight[], int size, int maxWeight);
void KnapsackDFS(Node *bestNode, Node *node, int benefit[], int weight[], int size, int maxWeight);

queue <Node*> nodes;
stack <Node*> nodes2;

int main(int argc, const char * argv[])
{
    
    int benefit[] = {20, 40, 50, 36, 25, 64, 54, 18, 46, 28, 25};
    int weight[] = {15, 32, 60, 80, 43, 120, 77, 6, 93, 35, 37};
    int W = 420;
    int n = sizeof(benefit)/sizeof(float);
    //float ratio[n];
    
    Node *bestNode = new Node(NULL, 0, 0, 0, false);
    
    Node *node = new Node(NULL, 0, 0, 0, false);
    
    KnapsackDFS(bestNode, node, benefit, weight, n, W);
    
    
    cout << "The biggest benefit we can get is: " << bestNode->benefitFromStart << endl;
    cout << "The items we need to take is:" << endl;
    while(bestNode->id != 0) {
        if(bestNode->taken)
            cout << bestNode->id << endl;
        bestNode = bestNode->parent;
    }
    
    
    
    /*for(int i = 0; i < n; i++) {
        ratio[i] = benefit[i] / weight[i];
    }*/
    
    //sortByRatio(benefit, weight, ratio, n);
    
    /*int currentW = 0;
    int maxProf = 0;
    for(int i = 0; i < n; i++) {
        if(currentW + weight[i] < W) {
            currentW += weight[i];
            maxProf += benefit[i];
        }
    }*/
    
    //cout << maxProf;
    
    return 0;
}


void KnapsackBFS(Node *bestNode, Node *node, int benefit[], int weight[], int size, int maxWeight)
{
    
    int counter = 0;
    
    nodes.push(node);
    
    while(!nodes.empty()) {
        
        Node *parent = nodes.front();
        
        nodes.pop();
        
        Node *left = new Node(parent, parent->benefitFromStart + benefit[parent->id], parent->weightFromStart + weight[parent->id], parent->id+1, true);
        Node *right = new Node(parent, parent->benefitFromStart, parent->weightFromStart, parent->id+1, false);
        
        if(left->weightFromStart < maxWeight)
        {
            if(parent->id < size){
                nodes.push(left);
            }
            
            if(parent->id == 0) {
                bestNode->changeValues(left->parent, left->benefitFromStart, left->weightFromStart, left->id, left->taken);
            }
            
            if(left->benefitFromStart > bestNode->benefitFromStart) {
                bestNode->changeValues(left->parent, left->benefitFromStart, left->weightFromStart, left->id, left->taken);
            }
        }
        if(parent->id < size){
            nodes.push(right);
        }
        
        //cout << bestNode->benefitFromStart << endl;
        
    }
}

void KnapsackDFS(Node *bestNode, Node *node, int benefit[], int weight[], int size, int maxWeight)
{
    
    int counter = 0;
    
    nodes2.push(node);
    
    while(!nodes2.empty()) {
        
        Node *parent = nodes2.top();
        
        nodes2.pop();
        
        Node *left = new Node(parent, parent->benefitFromStart + benefit[parent->id], parent->weightFromStart + weight[parent->id], parent->id+1, true);
        Node *right = new Node(parent, parent->benefitFromStart, parent->weightFromStart, parent->id+1, false);
        
        if(left->weightFromStart < maxWeight)
        {
            if(parent->id < size){
                nodes2.push(left);
            }
            
            if(parent->id == 0) {
                bestNode->changeValues(left->parent, left->benefitFromStart, left->weightFromStart, left->id, left->taken);
            }
            
            if(left->benefitFromStart > bestNode->benefitFromStart) {
                bestNode->changeValues(left->parent, left->benefitFromStart, left->weightFromStart, left->id, left->taken);
            }
        }
        if(parent->id < size){
            nodes2.push(right);
        }
        
        //cout << bestNode->benefitFromStart << endl;
        
    }
}


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
