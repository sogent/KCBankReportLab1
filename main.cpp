#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "KCBankReportModify.h"

using namespace std;

int main() {
    //this vector will be updated throughout the program
    vector<KCBankAccounts> KCBankRecAdd;
    //this vector is solely for error tracking
    //the errors occurring while updating the accounts
    vector<KCBankAccounts> KCBankRecUpdate;
    //this vector is for holding the values that caused errors to be thrown
    //as well as their respective error comments
    vector<string> KCBankErrorComments;



    openReadFile(KCBankRecAdd, KCBankRecUpdate, KCBankErrorComments);
    addAccounts(KCBankRecAdd);
    updateAccounts(KCBankRecAdd);
    printBankAccounts(KCBankRecAdd);
    printErrorLog(KCBankErrorComments);











        return 0;
}