//
// Created by Sarah Ogent on 10/21/21.
//
#include <iostream>
#include <vector>
using namespace std;

struct KCBankAccounts{
    int accountNum;
    string firstName;
    string lastName;
    float savingsBal;
    float checkingBal;


};

#ifndef KCBANKREPORTLAB1_KCBANKREPORTMODIFY_H
#define KCBANKREPORTLAB1_KCBANKREPORTMODIFY_H
void openReadFile(vector<KCBankAccounts>& KCBankRecVec, vector<KCBankAccounts>& KCBankRecErrors, vector<KCBankAccounts>& KCBankRecUpdate);
void addAccounts(vector<KCBankAccounts>& addAccountVec);
void updateAccounts(vector<KCBankAccounts>& accountUpdates, vector<KCBankAccounts>& accountErrors);

#endif //KCBANKREPORTLAB1_KCBANKREPORTMODIFY_H
