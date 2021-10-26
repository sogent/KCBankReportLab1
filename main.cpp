#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "KCBankReportModify.h"

using namespace std;




int main() {
    vector<KCBankAccounts> tempBankRec;
    vector<KCBankAccounts> tempBankRecErrors;
    vector<KCBankAccounts> KCBankRecUpdate;

    openReadFile(tempBankRec, tempBankRecErrors, KCBankRecUpdate);

    int i;
    for(i=0;i<tempBankRec.size();++i){
        cout<<endl;
        cout<<tempBankRec.at(i).accountNum<<endl;
        cout<<tempBankRec.at(i).firstName<<endl;
        cout<<tempBankRec.at(i).lastName<<endl;
        cout<<fixed<<setprecision(2)<<tempBankRec.at(i).savingsBal<<endl;
        cout<<tempBankRec.at(i).checkingBal<<endl;
        cout<<endl;
    }

    cout<<"Account errors:"<<endl;

    for(i=0;i<tempBankRecErrors.size();++i){
        cout<<tempBankRecErrors.at(i).accountNum<<endl;
        cout<<tempBankRecErrors.at(i).firstName<<endl;
        cout<<tempBankRecErrors.at(i).lastName<<endl;
        cout<<endl;
    }









        return 0;
}