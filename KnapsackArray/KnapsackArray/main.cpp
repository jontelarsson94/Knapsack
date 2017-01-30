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
    int benefitFromStart;
    int weightFromStart;
    int id;
    bool taken[11];
    
    Node(int benefitFromStart, int weightFromStart, int id)
    {
        this->id = id;
        this->benefitFromStart = benefitFromStart;
        this->weightFromStart = weightFromStart;
        for(int i = 0; i < 11; i++) {
            taken[i] = false;
        }
    }
    
    void changeValues(int benefitFromStart, int weightFromStart, int id, bool taken[])
    {
        this->id = id;
        this->benefitFromStart = benefitFromStart;
        this->weightFromStart = weightFromStart;
        for(int i = 0; i < 11; i++) {
            this->taken[i] = taken[i];
        }
    }
    
    void copyNode(Node node) {
        this->benefitFromStart = node.benefitFromStart;
        this->weightFromStart = node.weightFromStart;
        this->id = node.id;
        for(int i = 0; i < 11; i++) {
            this->taken[i] = node.taken[i];
        }
    }
    
    void copyTaken(Node node) {
        for(int i = 0; i < 11; i++) {
            this->taken[i] = node.taken[i];
        }
    }
};

void KnapsackBFS(int benefit[], int weight[], int size, int maxWeight);
void KnapsackDFS(int benefit[], int weight[], int size, int maxWeight);

queue <Node> nodes;
stack <Node> nodes2;

int main(int argc, const char * argv[])
{
    
    int benefit[] = {20, 40, 50, 36, 25, 64, 54, 18, 46, 28, 25};
    int weight[] = {15, 32, 60, 80, 43, 120, 77, 6, 93, 35, 37};
    int W = 420;
    int n = sizeof(benefit)/sizeof(float);
    
    KnapsackBFS(benefit, weight, n, W);
    //KnapsackDFS(bestNode, node, benefit, weight, n, W);
    
    return 0;
}

//Knapsack with BFS
void KnapsackBFS(int benefit[], int weight[], int size, int maxWeight)
{
    
    Node bestNode(0, 0, 0);
    Node node(0, 0, 0);
    //Using queue
    nodes.push(node);
    
    //While we have nodes to build tree from
    while(!nodes.empty()) {
        
        Node parent = nodes.front();
        
        //Take the oldest item from queue
        nodes.pop();
        
        //Set children to push in the queue
        Node left(parent.benefitFromStart + benefit[parent.id], parent.weightFromStart + weight[parent.id], parent.id+1);
        Node right(parent.benefitFromStart, parent.weightFromStart, parent.id+1);
        left.copyTaken(parent);
        right.copyTaken(parent);
        left.taken[parent.id] = true;
        right.taken[parent.id] = false;
        
        //If we still have chance to build longer path
        if(left.weightFromStart < maxWeight)
        {
            if(parent.id < size){
                nodes.push(left);
            }
            
            if(parent.id == 0) {
                bestNode.copyNode(left);
            }
            
            if(left.benefitFromStart > bestNode.benefitFromStart) {
                bestNode.copyNode(left);
            }
        }
        if(right.weightFromStart < maxWeight){
            if(parent.id < size){
                nodes.push(right);
            }
        }
    }
    cout << "The biggest benefit we can get is: " << bestNode.benefitFromStart << endl;
    cout << "The items we need to take is:" << endl;
    for(int i = 0; i < 11; i++) {
        if(bestNode.taken[i]) {
            cout << i+1 << endl;
        }
    }
}

//Knapsack with DFS
/*void KnapsackDFS(Node *bestNode, Node *node, int benefit[], int weight[], int size, int maxWeight)
{
    //Using stack
    nodes2.push(node);
    
    //While we have nodes to build tree from
    while(!nodes2.empty()) {
        
        Node *parent = nodes2.top();
        
        //Take newest item from stack
        nodes2.pop();
        
        //Set children to push in the stack
        Node *left = new Node(parent, parent->benefitFromStart + benefit[parent->id], parent->weightFromStart + weight[parent->id], parent->id+1, true);
        Node *right = new Node(parent, parent->benefitFromStart, parent->weightFromStart, parent->id+1, false);
        
        
        //If we still have chance to build longer path
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
        if(right->weightFromStart < maxWeight){
            if(parent->id < size){
                nodes2.push(right);
            }
        }
    }
}*/


/*void sortByRatio(float benefit[], float weight[], float ratio[], int size)
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
 }*/
