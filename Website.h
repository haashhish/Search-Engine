#ifndef WEBSITE_H
#define WEBSITE_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<cmath>
#include<iomanip>

using namespace std;

double *initialPRs;

class website
{
    private:
    int vertexNumber;
    string link = "";
    vector<string> keywords;
    double pageRank=0;
    double numberOfClicks=0;
    double numOfImpressions=0;
    double ctr=0;
    double score=0;

    public:
    void setData(website *sites)
    {
        int c=0;
        int vertex=0;
        string temp;
        ifstream file;
        file.open("keywords.csv");
        while(!file.eof()) //here to set the link of every website and add the assigned keywords from file keywords.csv
        {
            file>>temp;
            stringstream split(temp);
            string data;
            while (split.good()) 
            {
                getline(split, data, ',');
                if(sites[c].link == "")
                {
                    sites[c].link = data;
                    sites[c].vertexNumber=vertex;
                    vertex=vertex+1;
                }
                else
                {
                    sites[c].keywords.push_back(data);
                }
            }
            c++;
        }
        file.close();
        c=0;
        file.open("impressions.csv"); //here it adds the initial number of impressions from file impressions.csv
        while(!file.eof())
        {
            file>>temp;
            stringstream split(temp);
            string data;
            while (split.good()) 
            {
                string data;
                getline(split, data, ',');
                if(sites[c].link==data)
                {
                    //do nothing
                }
                else
                {
                    sites[c].numOfImpressions = stoi(data);
                }
            }
            c++;
        }
        file.close();
        c=0;
        file.open("clicks.csv"); //here it adds the initial number of impressions from file impressions.csv
        while(!file.eof())
        {
            file>>temp;
            stringstream split(temp);
            string data;
            while (split.good()) 
            {
                string data;
                getline(split, data, ',');
                if(data!=sites[c].link)
                {
                    sites[c].numberOfClicks = stoi(data);
                }
            }
            c++;
        }
        file.close();
        for(int i=0; i<c; i++)
        {
            sites[i].ctr=(sites[i].numberOfClicks/sites[i].numOfImpressions)*100;
        }
    }

    void saveData(website* sites, int counter)
    {
        ofstream file;
        file.open("impressions.csv");
        for(int i=0; i<counter; i++)
        {
            if(i==counter-1)
            {
                file<<sites[i].link<<","<<sites[i].numOfImpressions;
            }
            else
            {
                file<<sites[i].link<<","<<sites[i].numOfImpressions<<endl;
            }
        }
        file.close();
        file.open("clicks.csv");
        for(int i=0; i<counter; i++)
        {
            if(i==counter-1)
            {
                file<<sites[i].link<<","<<sites[i].numberOfClicks;
            }
            else
            {
                file<<sites[i].link<<","<<sites[i].numberOfClicks<<endl;
            }
        }
        file.close();
    }

    void updateCTR(website *sites, int n)
    {
        for(int i=0; i<n; i++)
        {
            sites[i].ctr=(sites[i].numberOfClicks/sites[i].numOfImpressions)*100;
        }
    }

    void setScores(website* sites,int n) //calculate total score based on CTR and PR
    {
        for(int i = 0; i<n; i++)
        {
            sites[i].score = 0.4 * sites[i].pageRank + ((1 - ((0.1 * sites[i].numOfImpressions) / (1 + 0.1 * sites[i].numOfImpressions))) * sites[i].pageRank + ((0.1 * sites[i].numOfImpressions) / (1 + 0.1 * sites[i].numOfImpressions)) * sites[i].ctr) * 0.6;
        }
        cout<<endl;
    }

    void setInitialPRForall(website* sites, int c)
    {
        initialPRs = new double[c];
        for(int i=0; i<c; i++)
        {
            initialPRs[i]=(pow(c,-1));
        }
    }

    void setPRSpecific(website* sites, double **matrix, int c)
    {
        double result[c];
        double** resultMatrix = new double*[c];
	    for (int i = 0; i < c; i++)
	    {
		    resultMatrix[i] = new double[c];
	    }
	    for (int i = 0; i < c; i++)
	    {
		    for (int j = 0; j < c; j++)
		    {
			    resultMatrix[i][j] = 0;
		    }
	    }
	    for (int i = 0; i<c; i++)
	    {
		    for (int j = 0; j<c; j++)
		    {
			    resultMatrix[i][j] = 0;
			    for (int k = 0; k < c; k++)
			    {
				    resultMatrix[i][j] += matrix[i][k] * matrix[k][j];
			    }
		    }
	    }
        for (int i = 0; i<c; i++)
	    {
            result[i]=0;
		    for (int j = 0; j<c; j++)
		    {
                result[i] += (resultMatrix[i][j]*initialPRs[j]);
		    }
            sites[i].pageRank=result[i];
	    }
    }

