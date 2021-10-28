#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "KCBankReportModify.h"

using namespace std;




int main() {
    vector<KCBankAccounts> KCBankRecAdd;
    vector<KCBankAccounts> KCBankRecUpdate;
    vector<string> KCBankErrorComments;
    vector<string>updateData;

    openReadFile(KCBankRecAdd, KCBankRecUpdate, KCBankErrorComments);
    addAccounts(KCBankRecAdd);
    updateAccounts(KCBankRecAdd);
    printBankAccounts(KCBankRecAdd);
    printErrorLog(KCBankErrorComments);

    cout<<endl;
    int i;
    cout<<"KCBankRecAdd output:"<<endl;
    for(i=0;i<KCBankRecAdd.size();++i){
        cout<<endl;
        cout<<KCBankRecAdd.at(i).accountNum<<endl;
        cout<<KCBankRecAdd.at(i).firstName<<endl;
        cout<<KCBankRecAdd.at(i).lastName<<endl;
        cout<<fixed<<setprecision(2)<<KCBankRecAdd.at(i).savingsBal<<endl;
        cout<<KCBankRecAdd.at(i).checkingBal<<endl;

    }
    cout<<endl;



cout<<"KCBankRecUpdate output:"<<endl;
    for(i=0;i<KCBankRecUpdate.size();++i){
        cout<<KCBankRecUpdate.at(i).accountNum<<endl;
        cout<<KCBankRecUpdate.at(i).firstName<<endl;
        cout<<KCBankRecUpdate.at(i).lastName<<endl;
        cout<<KCBankRecUpdate.at(i).savingsBal<<endl;
        cout<<KCBankRecUpdate.at(i).checkingBal<<endl;
        cout<<endl;
    }









        return 0;
}