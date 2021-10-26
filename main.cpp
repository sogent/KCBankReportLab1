#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "KCBankReportModify.h"

using namespace std;




int main() {
    vector<KCBankAccounts> KCBankRecAdd;
    vector<KCBankAccounts> KCBankRecErrors;
    vector<KCBankAccounts> KCBankRecUpdate;

    openReadFile(KCBankRecAdd, KCBankRecErrors, KCBankRecUpdate);
    addAccounts(KCBankRecAdd);

    int i;
    for(i=0;i<KCBankRecAdd.size();++i){
        cout<<endl;
        cout<<KCBankRecAdd.at(i).accountNum<<endl;
        cout<<KCBankRecAdd.at(i).firstName<<endl;
        cout<<KCBankRecAdd.at(i).lastName<<endl;
        cout<<fixed<<setprecision(2)<<KCBankRecAdd.at(i).savingsBal<<endl;
        cout<<KCBankRecAdd.at(i).checkingBal<<endl;

    }
    cout<<endl;

    cout<<"Account errors:"<<endl;

    for(i=0;i<KCBankRecErrors.size();++i){
        cout<<KCBankRecErrors.at(i).accountNum<<endl;
        cout<<KCBankRecErrors.at(i).firstName<<endl;
        cout<<KCBankRecErrors.at(i).lastName<<endl;
        cout<<endl;
    }
    cout<<endl;

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