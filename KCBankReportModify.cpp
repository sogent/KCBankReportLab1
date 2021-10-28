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

/*
 * Precondition:
 * 1.expects csv file with data according to following template:
 * A,accountNum,firstName,lastName,savingsAccountBalance,checkingAccountBalance
 * U,accountNum,S/C,W/D,moneyAmount
 * 2.expects 3 empty vectors of struct type KCBankAccounts
 *
 * Postcondition:
 * 1.file will be parsed through and checked for errors including data type conversion errors, account duplication errors,
 * account validation errors (if an account exists or not) and account overdrawn errors (if an account has enough funds to
 * withdraw specified amount)
 * 2.KCBankRecAdd vector will be loaded with error-free data of list of accounts that need to be added
 * 3.KCBankRecUpdate vector will be loaded with error-free data of list of accounts that have been successfully updated
 * 4.KCBankErrorComments will be loaded with the values of the members of the structs that had caused errors along
 * with their respective error comments
 */
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

                //begin assigning values to members of structs
                try{

                    tempKCBankRec.accountNum = stoi(fileData[1]);

                    //this vector is used for error checking, specifically
                    //if an account does or does not exist in the list of added accounts
                    // from the list of accounts to be updated
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

                    //Now that the struct members have been assigned values, we're
                    //pushing these values (specifically, from the list of accounts to add) into a vector
                    KCBankRecAdd.push_back(tempKCBankRec);


                    //sorting the vector of structs from the list of accounts to add
                    sort(KCBankRecAdd.begin(), KCBankRecAdd.end(), [](KCBankAccounts a, KCBankAccounts b){
                        return a.accountNum < b.accountNum;
                    });



                    //now pushing values into vector that will be used solely for error tracking,
                    //trying to break up putting errors and their comments in error vector in two different
                    //functions yielded unwanted results
                    KCBankRecUpdate.push_back(tempKCBankRec);

                //data type conversion failure catch
                }catch(invalid_argument& error1){
                    //setting up specific error message for data type conversion failure
                    string unIDError = " has an unidentified error";

                    //adding what error was caught to an error vector of strings
                    //so that comments specific to error and what value is throwing said
                    //error can also be passed to vector
                    KCBankErrorComments.push_back(firstChar);
                    KCBankErrorComments.emplace_back(", ");
                    KCBankErrorComments.push_back(to_string(tempKCBankRec.accountNum));
                    KCBankErrorComments.emplace_back(", ");
                    KCBankErrorComments.push_back(tempKCBankRec.firstName);
                    KCBankErrorComments.emplace_back(", ");
                    KCBankErrorComments.push_back(tempKCBankRec.lastName);
                    KCBankErrorComments.push_back(unIDError);
                    KCBankErrorComments.emplace_back("\n");

                    //if an account from the add accounts list already exists error catch
                }catch(runtime_error& error2){
                    //adding what error was caught to an error vector of strings
                    //so that comments specific to error and what value is throwing said
                    //error can also be passed to vector
                    KCBankErrorComments.push_back(to_string(tempKCBankRec.accountNum));
                    KCBankErrorComments.emplace_back(error2.what());
                    KCBankErrorComments.emplace_back("\n");
                }
            }

            //Up to this point, we have pushed the accounts from the list of accounts to be added
            // to a vector of structs while also stripping away accounts
            // with errors such as unidentified errors (data type conversion errors) and if an account from the
            //add accounts list has been repeated and placed these errors into a vector of errors.
            //We have also sorted the vector of structs so that the accounts will now be in
            //ascending order according to their account number.



            //The rest of this code is used for purposes of catching the rest of the errors
            //associated with the list of accounts needing to be updated

            //Organize the data by discriminating by firstChar variable value
            if(firstChar=="U") {

                //Now assigning the data from the lines beginning with U
                //with their own variables so that we may use that information
                //to properly update the vector struct members
                int accountNumUpdate;
                string SorC;
                string WorD;
                float moneyAmount;

                accountNumUpdate = stoi(fileData[1]);

                SorC = fileData[2];

                WorD = fileData[3];

                moneyAmount = stof(fileData[4]);

                    //lines of code within the loop of KCBankRecUpdate so that the value of the members accountNum
                    // from the vector of structs can simultaneously be compared to the value of accountNumUpdate
                    // according to the current loop
                    for (i = 0; i < KCBankRecUpdate.size() ; ++i) {

                        //Error check: making sure the account that needs to be updated has enough
                        //funds to be withdrawn from savings account
                        //if not, the value throwing error will be put into KCBankErrorComments vector
                        try {
                            if (accountNumUpdate == KCBankRecUpdate.at(i).accountNum && (SorC == "S" && WorD == "W")) {

                                if (moneyAmount > KCBankRecUpdate.at(i).savingsBal) {
                                    //update struct members to values that are throwing error so that
                                    //updated error values will be thrown to catch and added to KCBankErrorComments
                                    tempKCBankRec.accountNum=KCBankRecUpdate.at(i).accountNum;
                                    tempKCBankRec.firstName=KCBankRecUpdate.at(i).firstName;
                                    tempKCBankRec.lastName=KCBankRecUpdate.at(i).lastName;
                                    throw runtime_error(" does not have sufficient funds in savings account");

                                } else {
                                    KCBankRecUpdate.at(i).savingsBal = KCBankRecUpdate.at(i).savingsBal - moneyAmount;
                                }

                            }
                        }catch(runtime_error& error5) {
                            //adding what error was caught to an error vector of strings
                            //so that comments specific to error and what value is throwing said
                            //error can also be passed to vector
                            KCBankErrorComments.push_back(to_string(KCBankRecUpdate.at(i).accountNum));
                            KCBankErrorComments.emplace_back(error5.what());
                        }


                        //Depositing funds to savings account of account that needs to be updated
                        //as specified by value of accountNumUpdate in current loop
                        //while simultaneously iterating through the vector of structs
                        if (accountNumUpdate == KCBankRecUpdate.at(i).accountNum && (SorC == "S" && WorD == "D")) {
                            KCBankRecUpdate.at(i).savingsBal = KCBankRecUpdate.at(i).savingsBal + moneyAmount;
                        }


                        //Error check: making sure the account that needs to be updated has enough
                        //funds to be withdrawn from checking account
                        //if not, the value throwing error will be put into KCBankErrorComments vector
                        try {
                            if ((accountNumUpdate == KCBankRecUpdate.at(i).accountNum) && (SorC == "C" && WorD == "W")) {

                                if (moneyAmount > KCBankRecUpdate.at(i).checkingBal) {
                                    //update struct members to values that are throwing error so that
                                    //updated error values will be thrown to catch and added to KCBankErrorComments
                                    tempKCBankRec.accountNum=KCBankRecUpdate.at(i).accountNum;
                                    tempKCBankRec.firstName=KCBankRecUpdate.at(i).firstName;
                                    tempKCBankRec.lastName=KCBankRecUpdate.at(i).lastName;
                                    throw runtime_error(" does not have sufficient funds in checking account");
                                } else {
                                    KCBankRecUpdate.at(i).checkingBal = KCBankRecUpdate.at(i).checkingBal - moneyAmount;
                                }
                            }
                        }catch(runtime_error& error3) {
                            //adding what error was caught to an error vector of strings
                            //so that comments specific to error and what value is throwing said
                            //error can also be passed to vector
                            KCBankErrorComments.push_back(to_string(KCBankRecUpdate.at(i).accountNum));
                            KCBankErrorComments.emplace_back(error3.what());
                            KCBankErrorComments.emplace_back("\n");
                        }


                        //Depositing funds to checking account of account that needs to be updated
                        //as specified by value of accountNumUpdate in current loop
                        //while simultaneously iterating through the vector of structs
                        if (accountNumUpdate == KCBankRecUpdate.at(i).accountNum) {
                            if (SorC == "C" && WorD == "D") {
                                KCBankRecUpdate.at(i).checkingBal = KCBankRecUpdate.at(i).checkingBal + moneyAmount;
                                }
                            }

                    }


                    //Error check: iterating through vector of account numbers from the add account list
                    //while using the current loops value of accountNumUpdate as a key to see
                    //if an account from the update account list exists or not in the list of accounts that have
                    //already been added
                    try {
                        if (find(accountExistCheck.begin(), accountExistCheck.end(), accountNumUpdate) !=
                            accountExistCheck.end()) {
                            continue;
                        } else {
                            throw runtime_error(" does not exist");
                        }
                    }catch(runtime_error& error7){
                        //adding what error was caught to an error vector of strings
                        //so that comments specific to error and what value is throwing said
                        //error can also be passed to vector
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


/*
 * Precondition:
 *
 *
 *
 * Postcondition:
 */
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


/*
 *
 * Precondition:
 *
 * Postcondition:
 */
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


/*
 *
 * Precondition:
 *
 * Postcondition:
 */
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
            outFS<<KCBankErrorComments.at(i);
        }


        outFS.close();
    }
}