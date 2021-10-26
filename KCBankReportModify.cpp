//
// Created by Sarah Ogent on 10/21/21.
//

#include "KCBankReportModify.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>
using namespace std;



void openReadFile(vector<KCBankAccounts>& KCBankRecAdd, vector<KCBankAccounts>& KCBankRecErrors, vector<KCBankAccounts>& KCBankRecUpdate){
    ifstream inFS;
    vector<string> fileData;
    string word;
    string line;
    string firstChar;
    int i;
    vector<string> lineAData;
    vector<string> lineUData;
    vector<int> duplicateAccountError;
    vector<int>accountExistCheck;
    vector<int>accountExistCheckUpdate;
    vector<int>accountExistErrors;

    KCBankAccounts tempKCBankRec;


    //Open file
    inFS.open("/Users/sogent/CLionProjects/KCBankReportLab1/CS201PGM2.csv");
    if (!inFS.is_open()) {
        cout << "Could not open the file \"CS201PGM2.csv\"" << endl;
    }

    //Read file, first line by line
    getline(inFS, line);
    while (inFS.good()) {
        //Parse then assign first character to variable
        firstChar = line.substr(0, 1);

        if (firstChar == "A" || firstChar == "U") {
            //Clear for each loop
            fileData.clear();
            //Copy line into string stream variable
            stringstream inSS(line);

            //Parse line elements by commas then push into vector
            while(getline(inSS, line, ',')){
                fileData.push_back(line);
            }

            //Organize the data by discriminating by firstChar variable
            if(firstChar=="A"){

                try{

                    tempKCBankRec.accountNum = stoi(fileData[1]);
                    int accountNum=stoi(fileData[1]);
                    accountExistCheck.push_back(accountNum);

                    tempKCBankRec.firstName=fileData[2];

                    tempKCBankRec.lastName=fileData[3];

                    tempKCBankRec.savingsBal = stof(fileData[4]);

                    tempKCBankRec.checkingBal = stof(fileData[5]);


                    int p;
                    int q;
                    for (q = 0; q < accountExistCheck.size(); ++q) {
                        for (p = q + 1; p < accountExistCheck.size(); ++p) {
                            if (accountExistCheck.at(q) == accountExistCheck.at(p)) {

                                throw runtime_error("already exists");
                            }
                        }
                    }


                    KCBankRecAdd.push_back(tempKCBankRec);


                }catch(invalid_argument& error1){
                    cout<<firstChar<<", "<<tempKCBankRec.accountNum<<", "<<tempKCBankRec.firstName<<", "<<tempKCBankRec.lastName<<", "<<tempKCBankRec.savingsBal<<", "<<tempKCBankRec.checkingBal;

                    cout<<" has an unidentified error"<<endl;
                    KCBankRecErrors.push_back(tempKCBankRec);
                }catch(runtime_error& error2){
                    cout<<tempKCBankRec.accountNum <<" "<<error2.what()<<endl;
                    KCBankRecErrors.push_back(tempKCBankRec);

                }
            }





            //copy KCBankRecAdd vector values to KCBankRecUpdate values
            KCBankRecUpdate=KCBankRecAdd;

            if(firstChar=="U") {
                int accountNumUpdate;
                string SorC;
                string WorD;
                float moneyAmount;

                accountNumUpdate = stoi(fileData[1]);

                SorC = fileData[2];

                WorD = fileData[3];

                moneyAmount = stof(fileData[4]);


                    for (i = 0; i < KCBankRecAdd.size() ; ++i) {

                        try {
                            if (accountNumUpdate == KCBankRecUpdate.at(i).accountNum && (SorC == "S" && WorD == "W")) {

                                if (moneyAmount > KCBankRecAdd.at(i).savingsBal) {
                                    //update struct members to values that are throwing error
                                    //updated error values will be thrown to catch and added to KCBankRecErrors
                                    tempKCBankRec.accountNum=KCBankRecAdd.at(i).accountNum;
                                    tempKCBankRec.firstName=KCBankRecAdd.at(i).firstName;
                                    tempKCBankRec.lastName=KCBankRecAdd.at(i).lastName;
                                    throw runtime_error("does not have sufficient funds in savings account");

                                } else {
                                    KCBankRecAdd.at(i).savingsBal = KCBankRecAdd.at(i).savingsBal - moneyAmount;
                                }

                            }
                        }catch(runtime_error& error) {
                            cout<<KCBankRecAdd.at(i).accountNum<<", "<<KCBankRecAdd.at(i).firstName<<", "<<KCBankRecAdd.at(i).lastName<<" ";
                            cout << error.what() << endl;
                            KCBankRecErrors.push_back(tempKCBankRec);
                        }



                        try {
                            if (accountNumUpdate == KCBankRecAdd.at(i).accountNum && (SorC == "S" && WorD == "D")) {
                                KCBankRecAdd.at(i).savingsBal = KCBankRecAdd.at(i).savingsBal + moneyAmount;
                            }
                        }catch(runtime_error& error2) {
                            cout<<KCBankRecAdd.at(i).accountNum<<", "<<KCBankRecAdd.at(i).firstName<<", "<<KCBankRecAdd.at(i).lastName<<" ";
                            cout << error2.what() << endl;
                            KCBankRecErrors.push_back(tempKCBankRec);
                        }



                        try {
                            if ((accountNumUpdate == KCBankRecAdd.at(i).accountNum) && (SorC == "C" && WorD == "W")) {

                                if (moneyAmount > KCBankRecAdd.at(i).checkingBal) {
                                    //update struct members to values that are throwing error
                                    //updated error values will be thrown to catch and added to KCBankRecErrors
                                    tempKCBankRec.accountNum=KCBankRecAdd.at(i).accountNum;
                                    tempKCBankRec.firstName=KCBankRecAdd.at(i).firstName;
                                    tempKCBankRec.lastName=KCBankRecAdd.at(i).lastName;
                                    throw runtime_error("does not have sufficient funds in checking account");
                                } else {
                                    KCBankRecAdd.at(i).checkingBal = KCBankRecAdd.at(i).checkingBal - moneyAmount;
                                }
                            }
                        }catch(runtime_error& error3) {
                            cout<<KCBankRecAdd.at(i).accountNum<<", "<<KCBankRecAdd.at(i).firstName<<", "<<KCBankRecAdd.at(i).lastName<<" ";
                            cout << error3.what() << endl;
                            KCBankRecErrors.push_back(tempKCBankRec);
                        }



                        if (accountNumUpdate == KCBankRecAdd.at(i).accountNum) {
                            if (SorC == "C" && WorD == "D") {
                                KCBankRecAdd.at(i).checkingBal = KCBankRecAdd.at(i).checkingBal + moneyAmount;
                                }
                            }


                    }


                    //Error check: if an account exists or not
                    try {
                        if (find(accountExistCheck.begin(), accountExistCheck.end(), accountNumUpdate) !=
                            accountExistCheck.end()) {
                            continue;
                        } else {
                            throw runtime_error("does not exist");
                        }
                    }catch(runtime_error& error7){
                        accountExistErrors.push_back(accountNumUpdate);
                        cout<<accountNumUpdate<<" "<<error7.what()<<endl;
                    }


            }



        }

        getline(inFS, line);
    }

    inFS.close();
}





