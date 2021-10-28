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
#include <iomanip>
using namespace std;



void openReadFile(vector<KCBankAccounts>& KCBankRecAdd, vector<KCBankAccounts>& KCBankRecUpdate, vector<string>& KCBankErrorComments){
    ifstream inFS;
    vector<string> fileData;
    string word;
    string line;
    string firstChar;
    int i;
    vector<int>accountExistCheck;
    KCBankAccounts tempKCBankRec;


    //Open file
    inFS.open("/Users/sogent/CLionProjects/KCBankReportLab1/CS201PGM2.csv");
    if (!inFS.is_open()) {
        cout << "Could not open the file \"CS201PGM2.csv\"" << endl;
    }

    //Read file, this reads in the very first line of the data
    getline(inFS, line);
    //first line of data allows us to enter this while loop
    while (inFS.good()) {
        //Assign first character to variable
        firstChar = line.substr(0, 1);

        if (firstChar == "A" || firstChar == "U") {
            //Clear for each loop
            fileData.clear();
            //Copy line into string stream variable
            stringstream inSS(line);

            //Parse line by commas then push into vector
            while(getline(inSS, line, ',')){
                fileData.push_back(line);
            }

            //Organize the data by discriminating by firstChar variable value
            if(firstChar=="A"){

                try{


                    tempKCBankRec.accountNum = stoi(fileData[1]);
                    int accountNum=stoi(fileData[1]);
                    accountExistCheck.push_back(accountNum);

                    tempKCBankRec.firstName=fileData[2];

                    tempKCBankRec.lastName=fileData[3];


                    tempKCBankRec.savingsBal = stof(fileData[4]);


                    tempKCBankRec.checkingBal = stof(fileData[5]);


                    //Error check: checking if the account to be added already exists
                    int p;
                    int q;
                    for (q = 0; q < accountExistCheck.size(); ++q) {
                        for (p = q + 1; p < accountExistCheck.size(); ++p) {
                            if (accountExistCheck.at(q) == accountExistCheck.at(p)) {

                                throw runtime_error(" already exists");
                            }
                        }
                    }


                    //push values into vector that is for adding the accounts
                    KCBankRecAdd.push_back(tempKCBankRec);

                    //push values into vector that will be added but then updated
                    KCBankRecUpdate.push_back(tempKCBankRec);


                }catch(invalid_argument& error1){
                    //cout<<firstChar<<", "<<tempKCBankRec.accountNum<<", "<<tempKCBankRec.firstName<<", "<<tempKCBankRec.lastName<<", "<<tempKCBankRec.savingsBal<<", "<<tempKCBankRec.checkingBal;
                    string unIDError = " has an unidentified error";

                    KCBankErrorComments.push_back(firstChar);
                    KCBankErrorComments.emplace_back(", ");
                    KCBankErrorComments.push_back(to_string(tempKCBankRec.accountNum));
                    KCBankErrorComments.emplace_back(", ");
                    KCBankErrorComments.push_back(tempKCBankRec.firstName);
                    KCBankErrorComments.emplace_back(", ");
                    KCBankErrorComments.push_back(tempKCBankRec.lastName);
                    KCBankErrorComments.push_back(unIDError);
                    KCBankErrorComments.emplace_back("\n");

                }catch(runtime_error& error2){

                    KCBankErrorComments.push_back(to_string(tempKCBankRec.accountNum));
                    KCBankErrorComments.emplace_back(error2.what());
                    KCBankErrorComments.emplace_back("\n");
                }
            }

            //up to this point, we have added the accounts while also stripping away accounts with errors






            if(firstChar=="U") {
                int accountNumUpdate;
                string SorC;
                string WorD;
                float moneyAmount;

                accountNumUpdate = stoi(fileData[1]);

                SorC = fileData[2];

                WorD = fileData[3];

                moneyAmount = stof(fileData[4]);


                    for (i = 0; i < KCBankRecUpdate.size() ; ++i) {

                        try {
                            if (accountNumUpdate == KCBankRecUpdate.at(i).accountNum && (SorC == "S" && WorD == "W")) {

                                if (moneyAmount > KCBankRecUpdate.at(i).savingsBal) {
                                    //update struct members to values that are throwing error
                                    //updated error values will be thrown to catch and added to KCBankRecErrors
                                    tempKCBankRec.accountNum=KCBankRecUpdate.at(i).accountNum;
                                    tempKCBankRec.firstName=KCBankRecUpdate.at(i).firstName;
                                    tempKCBankRec.lastName=KCBankRecUpdate.at(i).lastName;
                                    throw runtime_error(" does not have sufficient funds in savings account");

                                } else {
                                    KCBankRecUpdate.at(i).savingsBal = KCBankRecUpdate.at(i).savingsBal - moneyAmount;
                                }

                            }
                        }catch(runtime_error& error5) {

                            KCBankErrorComments.push_back(to_string(KCBankRecUpdate.at(i).accountNum));
                            KCBankErrorComments.emplace_back(error5.what());
                        }



                        if (accountNumUpdate == KCBankRecUpdate.at(i).accountNum && (SorC == "S" && WorD == "D")) {
                            KCBankRecUpdate.at(i).savingsBal = KCBankRecUpdate.at(i).savingsBal + moneyAmount;
                        }



                        try {
                            if ((accountNumUpdate == KCBankRecUpdate.at(i).accountNum) && (SorC == "C" && WorD == "W")) {

                                if (moneyAmount > KCBankRecUpdate.at(i).checkingBal) {
                                    //update struct members to values that are throwing error
                                    //updated error values will be thrown to catch and added to KCBankRecErrors
                                    tempKCBankRec.accountNum=KCBankRecUpdate.at(i).accountNum;
                                    tempKCBankRec.firstName=KCBankRecUpdate.at(i).firstName;
                                    tempKCBankRec.lastName=KCBankRecUpdate.at(i).lastName;
                                    throw runtime_error(" does not have sufficient funds in checking account");
                                } else {
                                    KCBankRecUpdate.at(i).checkingBal = KCBankRecUpdate.at(i).checkingBal - moneyAmount;
                                }
                            }
                        }catch(runtime_error& error3) {
                            KCBankErrorComments.push_back(to_string(KCBankRecUpdate.at(i).accountNum));
                            KCBankErrorComments.emplace_back(error3.what());
                            KCBankErrorComments.emplace_back("\n");

                        }



                        if (accountNumUpdate == KCBankRecUpdate.at(i).accountNum) {
                            if (SorC == "C" && WorD == "D") {
                                KCBankRecUpdate.at(i).checkingBal = KCBankRecUpdate.at(i).checkingBal + moneyAmount;
                                }
                            }


                    }


                    //Error check: if an account exists or not
                    try {
                        if (find(accountExistCheck.begin(), accountExistCheck.end(), accountNumUpdate) !=
                            accountExistCheck.end()) {
                            continue;
                        } else {
                            throw runtime_error(" does not exist");
                        }
                    }catch(runtime_error& error7){
                       KCBankErrorComments.push_back(to_string(accountNumUpdate));
                       KCBankErrorComments.emplace_back(error7.what());
                       KCBankErrorComments.emplace_back("\n");

                    }


            }




        }

        getline(inFS, line);
    }

    inFS.close();
}