    void merge(double array[], int const left, int const mid, int const right)
    {
        auto const subArrayOne = mid - left + 1;
        auto const subArrayTwo = right - mid;
  
        auto *leftArray = new double[subArrayOne],
             *rightArray = new double[subArrayTwo];
  
        for (auto i = 0; i < subArrayOne; i++)
            leftArray[i] = array[left + i];
        for (auto j = 0; j < subArrayTwo; j++)
            rightArray[j] = array[mid + 1 + j];
  
        auto indexOfSubArrayOne = 0,
            indexOfSubArrayTwo = 0;
        int indexOfMergedArray = left;
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne] >= rightArray[indexOfSubArrayTwo]) {
                array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }
        while (indexOfSubArrayOne < subArrayOne) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }
        while (indexOfSubArrayTwo < subArrayTwo) {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
}

    void mergeSort(double array[], int const begin, int const end)
    {
        if (begin >= end)
            return; 
  
        auto mid = begin + (end - begin) / 2;
        mergeSort(array, begin, mid);
        mergeSort(array, mid + 1, end);
        merge(array, begin, mid, end);
    }

    void menu2(vector<website> repeatSites, website* sites, int index, int numOfSites)
    {
        int choice;
        cout<<"What would you like to do?"<<endl;
        cout<<"1- Back to search results"<<endl;
        cout<<"2- New search"<<endl;
        cout<<"3- Exit"<<endl;
        cout<<"Your choice: ";
        cin>>choice;
        if(choice == 1)
        {
            int choose;
            for(int i=0; i<repeatSites.size(); i++)
            {
                cout<<i+1<<"- "<<repeatSites[i].link<<endl;
                repeatSites[i].numOfImpressions = repeatSites[i].numOfImpressions+1;
            }
            for(int i=0; i<numOfSites; i++)
                {
                    for(int j=0; j<index; j++)
                    {
                        if(sites[i].link==repeatSites[j].link)
                        {
                            sites[i].numOfImpressions = repeatSites[j].numOfImpressions;
                            sites[i].numberOfClicks = repeatSites[j].numberOfClicks;
                        }
                    }
                }
            saveData(sites,numOfSites);
            cout<<"Choose a website: ";
            cin>>choose;
            choose=choose-1;
            repeatSites[choose].numberOfClicks++;
            cout<<endl;
            cout<<"You are now on site: "<< repeatSites[choose].link<<endl;
            for(int i=0; i<numOfSites; i++)
            {
                for(int j=0; j<index; j++)
                {
                    if(sites[i].link==repeatSites[j].link)
                    {
                        sites[i].numOfImpressions = repeatSites[j].numOfImpressions;
                        sites[i].numberOfClicks = repeatSites[j].numberOfClicks;
                    }
                }
            }
                saveData(sites,numOfSites);
                menu2(repeatSites,sites, index, numOfSites);
            }
            else if(choice ==2)
            {
                search(sites,numOfSites);
            }
            else if(choice == 3)
            {
                //exit function
                saveData(sites,numOfSites);
                exit(0);
            }
    }

    int removeDuplicates(double arr[], int n)
    {
        if (n==0 || n==1)
        {
            return n;
        }
        int j = 0;
        for (int i=0; i < n-1; i++)
        {
            if (arr[i] != arr[i+1])
                {
                    arr[j++] = arr[i];
                }
        }
        arr[j++] = arr[n-1];
        return j;
    }

    void search(website *sites, int numOfSites)
    {
        char choice;
        int n=0;
        string query;
        string temp;
        do{
            bool AND=false;
            bool OR=false;
            bool quotation=false;
            int choice;
            double scores[numOfSites];
            int index=0;
            cout<<"Enter keywords to search in available sites: ";
            cin.ignore();
            getline(cin,query);
            stringstream split(query);
            string data;
            string temp=query;
            vector<string> keyWords;
            vector<website> availableSites;
            char quote = '"';
            if(query[0]==quote)
            {
                quotation=true;
            }
            while (split.good())
            {
                string data;
                getline(split, data,' ');
                if(data=="AND")
                {
                    AND=true;
                }
                else if(data=="OR")
                {
                    OR=true;
                }
            }
            if(AND==false && OR==false && quotation==false)
            {
                    int counter=0;
                    for(int i=0; i<numOfSites; i++)
                    {
                        vector<string>::iterator it=sites[i].keywords.begin();
                        while(it!=sites[i].keywords.end())
                        {
                            if(*it==query)
                            {
                                scores[index] = sites[i].score;
                                index++;
                            }
                            it++;
                        }
                    }
            
                index = removeDuplicates(scores,index); //remove any duplicates
                
                mergeSort(scores, index-index, index-1);
        
                for(int i=0; i<index; i++)
                {
                    for(int j=0; j<numOfSites; j++)
                    {
                        if(scores[i]==sites[j].score)
                        {
                            availableSites.push_back(sites[j]);
                        }
                    }
                }
                cout<<"Search results: "<<endl;
                cout<<"----------------"<<endl;
                for(int i=0; i<availableSites.size(); i++)
                {
                    cout<<i+1<<"- "<<availableSites[i].link<<endl;
                    availableSites[i].numOfImpressions = availableSites[i].numOfImpressions + 1;
                }
                for(int i=0; i<numOfSites; i++)
                {
                    for(int j=0; j<index; j++)
                    {
                        if(sites[i].link==availableSites[j].link)
                        {
                            sites[i].numOfImpressions = availableSites[j].numOfImpressions;
                            sites[i].numberOfClicks = availableSites[j].numberOfClicks;
                        }
                    }
                }
                saveData(sites,numOfSites);
                cout<<endl;
                cout<<"What would you link to do?"<<endl;
                cout<<"1- Choose a webpage to open"<<endl;
                cout<<"2- Perform new search"<<endl;
                cout<<"3- Exit"<<endl;
                cout<<"Your choice: ";
                cin>>choice;
                if(choice==1)
                {
                    cout<<"Choose a website: ";
                    cin>>choice;
                    choice=choice-1;
                    availableSites[choice].numberOfClicks++;
                    cout<<"You are now on site: "<< availableSites[choice].link<<endl;
                    for(int i=0; i<numOfSites; i++)
                    {
                        for(int j=0; j<index; j++)
                        {
                            if(sites[i].link==availableSites[j].link)
                            {
                                sites[i].numOfImpressions = availableSites[j].numOfImpressions;
                                sites[i].numberOfClicks = availableSites[j].numberOfClicks;
                            }
                        }
                    }
                    saveData(sites,numOfSites);
                    updateCTR(sites,numOfSites); //update ctr values
                    setScores(sites,numOfSites); //to update scores
                    menu2(availableSites, sites, index, numOfSites);
                }
                else if(choice == 2)
                {
                    search(sites,numOfSites);
                }
                else if(choice==3)
                {
                    //exit function
                    saveData(sites,numOfSites);
                    exit(0);      
                }
            }
            else if(AND==true && OR==false && quotation == false)
            {
                stringstream split(query);
                string data;
                vector<string> keyWords;
                while (split.good()) 
                {
                    string data;
                    getline(split, data,' ');
                    if(data=="AND")
                    {
                        //do nothing
                    }
                    else
                    {
                        keyWords.push_back(data);
                    }
                }

                for(int i=0; i<numOfSites; i++)
                {
                    int counter = 0;
                    vector<string>::iterator it = sites[i].keywords.begin();
                    while(it!=sites[i].keywords.end())
                    {
                        for(int k = 0; k<keyWords.size(); k++)
                        {
                            if(keyWords[k]==*it)
                            {
                                counter++;
                                if(counter==keyWords.size())
                                {
                                    scores[index] = sites[i].score;
                                    index++;
                                }
                            }
                        }
                        it++;
                    }
                }

                index = removeDuplicates(scores,index); //remove any duplicates

                mergeSort(scores, index-index, index-1);
        
                for(int i=0; i<index; i++)
                {
                    for(int j=0; j<numOfSites; j++)
                    {
                        if(scores[i]==sites[j].score)
                        {
                            availableSites.push_back(sites[j]);
                        }
                    }
                }
                cout<<"Search results: "<<endl;
                cout<<"----------------"<<endl;
                for(int i=0; i<availableSites.size(); i++)
                {
                    cout<<i+1<<"- "<<availableSites[i].link<<endl;
                    availableSites[i].numOfImpressions = availableSites[i].numOfImpressions+1;
                }
                for(int i=0; i<numOfSites; i++)
                {
                    for(int j=0; j<index; j++)
                    {
                        if(sites[i].link==availableSites[j].link)
                        {
                            sites[i].numOfImpressions = availableSites[j].numOfImpressions;
                            sites[i].numberOfClicks = availableSites[j].numberOfClicks;
                        }
                    }
                }
                saveData(sites,numOfSites);
                updateCTR(sites,numOfSites); //update ctr values
                setScores(sites,numOfSites); //to update scores
                cout<<endl;
                cout<<"What would you link to do?"<<endl;
                cout<<"1- Choose a webpage to open"<<endl;
                cout<<"2- Perform new search"<<endl;
                cout<<"3- Exit"<<endl;
                cout<<"Your choice: ";
                cin>>choice;
                if(choice==1)
                {
                    cout<<"Choose a website: ";
                    cin>>choice;
                    choice=choice-1;
                    availableSites[choice].numberOfClicks++;
                    cout<<"You are now on site: "<< availableSites[choice].link<<endl;
                    for(int i=0; i<numOfSites; i++)
                    {
                        for(int j=0; j<index; j++)
                        {
                            if(sites[i].link==availableSites[j].link)
                            {
                                sites[i].numOfImpressions = availableSites[j].numOfImpressions;
                                sites[i].numberOfClicks = availableSites[j].numberOfClicks;
                            }
                        }
                    }
                    saveData(sites,numOfSites);
                    updateCTR(sites,numOfSites); //update ctr values
                    setScores(sites,numOfSites); //to update scores
                    menu2(availableSites, sites, index, numOfSites);
                }
                else if(choice == 2)
                {
                    search(sites,numOfSites);
                }
                else if(choice==3)
                {
                    //exit function
                    saveData(sites,numOfSites);
                    exit(0);       
                }
            }
            else if(AND==false && OR==true && quotation==false)
            {
                stringstream split(query);
                string data;
                vector<string> keyWords;
                while (split.good()) 
                {
                    string data;
                    getline(split, data,' ');
                    if(data=="OR")
                    {
                        //do nothing
                    }
                    else
                    {
                        cout<<data<<endl;
                        keyWords.push_back(data);
                    }
                }
                for(int i=0; i<numOfSites; i++)
                {
                    vector<string>::iterator it = sites[i].keywords.begin();
                    while(it!=sites[i].keywords.end())
                    {
                        for(int k = 0; k<keyWords.size(); k++)
                        {
                            if(keyWords[k]==*it)
                            {
                                scores[index] = sites[i].score;
                                index++;
                            }
                        }
                        it++;
                    }
                }
            
                index = removeDuplicates(scores,index); //to remove any duplicates sites

                mergeSort(scores, index-index, index-1);
        
                for(int i=0; i<index; i++)
                {
                    for(int j=0; j<numOfSites; j++)
                    {
                        if(scores[i]==sites[j].score)
                        {
                            availableSites.push_back(sites[j]);
                        }
                    }
                }
                cout<<"Search results: "<<endl;
                cout<<"----------------"<<endl;
                for(int i=0; i<availableSites.size(); i++)
                {
                    cout<<i+1<<"- "<<availableSites[i].link<<endl;
                    availableSites[i].numOfImpressions = availableSites[i].numOfImpressions+1;
                }
                for(int i=0; i<numOfSites; i++)
                {
                    for(int j=0; j<index; j++)
                    {
                        if(sites[i].link==availableSites[j].link)
                        {
                            sites[i].numOfImpressions = availableSites[j].numOfImpressions;
                            sites[i].numberOfClicks = availableSites[j].numberOfClicks;
                        }
                    }
                }
                saveData(sites,numOfSites);
                updateCTR(sites,numOfSites); //update ctr values
                setScores(sites,numOfSites); //to update scores
                cout<<endl;
                cout<<"What would you link to do?"<<endl;
                cout<<"1- Choose a webpage to open"<<endl;
                cout<<"2- Perform new search"<<endl;
                cout<<"3- Exit"<<endl;
                cout<<"Your choice: ";
                cin>>choice;
                if(choice==1)
                {
                    cout<<"Choose a website: ";
                    cin>>choice;
                    choice=choice-1;
                    availableSites[choice].numberOfClicks++;
                    cout<<"You are now on site: "<< availableSites[choice].link<<endl;
                    for(int i=0; i<numOfSites; i++)
                    {
                        for(int j=0; j<index; j++)
                        {
                            if(sites[i].link==availableSites[j].link)
                            {
                                sites[i].numOfImpressions = availableSites[j].numOfImpressions;
                                sites[i].numberOfClicks = availableSites[j].numberOfClicks;
                            }
                        }
                    }
                    saveData(sites,numOfSites);
                    updateCTR(sites,numOfSites); //update ctr values
                    setScores(sites,numOfSites); //to update scores
                    menu2(availableSites, sites, index, numOfSites);
                }
                else if(choice == 2)
                {
                    search(sites,numOfSites);
                }
                else if(choice==3)
                {
                    //exit function
                    saveData(sites,numOfSites);
                    exit(0);         
                }
            }
            else if(AND==false && OR == false && quotation ==true)
            {
                query=temp;
                query = query.substr(1, query.size() - 2); //to remove quotation marks
                for(int i=0; i<numOfSites; i++)
                {
                    vector<string>::iterator it = sites[i].keywords.begin();
                    while(it!=sites[i].keywords.end())
                    {
                        if(*it == query)
                        {
                            scores[index]=sites[i].score;
                            index++;
                        }
                        it++;
                    }
                }
            
                index = removeDuplicates(scores,index); //to remove any duplicates sites if exists

                mergeSort(scores, index-index, index-1);
        
                for(int i=0; i<index; i++)
                {
                    for(int j=0; j<numOfSites; j++)
                    {
                        if(scores[i]==sites[j].score)
                        {
                            availableSites.push_back(sites[j]);
                        }
                    }
                }
                cout<<"Search results: "<<endl;
                cout<<"----------------"<<endl;
                for(int i=0; i<availableSites.size(); i++)
                {
                    cout<<i+1<<"- "<<availableSites[i].link<<endl;
                    availableSites[i].numOfImpressions = availableSites[i].numOfImpressions+1;
                }
                for(int i=0; i<numOfSites; i++)
                {
                    for(int j=0; j<index; j++)
                    {
                        if(sites[i].link==availableSites[j].link)
                        {
                            sites[i].numOfImpressions = availableSites[j].numOfImpressions;
                            sites[i].numberOfClicks = availableSites[j].numberOfClicks;
                        }
                    }
                }
                saveData(sites,numOfSites);
                updateCTR(sites,numOfSites); //update ctr values
                setScores(sites,numOfSites); //to update scores
                cout<<endl;
                cout<<"What would you link to do?"<<endl;
                cout<<"1- Choose a webpage to open"<<endl;
                cout<<"2- Perform new search"<<endl;
                cout<<"3- Exit"<<endl;
                cout<<"Your choice: ";
                cin>>choice;
                if(choice==1)
                {
                    cout<<"Choose a website: ";
                    cin>>choice;
                    choice=choice-1;
                    availableSites[choice].numberOfClicks++;
                    cout<<"You are now on site: "<< availableSites[choice].link<<endl;
                    for(int i=0; i<numOfSites; i++)
                    {
                        for(int j=0; j<index; j++)
                        {
                            if(sites[i].link==availableSites[j].link)
                            {
                                sites[i].numOfImpressions = availableSites[j].numOfImpressions;
                                sites[i].numberOfClicks = availableSites[j].numberOfClicks;
                            }
                        }
                    }
                    saveData(sites,numOfSites);
                    updateCTR(sites,numOfSites); //update ctr values
                    setScores(sites,numOfSites); //to update scores
                    menu2(availableSites, sites, index, numOfSites);
                }
                else if(choice == 2)
                {
                    search(sites,numOfSites);
                }
                else if(choice==3)
                {
                    //exit function
                    saveData(sites,numOfSites);
                    exit(0);         
                }
            }
        }while(choice!=3);
    }

    void menu1(website *sites, int counterOfSites)
    {
        int choice;
        char n;
        cout<<"Welcome to search engine:"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"What would you like to do?"<<endl;
        cout<<"1- New Search"<<endl;
        cout<<"2- Exit"<<endl;
        cout<<"--------------------------"<<endl;
        cout<<"Your choice: ";
        cin>>choice;
        if(choice==1)
        {
            search(sites,counterOfSites);
        }
        else
        {
            saveData(sites,counterOfSites);
            exit(0);
        }
    }

    int seeVertex()
    {
        return vertexNumber;
    }

    string checkLink()
    {
        return link;
    }

    int vNum()
    {
        return vertexNumber;
    }
};
#endif