void addAccounts(vector<KCBankAccounts>& addAccountVec){
    ofstream outFS;
    int i;
    outFS.open("KCBankAccountReportSummary.txt");
    if (!outFS.is_open()) {
        cout << "Could not open the file \"KCBankAccountReportSummary.txt\"" << endl;
    }
    while (outFS.is_open()) {
        for(i=0;i<addAccountVec.size();++i){

            outFS << addAccountVec.at(i).accountNum << " ";
            outFS << addAccountVec.at(i).firstName << " ";
            outFS << addAccountVec.at(i).lastName << " ";
            outFS << setprecision(2)<<fixed<<addAccountVec.at(i).savingsBal<< " ";
            outFS << addAccountVec.at(i).checkingBal << " " << endl;


        }


        outFS.close();
    }


}

void updateAccounts(vector<KCBankAccounts>& accountUpdates, vector<KCBankAccounts>& accountErrors){
    ifstream inFS;
    string line;
    int i;
    inFS.open("KCBankAccountReportSummary.txt");
    if (!inFS.is_open()) {
        cout << "Could not open the file \"KCBankAccountReportSummary.txt\"" << endl;
    }
    getline(inFS, line);
    while (inFS.good()) {
        stringstream inSS;
        string accountLine;
        accountLine =line.substr(0, line.length());




        cout<<accountLine<<endl;
        for(i=0;i<accountUpdates.size();++i){
            //string accountNum = line.substr(0, accountUpdates.at(i).accountNum);
            string key=to_string(accountUpdates.at(i).accountNum);

        }



        getline(inFS, line);
    }
    inFS.close();


}

vector<struct KCBankAccountRecords>printBankAccounts(vector<KCBankAccountRecords>& addBankRec) {
    ofstream outFS;
    vector<string> newAddBankRec;
    int i;
    outFS.open("KCBankAccountReportSummary.txt");
    if (!outFS.is_open()) {
        cout << "Could not open the file \"KCBankAccountReportSummary.txt\"" << endl;
    }

    while (outFS.is_open()) {
        outFS << "Welcome to Bank of Kansas City" << endl;
        outFS << "Customer Summary Report" << endl;
        outFS << endl;
        outFS << "Bank ID: " << "First Name: " << "Last Name: " << "Savings: " << "Checking: " << "Total: " << endl;
        /*
        for (i = 0; i < addBankRec.size(); ++i) {

            outFS << to_string(addBankRec.at(i).accountNum) << " ";
            outFS << addBankRec.at(i).firstName << " ";
            outFS << addBankRec.at(i).lastName << " ";
            outFS << to_string(addBankRec.at(i).savingsBal) << " ";
            outFS << to_string(addBankRec.at(i).checkingBal) << " " << endl;


        }
        outFS.close();
         */


    }
}