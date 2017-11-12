// Development environment: Ubuntu 16.04 - ITU SSH servers
// Tested in gcc 4.9.2 & 4.8.5 - ITU SSH servers

// To compile: g++ main.cpp -o main.exe
// To run: ./main.exe input.txt

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>

using namespace std;

int main ( int argc, char *argv[] ){
    //cout << argv[1] << endl;
    string line;
    ifstream myfile;

    //VECTORS
    vector<int> allocVector;
    vector<int> maxRequiredVector;
    vector<int> remainVector;

    //VALUES
    int allocValue;
    int maxValue;
    int resource;
    int freeValue;
    int numberOfLines;

    myfile.open(argv[1]);

    // If it opens file successfuly, it appends values to appropriate vectors.
    if(myfile){
    getline(myfile,line);
    if ( ! (istringstream(line) >> resource) ) resource = 0;
    //cout << resource << endl;
    while (getline(myfile,line)){
        unsigned pos = line.find(" ");
        if ( ! (istringstream(line.substr(0,pos)) >> allocValue) ) allocValue = 0;
        allocVector.push_back(allocValue);
        // cout << allocValue << endl;
        pos = line.find(" ");
        if ( ! (istringstream(line.substr(pos+1)) >> maxValue) ) maxValue = 0;
        maxRequiredVector.push_back(maxValue);
        // cout << maxValue << endl;
        remainVector.push_back(maxValue - allocValue);
        //cout << maxValue - allocValue << endl;
    }
}
    
//================================================================================
// Sums allocated values then subtracts from resource to find "WORK"
//================================================================================
int sumOfAlloc = accumulate(allocVector.begin(), allocVector.end(), 0);
freeValue = resource - sumOfAlloc;

//================================================================================
// The part of the program which provides safe sequence
//================================================================================

int size = remainVector.size();
bool finish[size];
vector<int> safeSequence;

    for(int i=0; i<size; ++i){
        for (int p = 0; p < size; p++)
        {
            if (finish[p] == 0)
            {    
                if(remainVector[p] <= freeValue){
                    safeSequence.push_back(p);
                    freeValue += allocVector[p];
                    finish[p] = 1;
                }
            }
        }    
    }

    if (safeSequence.size() != size){
        cout << "System is not in safe state ";
    }else{
        cout << "Input state is SAFE." << endl;
        cout << "A correct process execution order is ";
        for (int i = 0; i < safeSequence.size(); i++){
            cout << safeSequence[i] << " ";
        }      
    } cout << endl;

//================================================================================
// The part of the program which gets user input requests.
//================================================================================

    int procID = 0;
    int requestedRec = 0;

    while(procID!=-1){
        cout << "Enter a process id to simulate a resource request."<< endl;
        cin >> procID;
        cout << "How many resources does process " << procID << " request?" << endl;
        cin >> requestedRec;

        if(remainVector[procID] <= requestedRec){
            cout << "Request CAN be granted." << endl;
        }else{
            cout << "Request CANNOT be granted." << endl;
        }
    }
    return 0;
}

// OMER DOGAN 150130208
// https://github.com/Omerdogan3