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



void openReadFile(vector<KCBankAccounts>& KCBankRecVec, vector<KCBankAccounts>& KCBankRecErrors, vector<KCBankAccounts>& KCBankRecUpdate){
    ifstream inFS;
    vector<string> fileData;
    string word;
    string line;
    string firstChar;
    int i;
    vector<string> lineAData;
    vector<string> lineUData;
    vector<int> duplicateAccountError;
    vector<float> dataTypeError;
    vector<int>accountExistCheck;
    vector<int>accountExistCheckUpdate;
    vector<int>accountExistErrors;

    KCBankAccounts tempKCBankRec;
    KCBankAccounts tempKCBankRec2Update;


    inFS.open("/Users/sogent/CLionProjects/KCBankReportLab1/CS201PGM2.csv");
    if (!inFS.is_open()) {
        cout << "Could not open the file \"CS201PGM2.csv\"" << endl;
    }

    getline(inFS, line);
    while (inFS.good()) {
        firstChar = line.substr(0, 1);
        if (firstChar == "A" || firstChar == "U") {
            fileData.clear();
            stringstream inSS(line);

            while(getline(inSS, line, ',')){
                fileData.push_back(line);

            }

            if(firstChar=="A"){


                try{

                    tempKCBankRec.accountNum=stoi(fileData[1]);
                    accountExistCheck.push_back(tempKCBankRec.accountNum);


                    tempKCBankRec.firstName=fileData[2];


                    tempKCBankRec.lastName=fileData[3];



                    tempKCBankRec.savingsBal = stof(fileData[4]);



                    tempKCBankRec.checkingBal = stof(fileData[5]);





                    KCBankRecVec.push_back(tempKCBankRec);





                        int p;
                        int q;
                        int duplicateAccount;
                        for (q = 0; q < KCBankRecVec.size(); ++q) {
                            for (p = q + 1; p < KCBankRecVec.size(); ++p) {
                                if (KCBankRecVec.at(q).accountNum == KCBankRecVec.at(p).accountNum) {
                                    throw runtime_error("already exists");
                                    //also make sure to add result to the error vector
                                    //duplicateAccount = addAccountNumInt.at(q);
                                }
                            }
                        }








                }catch(invalid_argument& error1){
                    cout<<firstChar<<", "<<tempKCBankRec.accountNum<<", "<<tempKCBankRec.firstName<<", "<<tempKCBankRec.lastName<<", "<<tempKCBankRec.savingsBal<<", "<<tempKCBankRec.checkingBal;

                    cout<<" has an unidentified error"<<endl;
                    KCBankRecErrors.push_back(tempKCBankRec);
                }catch(runtime_error& error2){
                    cout<<tempKCBankRec.accountNum <<" "<<error2.what()<<endl;
                    KCBankRecErrors.push_back(tempKCBankRec);

                }


            }




            if(firstChar=="U") {
                int accountNumUpdate;
                string SorC;
                string WorD;
                float moneyAmount;

                accountNumUpdate = stoi(fileData[1]);
                SorC = fileData[2];
                WorD = fileData[3];
                moneyAmount = stof(fileData[4]);












                    for (i = 0; i < KCBankRecVec.size() ; ++i) {

                        try {

                            if (accountNumUpdate == KCBankRecVec.at(i).accountNum && (SorC == "S" && WorD == "W")) {

                                if (moneyAmount > KCBankRecVec.at(i).savingsBal) {
                                    //update struct members to values that are throwing error
                                    //updated error values will be thrown to catch and added to KCBankRecErrors
                                    tempKCBankRec.accountNum=KCBankRecVec.at(i).accountNum;
                                    tempKCBankRec.firstName=KCBankRecVec.at(i).firstName;
                                    tempKCBankRec.lastName=KCBankRecVec.at(i).lastName;
                                    throw runtime_error("does not have sufficient funds in savings account");

                                } else {
                                    KCBankRecVec.at(i).savingsBal = KCBankRecVec.at(i).savingsBal - moneyAmount;
                                }

                            }
                        }catch(runtime_error& error) {
                            cout<<KCBankRecVec.at(i).accountNum<<", "<<KCBankRecVec.at(i).firstName<<", "<<KCBankRecVec.at(i).lastName<<" ";
                            cout << error.what() << endl;
                            KCBankRecErrors.push_back(tempKCBankRec);
                        }



                        try {
                            if (accountNumUpdate == KCBankRecVec.at(i).accountNum && (SorC == "S" && WorD == "D")) {

                                if (accountNumUpdate != KCBankRecVec.at(i).accountNum) {
                                    throw runtime_error("does not exist");
                                }

                                KCBankRecVec.at(i).savingsBal = KCBankRecVec.at(i).savingsBal + moneyAmount;

                            }
                        }catch(runtime_error& error2) {
                            cout<<KCBankRecVec.at(i).accountNum<<", "<<KCBankRecVec.at(i).firstName<<", "<<KCBankRecVec.at(i).lastName<<" ";
                            cout << error2.what() << endl;
                            KCBankRecErrors.push_back(tempKCBankRec);
                        }



                        try {
                            if ((accountNumUpdate == KCBankRecVec.at(i).accountNum) && (SorC == "C" && WorD == "W")) {

                                if (moneyAmount > KCBankRecVec.at(i).checkingBal) {
                                    //update struct members to values that are throwing error
                                    //updated error values will be thrown to catch and added to KCBankRecErrors
                                    tempKCBankRec.accountNum=KCBankRecVec.at(i).accountNum;
                                    tempKCBankRec.firstName=KCBankRecVec.at(i).firstName;
                                    tempKCBankRec.lastName=KCBankRecVec.at(i).lastName;
                                    throw runtime_error("does not have sufficient funds in checking account");
                                } else {
                                    KCBankRecVec.at(i).checkingBal = KCBankRecVec.at(i).checkingBal - moneyAmount;
                                }


                            }
                        }catch(runtime_error& error3) {
                            cout<<KCBankRecVec.at(i).accountNum<<", "<<KCBankRecVec.at(i).firstName<<", "<<KCBankRecVec.at(i).lastName<<" ";
                            cout << error3.what() << endl;
                            KCBankRecErrors.push_back(tempKCBankRec);
                        }


                            if (accountNumUpdate == KCBankRecVec.at(i).accountNum) {
                                if (SorC == "C" && WorD == "D") {
                                    KCBankRecVec.at(i).checkingBal = KCBankRecVec.at(i).checkingBal + moneyAmount;
                                }
                            }



                    }



                    try {
                        if (find(accountExistCheck.begin(), accountExistCheck.end(), accountNumUpdate) !=
                            accountExistCheck.end()) {
                            continue;
                        } else {
                            throw runtime_error("does not exist");

                        }
                    }catch(runtime_error& error7){
                        cout<<accountNumUpdate<<" "<<error7.what()<<endl;
                    }







            }



        }

        getline(inFS, line);
    }

    inFS.close();







}



void addAccounts(vector<KCBankAccounts>& addAccountVec, vector<KCBankAccounts>& accountErrors){
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
        outFS<<endl;
        outFS<<endl;

        for(i=0;i<accountErrors.size();++i){
            outFS<<accountErrors.at(i).accountNum<<" ";
            outFS<<accountErrors.at(i).firstName<<" ";
            outFS<<accountErrors.at(i).lastName<<" ";
        }


        outFS.close();

    }
    outFS.close();

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