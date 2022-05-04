#include<iostream>
#include<vector>
#include"Graph.h"
#include"Website.h"

using namespace std;

double **matrixPR;

int countWebsites()
{
    int counter = 0;
    string temp;
    ifstream file;
    file.open("keywords.csv");
    while(!file.eof())
    {
        getline(file,temp);
        counter++;
    }
    file.close();
    return counter;
}

int main()
{
    char n;
    int choice;
    double counter;
    int counterOfSites = countWebsites();
    matrixPR = new double*[counterOfSites];
    for(int i=0; i<counterOfSites;i++)
    {
        matrixPR[i] = new double[counterOfSites];
    }
    for(int i=0; i<counterOfSites; i++)
    {
        for(int j=0; j<counterOfSites; j++)
        {
            matrixPR[i][j]=0;
        }
    }
    website *allSites = new website[counterOfSites];
    allSites->setData(allSites);
    allSites->setInitialPRForall(allSites,counterOfSites);
    Graph webGraph(counterOfSites); //creates a graph with no. of available nodes
    webGraph.addEdge(allSites,counterOfSites); //creates the directed edges between the nodes
    for(int i=0; i<counterOfSites; i++)
    {
        int to[100];
        counter = webGraph.outgoing(i, to,(double)counterOfSites); //to get number of elements and their indexes
        for(int j=0; j<counter; j++)
        {
            matrixPR[to[j]][i]=1/counter;
        }
    }
    allSites->setPRSpecific(allSites,matrixPR, counterOfSites);
    allSites->setScores(allSites,counterOfSites);
    allSites->menu1(allSites, counterOfSites);
}