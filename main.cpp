#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

struct KCBankAccounts{
    int accountNum;
    string firstName;
    string lastName;
    float savingsBal;
    float checkingBal;

};

int main() {
    ifstream inFS;
    vector<string> fileData;
    string word;
    string line;
    int i;
    vector<string> lineAData;
    vector<string> lineUData;

    inFS.open("/Users/sogent/CLionProjects/KCBankReportLab1/CS201PGM2.csv");
    if (!inFS.is_open()) {
        cout << "Could not open the file \"CS201PGM2.csv\"" << endl;
    }


    getline(inFS, line); //reading in line by line
    while (inFS.good()) {         // Loop while input data exists
        //++nRows;
        while(line.find(',') != string::npos) { //in a line
            word = line.substr(0, line.find(',')); //find a member (word) of that line
            //start error checking by dividing up by A vs U


            fileData.push_back(word); //add that word to the vector
            line = line.substr(line.find(',') + 1); //updates line as looking for next word?
        }
        fileData.push_back(line);


        getline(inFS, line); //onto the next line
    }


    //checking for initial vector (fileData) output
    for(i=0;i<fileData.size();++i){
        cout<<fileData.at(i)<<endl;
    }



    //parting data from fileData vector into lineAData
    //finds any "A" element then adds the proceeding 5 elements to lineAData
    for(i=0;i<fileData.size();++i){
        if(fileData.at(i)=="A"){
            lineAData.push_back(fileData.at(i+1));
            lineAData.push_back(fileData.at(i+2));
            lineAData.push_back(fileData.at(i+3));
            lineAData.push_back(fileData.at(i+4));
            lineAData.push_back(fileData.at(i+5));

        }
    }

    cout<<endl;

    //checking lineAData output
    for(i=0;i<lineAData.size();++i){
        cout<<lineAData.at(i)<<endl;
    }

    cout<<endl;

    //parting data from fileData vector into lineUData vector
    //finds any "U" element then adds the proceeding 4 elements to lineUData
    for(i=0;i<fileData.size();++i){
        if(fileData.at(i)=="U"){
            lineUData.push_back(fileData.at(i+1));
            lineUData.push_back(fileData.at(i+2));
            lineUData.push_back(fileData.at(i+3));
            lineUData.push_back(fileData.at(i+4));

        }
    }

    //checking lineUData output
    for(i=0;i<lineUData.size();++i){
        cout<<lineUData.at(i)<<endl;
    }

    //ok whats next tho
    //start error checking


    ///////ERROR CHECKING ROUND 1: IF AN ACCOUNT FROM UPDATE EXISTS IN LIST OF ACCOUNTS TO ADD
    //////STILL NEED TO FIGURE OUT WHAT TO DO WITH RESULTS

    //check if an account even exists or not
    //sort then loop through?
    //put all 'add' account numbers in their own vector
    vector<string> addAccountNum;
    for(i=0;i<lineAData.size();i+=5){
        addAccountNum.push_back(lineAData.at(i));
    };
    cout<<endl;
    cout<<endl;

    //check addAccountNum output
    for(i=0;i<addAccountNum.size();++i){
       cout<< addAccountNum.at(i)<<endl;
    }

    cout<<endl;

    //put all 'update' account numbers in their own vector
    vector<string> updateAccountNum;
    for(i=0;i<lineUData.size();i+=4){
        updateAccountNum.push_back(lineUData.at(i));

    }

    //check updateAccountNum output
    for(i=0;i<updateAccountNum.size();++i){
        cout<<updateAccountNum.at(i)<<endl;
    }

    cout<<endl;
    //convert the updateAccountNum and addAccountNum from string to int
    //declare new vectors
    vector<int>addAccountNumInt;
    vector<int>updateAccountNumInt;

    //iterate through updateAccountNum and addAccountNum string vectors and add to new int vectors
    for(i=0;i<addAccountNum.size();++i){
        addAccountNumInt.push_back(stoi(addAccountNum.at(i)));
    }

    //check addAccountNumInt output
    for(int x:addAccountNumInt){
        cout<<x<<endl;
    }

    cout<<endl;

    for(i=0;i<updateAccountNum.size();++i){
        updateAccountNumInt.push_back(stoi(updateAccountNum.at(i)));
    }

    //check updateAccountNumInt output
    for(int y:updateAccountNumInt){
        cout<<y<<endl;
    }
cout<<endl;

    //sort addAccountNumInt and updateAccountNumInt vectors
    sort(updateAccountNumInt.begin(), updateAccountNumInt.end());
    for(int z:updateAccountNumInt){
        cout<<z<<endl;
    }

    cout<<endl;
   sort(addAccountNumInt.begin(), addAccountNumInt.end());
    for(int j:addAccountNumInt){
        cout<<j<<endl;
    }

    cout<<endl;
    //now checking if an account exists or not by comparing the two vectors

    //initialize vectors which will hold results
    vector<int>nonAccounts;
    vector<int>verifiedAccounts;

    for(i=0;i<updateAccountNumInt.size();++i){
        int key=updateAccountNumInt.at(i);

        if(find(addAccountNumInt.begin(), addAccountNumInt.end(), key) != addAccountNumInt.end()){
            verifiedAccounts.push_back(key);
        }else{
            //throw a runtime_error here ("Error: account does not exist")
            //also put result in error vector
            nonAccounts.push_back(key);
        }

    }

    //accounts not found
    cout<<endl;
    for(int m:nonAccounts){
        cout<<m<<endl;
    }

    //accounts found
    cout<<endl;
    for(int n:verifiedAccounts){
        cout<<n<<endl;
    }
    cout<<endl;


    ///////ERROR CHECKING ROUND 2: IF AN ACCOUNT FROM THE ADD ACCOUNTS LIST IS REPEATED

    //checking output of sorted add account numbers
    for(int xyz:addAccountNumInt){
        cout<<xyz<<endl;
    }

    int p;
    int q;
    int duplicateAccount;
    for(q=0;q<addAccountNumInt.size();++q){
        for(p=q+1;p<addAccountNumInt.size();++p){
            if(addAccountNumInt.at(q)==addAccountNumInt.at(p)){
                //throw a runtime_error exception here ("Error: account already exists")
                //also make sure to add result to the error vector
                duplicateAccount=addAccountNumInt.at(q);
            }
        }

    }

    cout<<endl;
    cout<<duplicateAccount;
    cout<<endl;
    cout<<endl;


    ////////ERROR CHECKING ROUND 3: CONVERTING REST OF DATA TYPES, THIS FINNA GET MESSY
    //add account numbers and update account numbers already have data types changed
    //and are in their respective temp vectors (addAccountNumInt and updateAccountNumInt)
    //need to change
    // ADD: firstName (string) [6]X, lastname (string) [7]X, savingsBal (float) [8], checkingBal (float) [9]
    //UPDATE:  saveOrChecking (string) [5], withdrawOrDeposit (string) [6], withdrawOrDepositAmt (float) [7]

    //recall: vector<string> lineAData and vector<string> lineUData

    //put all firstName var in own vector (lineAData)
    vector<string>firstName;

    //every 2nd element
    for(i=1;i<lineAData.size();i+=5){
        firstName.push_back(lineAData.at(i));
    }

    //check firstName vector output
    for(string abc:firstName){
        cout<<abc<<endl;
    }

    cout<<endl;

    //put all lastName var in own vector (lineAData)
    vector<string> lastNameStr;

    //every 3rd element
    for(i=2;i<lineAData.size();i+=5){
        lastNameStr.push_back(lineAData.at(i));

    }

    //check lastName vector output
    for(string jkl: lastNameStr){
        cout<<jkl<<endl;
    }
    cout<<endl;

    //put all of savingsBal in own vector (lineAData)
    vector<string>savingsBalStr;
    vector<float>savingsBalFloat;

    for(i=3;i<lineAData.size();i+=5){
        savingsBalStr.push_back(lineAData.at(i));
    }

    //check output
    for(string mno: savingsBalStr){
        cout<<mno<<endl;
    }
    cout<<endl;

    //convert from string to float - need error checking with this
    //stof and lineAData
    //still need to figure out how to add stof: no conversion error to error vector
    try{
        for(i=3;i<lineAData.size();i+=5){
            savingsBalFloat.push_back(stof(lineAData.at(i)));

        }





    }catch(invalid_argument& hi){
        //error is caught, value to cause error needs to be put in error vector
        savingsBalStr.push_back(lineAData.at(i));

    }
    cout<<endl;

    for(string hi:savingsBalStr){
        cout<<hi<<endl;
    }
cout<<endl;

    //check savingsBalFloat output
    for(float pqr:savingsBalFloat){
        cout<<pqr<<endl;
    }

































    return 0;
}
