#include<iostream>
using namespace std;

int main(){
    int c;
    double money = 1000;
    double x;

    do{
        cout<<"1. balance\n2. deposit\n3. withdraw\n4. exit\nchoose: ";
        cin>>c;

        switch(c){
            case 1:
                cout<<"balance = "<<money<<endl;
                break;
            case 2:
                cout<<"enter amount: ";
                cin>>x;
                money = money + x;
                cout<<"done. balance = "<<money<<endl;
                break;
            case 3:
                cout<<"enter amount: ";
                cin>>x;
                if(x > money){
                    cout<<"no enough money"<<endl;
                }
                else{
                    money = money - x;
                    cout<<"done. balance = "<<money<<endl;
                }
                break;
            case 4:
                cout<<"bye"<<endl;
                break;
            default:
                cout<<"wrong choice"<<endl;
        }
    }while(c!=4);

    return 0;
}