//this function simply adds the accounts from the add account list to the new file
void addAccounts(vector<KCBankAccounts>& addAccountVec){
    ofstream outFS;
    int i;
    outFS.open("KCBankAccountReportSummary.txt");
    if (!outFS.is_open()) {
        cout << "Could not open the file \"KCBankAccountReportSummary.txt\"" << endl;
    }
    while (outFS.is_open()) {
        //initialize account total variable
        float accountAddTotal;

        for(i=0;i<addAccountVec.size();++i){

            outFS << addAccountVec.at(i).accountNum << " ";
            outFS << addAccountVec.at(i).firstName << " ";
            outFS << addAccountVec.at(i).lastName << " ";
            outFS << setprecision(2)<<fixed<<addAccountVec.at(i).savingsBal<< " ";
            outFS << addAccountVec.at(i).checkingBal << " ";
            //add account total values to accounts that were added into the new file
            accountAddTotal = addAccountVec.at(i).savingsBal + addAccountVec.at(i).checkingBal;
            outFS<<accountAddTotal<<endl;


        }

        outFS.close();
    }


}

//this function takes the vector of structs with the updated account information and updates the account record file
void updateAccounts(vector<KCBankAccounts>& KCBankAccountVecToUpdate){
    ifstream inFS;
    vector<string> fileData;
    string word;
    string line;
    string firstChar;
    int i;
    vector<int>accountExistCheck;
    KCBankAccounts tempKCBankRec;

    //Open file
    inFS.open("/Users/sogent/CLionProjects/KCBankReportLab1/CS201PGM2.csv");
    if (!inFS.is_open()) {
        cout << "Could not open the file \"CS201PGM2.csv\"" << endl;
    }

    //Read file, this reads in the very first line of the data
    getline(inFS, line);
    //first line of data allows us to enter this while loop
    while (inFS.good()) {
        //Assign first character to variable
        firstChar = line.substr(0, 1);

        if (firstChar == "A" || firstChar == "U") {
            //Clear for each loop
            fileData.clear();
            //Copy line into string stream variable
            stringstream inSS(line);

            //Parse line by commas then push into vector
            while (getline(inSS, line, ',')) {
                fileData.push_back(line);
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


                for (i = 0; i < KCBankAccountVecToUpdate.size() ; ++i) {

                    try {
                        if (accountNumUpdate == KCBankAccountVecToUpdate.at(i).accountNum && (SorC == "S" && WorD == "W")) {

                            if (moneyAmount > KCBankAccountVecToUpdate.at(i).savingsBal) {
                                //update struct members to values that are throwing error
                                //updated error values will be thrown to catch and added to KCBankRecErrors
                                tempKCBankRec.accountNum=KCBankAccountVecToUpdate.at(i).accountNum;
                                tempKCBankRec.firstName=KCBankAccountVecToUpdate.at(i).firstName;
                                tempKCBankRec.lastName=KCBankAccountVecToUpdate.at(i).lastName;
                                throw runtime_error(" does not have sufficient funds in savings account");

                            } else {
                                KCBankAccountVecToUpdate.at(i).savingsBal = KCBankAccountVecToUpdate.at(i).savingsBal - moneyAmount;
                            }

                        }
                    }catch(runtime_error& error5) {
                        //KCBankAccountErrors.push_back(to_string(KCBankAccountVecToUpdate.at(i).accountNum));
                        //KCBankAccountErrors.emplace_back(error5.what());
                        //KCBankAccountErrors.emplace_back("\n");
                    }



                    if (accountNumUpdate == KCBankAccountVecToUpdate.at(i).accountNum && (SorC == "S" && WorD == "D")) {
                        KCBankAccountVecToUpdate.at(i).savingsBal = KCBankAccountVecToUpdate.at(i).savingsBal + moneyAmount;
                    }



                    try {
                        if ((accountNumUpdate == KCBankAccountVecToUpdate.at(i).accountNum) && (SorC == "C" && WorD == "W")) {

                            if (moneyAmount > KCBankAccountVecToUpdate.at(i).checkingBal) {
                                //update struct members to values that are throwing error
                                //updated error values will be thrown to catch and added to KCBankRecErrors
                                tempKCBankRec.accountNum=KCBankAccountVecToUpdate.at(i).accountNum;
                                tempKCBankRec.firstName=KCBankAccountVecToUpdate.at(i).firstName;
                                tempKCBankRec.lastName=KCBankAccountVecToUpdate.at(i).lastName;
                                throw runtime_error(" does not have sufficient funds in checking account");
                            } else {
                                KCBankAccountVecToUpdate.at(i).checkingBal = KCBankAccountVecToUpdate.at(i).checkingBal - moneyAmount;
                            }
                        }
                    }catch(runtime_error& error3) {
                        //KCBankAccountErrors.push_back(to_string(KCBankAccountVecToUpdate.at(i).accountNum));
                        //KCBankAccountErrors.emplace_back(error3.what());
                        //KCBankAccountErrors.emplace_back("\n");

                    }



                    if (accountNumUpdate == KCBankAccountVecToUpdate.at(i).accountNum) {
                        if (SorC == "C" && WorD == "D") {
                            KCBankAccountVecToUpdate.at(i).checkingBal = KCBankAccountVecToUpdate.at(i).checkingBal + moneyAmount;
                        }
                    }


                }


                //Error check: if an account exists or not
                try {
                    if (find(accountExistCheck.begin(), accountExistCheck.end(), accountNumUpdate) !=
                        accountExistCheck.end()) {
                        continue;
                    } else {
                        throw runtime_error(" does not exist");
                    }
                }catch(runtime_error& error7){
                    //KCBankAccountErrors.push_back(to_string(accountNumUpdate));
                    //KCBankAccountErrors.emplace_back(error7.what());
                    //KCBankAccountErrors.emplace_back("\n");

                }


            }

        }
        getline(inFS, line);



    }
    inFS.close();


}



