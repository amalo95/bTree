//
//  main.cpp
//  BTree
//
//  Created by Agustin Malo  on 4/2/15.
//  Copyright (c) 2015 Agustin Malo . All rights reserved.
//
#include<iostream>
#include"bTree.h"

using namespace std;
int main () {
    
    int op = 0;
    int size;
    string key;
    string value;
    cin>>size;
    
    bTree * BT = new bTree(size);
    while(op < 4) {
        cout << "Enter op:\n";
        cin >> op;
        switch(op) {
            case 0://Insert
                cout << "insert\n";
                cin>>key;
                cin>>value;
                BT->insert(key,value);
                break;
            case 1://Delete
                cout << "delete key:\n";
                cin>>key;
                BT->delete_key(key);
                break;
            case 2://Find
                cout << "find key:\n";
                cin>>key;
                if(BT->find(key,&value))
                    cout<<value<<endl;
                else
                    cout<<"Key Not Found\n";
                break;
            case 3://toString
                cout << "string out:\n";
                cout<<BT->toStr();
                break;
        }
    }
    return 0;
}
