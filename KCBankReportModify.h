//
// Created by Sarah Ogent on 10/21/21.
//
#include <iostream>
#include <vector>
#include<iomanip>
using namespace std;

struct KCBankAccounts{
    int accountNum;
    string firstName;
    string lastName;
    float savingsBal;
    float checkingBal;
    float balanceTotal;


};

#ifndef KCBANKREPORTLAB1_KCBANKREPORTMODIFY_H
#define KCBANKREPORTLAB1_KCBANKREPORTMODIFY_H

void openReadFile(vector<KCBankAccounts>& KCBankRecVec, vector<KCBankAccounts>& KCBankRecUpdate, vector<string>& KCBankErrorComments);
void addAccounts(vector<KCBankAccounts>& addAccountVec);
void updateAccounts(vector<KCBankAccounts>& KCBankAccountVecToUpdate);
void printBankAccounts(vector<KCBankAccounts>& updatedAccountRec);
void printErrorLog(vector<string>& KCBankErrorComments);

#endif //KCBANKREPORTLAB1_KCBANKREPORTMODIFY_H
