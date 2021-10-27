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



void openReadFile(vector<KCBankAccounts>& KCBankRecAdd, vector<KCBankAccounts>& KCBankRecUpdate, vector<string>& KCBankErrorComments, vector<string>& updateData){
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
                updateData.push_back(fileData[1]);
                updateData.push_back(fileData[2]);
                updateData.push_back(fileData[3]);
                updateData.push_back(fileData[4]);

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

            outFS << addAccountVec.at(i).accountNum << ", ";
            outFS << addAccountVec.at(i).firstName << ", ";
            outFS << addAccountVec.at(i).lastName << ", ";
            outFS << setprecision(2)<<fixed<<addAccountVec.at(i).savingsBal<< ", ";
            outFS << addAccountVec.at(i).checkingBal << ", ";
            //add account total values to accounts that were added into the new file
            accountAddTotal = addAccountVec.at(i).savingsBal + addAccountVec.at(i).checkingBal;
            outFS<<accountAddTotal<<endl;


        }

        outFS.close();
    }


}

//this function takes the vector of structs with the updated account information and updates the account record file
void updateAccounts(vector<KCBankAccounts>& updateAccountVec, vector<string>& KCBankErrorComments){
    fstream inFS, inFS2, outFS;
    int i;
    inFS.open("/Users/sogent/CLionProjects/KCBankReportLab1/cmake-build-debug/KCBankAccountReportSummary.txt");
    if (!inFS.is_open()) {
        cout << "Could not open the file \"KCBankAccountReportSummary.txt\"" << endl;
    }

    outFS.open("KCBankAccountReportSummaryUpdated.txt");

    KCBankAccounts tempKCBankRec;
    vector<string>row;
    string line;
    string word;
    vector<int>accountExistCheck;


    while (!inFS.eof()) {
        row.clear();
        getline(inFS, line, '\n');
        stringstream inSS(line);

        while(getline(inSS, word, ',')){
            row.push_back(word);
        }
        for(i=0;i<row.size();++i){
            cout<<row.at(i)<<endl;
        }
        tempKCBankRec.accountNum=stoi(row[0]);
        accountExistCheck.push_back(tempKCBankRec.accountNum);

        tempKCBankRec.firstName=row[1];
        tempKCBankRec.lastName=row[2];
        tempKCBankRec.savingsBal=stof(row[3]);
        tempKCBankRec.checkingBal=stof(row[4]);
        tempKCBankRec.balanceTotal=stof(row[5]);

        updateAccountVec.push_back(tempKCBankRec);



        /*
        float accountUpdateTotal;

        for(i=0;i<updateAccountVec.size();++i) {
            outFS << updateAccountVec.at(i).accountNum << " ";
            outFS << updateAccountVec.at(i).firstName << " ";
            outFS << updateAccountVec.at(i).lastName << " ";
            outFS << setprecision(2)<<fixed<<updateAccountVec.at(i).savingsBal<< " ";
            outFS << updateAccountVec.at(i).checkingBal << " ";
            accountUpdateTotal = updateAccountVec.at(i).savingsBal + updateAccountVec.at(i).checkingBal;
            outFS << accountUpdateTotal << endl;

        }
        */

        }
    inFS.close();



    //open other file to extract U-line data from
    string firstChar;
    vector<string> fileData;
    string word2;
    string line2;

    inFS2.open("/Users/sogent/CLionProjects/KCBankReportLab1/CS201PGM2.csv");
    if (!inFS2.is_open()) {
        cout << "Could not open the file \"CS201PGM2.csv\"" << endl;
    }
    //Read file, first line by line
    getline(inFS2, line2);
    while (inFS2.good()) {
        //Parse then assign first character to variable
        firstChar = line2.substr(0, 1);

        if (firstChar == "A" || firstChar == "U") {
            //Clear for each loop
            fileData.clear();
            //Copy line into string stream variable
            stringstream inSS2(line2);

            //Parse line elements by commas then push into vector
            while (getline(inSS2, line2, ',')) {
                fileData.push_back(line2);
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


                for (i = 0; i < updateAccountVec.size() ; ++i) {

                    try {
                        if (accountNumUpdate == updateAccountVec.at(i).accountNum && (SorC == "S" && WorD == "W")) {

                            if (moneyAmount > updateAccountVec.at(i).savingsBal) {
                                //update struct members to values that are throwing error
                                //updated error values will be thrown to catch and added to KCBankRecErrors
                                tempKCBankRec.accountNum=updateAccountVec.at(i).accountNum;
                                tempKCBankRec.firstName=updateAccountVec.at(i).firstName;
                                tempKCBankRec.lastName=updateAccountVec.at(i).lastName;
                                throw runtime_error(" does not have sufficient funds in savings account");

                            } else {
                                updateAccountVec.at(i).savingsBal = updateAccountVec.at(i).savingsBal - moneyAmount;
                            }

                        }
                    }catch(runtime_error& error5) {

                        KCBankErrorComments.push_back(to_string(updateAccountVec.at(i).accountNum));
                        KCBankErrorComments.emplace_back(error5.what());
                    }



                    if (accountNumUpdate == updateAccountVec.at(i).accountNum && (SorC == "S" && WorD == "D")) {
                        updateAccountVec.at(i).savingsBal = updateAccountVec.at(i).savingsBal + moneyAmount;
                    }



                    try {
                        if ((accountNumUpdate == updateAccountVec.at(i).accountNum) && (SorC == "C" && WorD == "W")) {

                            if (moneyAmount > updateAccountVec.at(i).checkingBal) {
                                //update struct members to values that are throwing error
                                //updated error values will be thrown to catch and added to KCBankRecErrors
                                tempKCBankRec.accountNum=updateAccountVec.at(i).accountNum;
                                tempKCBankRec.firstName=updateAccountVec.at(i).firstName;
                                tempKCBankRec.lastName=updateAccountVec.at(i).lastName;
                                throw runtime_error(" does not have sufficient funds in checking account");
                            } else {
                                updateAccountVec.at(i).checkingBal = updateAccountVec.at(i).checkingBal - moneyAmount;
                            }
                        }
                    }catch(runtime_error& error3) {
                        KCBankErrorComments.push_back(to_string(updateAccountVec.at(i).accountNum));
                        KCBankErrorComments.emplace_back(error3.what());
                        KCBankErrorComments.emplace_back("\n");

                    }



                    if (accountNumUpdate == updateAccountVec.at(i).accountNum) {
                        if (SorC == "C" && WorD == "D") {
                            updateAccountVec.at(i).checkingBal = updateAccountVec.at(i).checkingBal + moneyAmount;
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
    inFS2.close();



    while(outFS.good()){
        float accountUpdateTotal;

        for(i=0;i<updateAccountVec.size();++i) {
            outFS << updateAccountVec.at(i).accountNum << " ";
            outFS << updateAccountVec.at(i).firstName << " ";
            outFS << updateAccountVec.at(i).lastName << " ";
            outFS << setprecision(2)<<fixed<<updateAccountVec.at(i).savingsBal<< " ";
            outFS << updateAccountVec.at(i).checkingBal << " ";
            accountUpdateTotal = updateAccountVec.at(i).savingsBal + updateAccountVec.at(i).checkingBal;
            outFS << accountUpdateTotal << endl;

        }





        outFS.close();
    }








}



void printBankAccounts(vector<KCBankAccounts>& updatedAccountRec) {
    ofstream outFS;
    int i;
    outFS.open("KCBankAccountReportSummary.txt");
    if (!outFS.is_open()) {
        cout << "Could not open the file \"KCBankAccountReportSummary.txt\"" << endl;
    }

    float accountUpdateTotal;
    while (outFS.is_open()) {
        outFS << "Welcome to Bank of Kansas City" << endl;
        outFS << "Customer Summary Report" << endl;
        outFS << endl;
        outFS << "Bank ID: " << "First Name: " << "Last Name: " << "Savings: " << "Checking: " << "Total: " << endl;
        for(i=0;i<updatedAccountRec.size();++i) {
            outFS << updatedAccountRec.at(i).accountNum << " ";
            outFS << updatedAccountRec.at(i).firstName << " ";
            outFS << updatedAccountRec.at(i).lastName << " ";
            outFS << setprecision(2)<<fixed<<updatedAccountRec.at(i).savingsBal<< " ";
            outFS << updatedAccountRec.at(i).checkingBal << " ";
            accountUpdateTotal = updatedAccountRec.at(i).savingsBal + updatedAccountRec.at(i).checkingBal;
            outFS << accountUpdateTotal << endl;

        }





        outFS.close();
    }
}


void printErrorLog(vector<string>& KCBankErrorComments){
int i;
for(i=0;i<KCBankErrorComments.size();++i){
    cout<<KCBankErrorComments.at(i);
}




}