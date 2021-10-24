//
// Created by Sarah Ogent on 10/21/21.
//

#include "KCBankReportModify.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;


void openReadFile(vector<KCBankAccounts>& KCBankRecVec, vector<KCBankAccounts>& KCBankRecErrors){
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

    KCBankAccounts tempKCBankRec;
    //vector<KCBankAccounts> KCBankRecVec;
    //vector<KCBankAccounts> KCBankRecErrors;

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
                int accountNum;
                string firstName;
                string lastName;
                float savingsBalance;
                float checkingBalance;

                try{
                    tempKCBankRec.accountNum=stoi(fileData[1]);
                    tempKCBankRec.firstName=fileData[2];
                    tempKCBankRec.lastName=fileData[3];
                    tempKCBankRec.savingsBal=stof(fileData[4]);
                    tempKCBankRec.checkingBal=stof(fileData[5]);







                    KCBankRecVec.push_back(tempKCBankRec);




                }catch(invalid_argument& error1){

                    cout<<firstChar<<", "<<tempKCBankRec.accountNum<<", "<<tempKCBankRec.firstName<<", "<<tempKCBankRec.lastName<<", "<<tempKCBankRec.savingsBal<<", "<<tempKCBankRec.checkingBal;
                    cout<<" has an unidentified error"<<endl;
                    KCBankRecErrors.push_back(tempKCBankRec);
                }


            }




            if(firstChar=="U"){
                int accountNumUpdate;
                string SorC;
                string WorD;
                float moneyAmount;

                accountNumUpdate=stoi(fileData[1]);
                SorC=fileData[2];
                WorD=fileData[3];
                moneyAmount=stof(fileData[4]);

                //cout<<accountNumUpdate<<endl;

                try{
                    for(i=0;i<KCBankRecVec.size();++i) {
                        if (accountNumUpdate ==KCBankRecVec.at(i).accountNum){
                            if(SorC=="S"&&WorD=="W"){
                                tempKCBankRec.savingsBal=KCBankRecVec.at(i).savingsBal-moneyAmount;
                                cout<<fixed<<setprecision(2)<<tempKCBankRec.savingsBal<<endl;
                                //KCBankRecVec.push_back(tempKCBankRec);

                                if(KCBankRecVec.at(i).savingsBal<moneyAmount){
                                    throw runtime_error("Not enough funds");
                                }

                            }

                            if(SorC=="S"&&WorD=="D"){
                                tempKCBankRec.savingsBal=KCBankRecVec.at(i).savingsBal+moneyAmount;
                                cout<<fixed<<setprecision(2)<<tempKCBankRec.savingsBal<<endl;
                                //KCBankRecVec.push_back(tempKCBankRec);

                            }

                            if(SorC=="C"&&WorD=="W"){
                                tempKCBankRec.checkingBal=KCBankRecVec.at(i).checkingBal-moneyAmount;
                                cout<<fixed<<setprecision(2)<<tempKCBankRec.checkingBal<<endl;
                                //KCBankRecVec.push_back(tempKCBankRec);

                                if(tempKCBankRec.checkingBal<moneyAmount){
                                    throw runtime_error("Error: not sufficient funds");
                                }

                            }

                            if(SorC=="C"&&WorD=="D"){
                                tempKCBankRec.checkingBal=KCBankRecVec.at(i).checkingBal+moneyAmount;
                                cout<<fixed<<setprecision(2)<<tempKCBankRec.checkingBal<<endl;
                                //KCBankRecVec.push_back(tempKCBankRec);


                            }


                        }


                    }


                }catch(runtime_error& error3){
                    cout<<error3.what()<<endl;
                    KCBankRecErrors.push_back(tempKCBankRec);

                }

            }



        }
        getline(inFS, line);
    }


    try {
        int p;
        int q;
        int duplicateAccount;
        for (q = 0; q < KCBankRecVec.size(); ++q) {
            for (p = q + 1; p < KCBankRecVec.size(); ++p) {
                if (KCBankRecVec.at(q).accountNum == KCBankRecVec.at(p).accountNum) {
                    throw runtime_error("Error: account already exists");
                    //also make sure to add result to the error vector
                    //duplicateAccount = addAccountNumInt.at(q);
                }
            }
        }
    }catch(runtime_error& error4){
        cout<<error4.what()<<endl;
        KCBankRecErrors.push_back(tempKCBankRec);
    }








}