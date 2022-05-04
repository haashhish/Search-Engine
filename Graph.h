#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include"Website.h"

using namespace std;

class Graph
{
    private:
    int numOfVertices;
    vector<int> *adjacencyList;

    public:
    Graph(int n)
    {
        numOfVertices = n;
        adjacencyList = new vector<int>[numOfVertices];
    }

    void addEdge(website* sites,int n) //here it creates the directed webgraph using the adjacency list
    {
        vector<int> indexes;
        string temp;
        fstream file;
        file.open("webgraph.csv");
        while(!file.eof())
        {
            int flag = 0;
            file>>temp;
            stringstream split(temp);
            string data;
            while (split.good()) 
            {
                string data;
                getline(split, data, ',');
                for(int i=0; i<n; i++)
                {
                    if(data==sites[i].checkLink())
                    {
                        indexes.push_back(sites[i].vNum()); //it stores the indexes by order in the vector calles indexes
                    }
                }
            }
        }
        file.close();
        vector<int>::iterator it = indexes.begin();
        while(it!=indexes.end())
        {
            adjacencyList[*it].push_back(*(it+1)); //here, all indexes are added to the adjacency list with the right order to form a directed graph
            it=it+2;
        }
    }

    void displayGraph(int total)
    {
        for(int i=0; i<total; i++)
        {
            cout<<"Vertex no. "<<i;
            vector<int>::iterator it=adjacencyList[i].begin();
            while(it!=adjacencyList[i].end())
            {
                cout<<"->"<<*it;
                it++;
            }
            cout<<endl;
        }
    }

    double outgoing(int index, int* to,double cTotal)
    {
        double counter=0;
        vector<int>::iterator it = adjacencyList[index].begin();
        int i=0;
        while(it!=adjacencyList[index].end()) //here i count all outgoing edges from a certain node, and save the value for each node;
        {
            to[i] = *it;
            counter++;
            i++;
            it++;
        }
        if(counter==0) //if there exists dangling nodes, i must assume that it is connected to every other nodes and also to itself so that page rank is calculated in a right way;
        {
            counter=cTotal;
            for(int i = 0; i<cTotal; i++)
            {
                to[i]=i;
            }
            return counter;
        }
        else
        {
            return counter;    
        }
    }
};
#endif