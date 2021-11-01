
#include <vector>
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


    //pass vectors to openReadFile to read the file data, organize then place into their respective vectors
    openReadFile(KCBankRecAdd, KCBankRecUpdate, KCBankErrorComments);

    //adds accounts to a new file
    addAccounts(KCBankRecAdd);

    //updates the accounts previously added (if they need to be updated)
    updateAccounts(KCBankRecAdd);

    //prints out updated accounts to a new summary file
    printBankAccounts(KCBankRecAdd);

    //update summary file to include errors and error comments
    printErrorLog(KCBankErrorComments);





        return 0;
}