void printBankAccounts(vector<KCBankAccounts>& updatedAccountRec) {
    ofstream outFS;
    int i;
    outFS.open("KCBankAccountReportSummaryUpdated.txt");
    if (!outFS.is_open()) {
        cout << "Could not open the file \"KCBankAccountReportSummaryUpdated.txt\"" << endl;
    }

    float accountUpdateTotal;
    while (outFS.is_open()) {
        outFS << right<<setw(75)<<"Welcome to Bank of Kansas City" << endl;
        outFS << right<<setw(71)<<"Customer Summary Report" << endl;
        outFS << endl;
        outFS <<right<<setw(12)<< "Bank ID ";
        outFS<<right<<setw(20)<< "First Name ";
        outFS<<right<<setw(20)<< "Last Name ";
        outFS<<right<<setw(21)<< "Savings ";
        outFS<<right<<setw(20)<< "Checking ";
        outFS<<right<<setw(18)<< "Total "<<endl;
        for(i=0;i<updatedAccountRec.size();++i) {
            outFS << right<<setw(11)<<updatedAccountRec.at(i).accountNum << " ";
            outFS<<right<<setw(9)<<" ";
            outFS << left<<setw(20)<<updatedAccountRec.at(i).firstName << " ";
            outFS << left<<setw(18)<<updatedAccountRec.at(i).lastName << " ";
            outFS << right<<setw(11)<<setprecision(2)<<fixed<<updatedAccountRec.at(i).savingsBal<< " ";
            outFS << right<<setw(19)<<updatedAccountRec.at(i).checkingBal << " ";
            accountUpdateTotal = updatedAccountRec.at(i).savingsBal + updatedAccountRec.at(i).checkingBal;
            outFS << right<<setw(17)<<accountUpdateTotal << endl;


        }

        outFS.close();
    }

}


void printErrorLog(vector<string>& KCBankErrorComments){
    ofstream outFS;
    int i;

    //Open file in "append" mode
    outFS.open("/Users/sogent/CLionProjects/KCBankReportLab1/cmake-build-debug/KCBankAccountReportSummaryUpdated.txt", ios::app);
    if (!outFS.is_open()) {
        cout << "Could not open the file \"KCBankAccountReportSummaryUpdated.txt\"" << endl;
    }

    while(outFS.is_open()){
        outFS<<endl;
        outFS<<endl;
        outFS<<"Bank of Kansas City"<<endl;
        outFS<<"Error Log"<<endl;
        for(i=0;i<KCBankErrorComments.size();++i){
            //cout<<KCBankErrorComments.at(i);
            outFS<<KCBankErrorComments.at(i);
        }


        outFS.close();
    }






}