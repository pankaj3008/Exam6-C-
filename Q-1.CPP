#include<iostream>
#include<string>
using namespace std;

class BankAccount{
    
    protected:
    string accountNumber;
    string accountHolderName;
    double balance;

    public:
    BankAccount(){

    }

    BankAccount(string ACC_No , string ACC_Hold_Name , double Balance){
        this -> accountNumber = ACC_No;
        this -> accountHolderName = ACC_Hold_Name ;
        this -> balance = Balance;
    }

    void deposit(double amount){
        this -> balance += amount;        
    }

    void withdraw(double amount){
        if (amount > this -> balance){
            cout << "Insufficient balance" << endl;
        }
        else {
            this -> balance -= amount;
            cout << "Withdrawn: Rs." << amount << endl ;
            }
    }

    int getBalance(){
        return this -> balance;
    }

    void displayAccountDetails(){
        cout << "Account Number: " << this->accountNumber << endl;
        cout << "Account Holder Name: " << this->accountHolderName << endl;
        cout << "Balance: Rs" << this->balance << endl;
    }

    };

    class SavingAccount : public BankAccount{
        public:
        double interestRate ;
        SavingAccount(string ACC_No , string ACC_Hold_Name , double Balance , double Rate) : BankAccount(ACC_No, ACC_Hold_Name, Balance){
            this -> interestRate = Rate ;
        }
        
        void calculateInterest(){
            double Rate = this -> balance * (this -> interestRate / 100);
            cout << "Interst Earned: Rs." << Rate << endl;
            this -> balance += Rate;
        }

    };

    class CheckingAccount : public BankAccount{
        private:
        double overdraftLimit ;

        public:
        CheckingAccount(string ACC_No , string ACC_Hold_Name , double Balance , double Limit) : BankAccount(ACC_No, ACC_Hold_Name, Balance){
            this -> overdraftLimit = Limit ;
            }    

        void withdraw(double amount){
            if(amount > 0 && getBalance() + overdraftLimit >= amount){
                cout << "Withdrawn: Rs." << amount << endl ;
                this->balance -= amount;
            }
            else{
                cout << "withdrawal exceeds overdraft limit!" << endl ;
            }
        }
    };

    class FixedDepositAccount : public BankAccount{
        private:
        int term;
        double interestRate;

        public:
        FixedDepositAccount(string ACC_No , string ACC_Hold_Name , double Balance , int TermOfMonths , double Rate) : BankAccount(ACC_No, ACC_Hold_Name, Balance){
            this -> term = TermOfMonths;
            this -> interestRate = Rate;
        }


        void calculateInterest(){
            double interest = getBalance() * (interestRate / 100) * (term / 12.0);
            cout << "Fixed Deposit Interest: Rs." << interest << "\n";
        }
    };
    void ACC_Type(){
        cout << endl << "SELECT ACCOUNT TYPE" << endl;
        cout << "1. Create Saving Account." << endl;
        cout << "2. Create Checking Account." << endl;
        cout << "3. Create Fixed Deposit Account." << endl;
    }

    void Menu(){
        cout << endl << "BANKING SYSTEM MENU" << endl;
        cout << "1. Deposit Amount" << endl;
        cout << "2. Withdraw Amount" << endl;
        cout << "3. Calculate Interest" << endl;
        cout << "4. Display Bank Account Info.." << endl;
        cout << "5. Exit Now.." << endl;

    }

int main(){

    ACC_Type();

    int Choice;
    int Acc_Type;
    cout << "Select Account Type : ";
    cin >> Acc_Type;
    string ACCNO;
    string NAME;
    double BAL;
    double RATE;
    double ODRAFT;
    double TERM;

    
    SavingAccount savingAccount("", "", 0, 0);
    CheckingAccount checkingAccount("", "", 0, 0);
    FixedDepositAccount fixedDepositAccount("", "", 0, 0, 0);

    switch (Acc_Type)
    {
    case 1:

        cout << "Enter Account Number: ";
        cin >> ACCNO;
        cout << "Enter Account Holder Name: ";
        cin >> NAME;
        cout << "Enter Initial Balance: ";
        cin >> BAL;
        cout << "Enter Interest Rate: ";
        cin >> RATE;
        savingAccount = SavingAccount(ACCNO , NAME , BAL , RATE); 
        break;
    case 2:

        cout << "Enter Account Number: ";
        cin >> ACCNO;
        cout << "Enter Account Holder Name: ";
        cin >> NAME;
        cout << "Enter Initial Balance: ";
        cin >> BAL;
        cout << "Enter Overdraft Limit: ";
        cin >> ODRAFT;
        checkingAccount = CheckingAccount(ACCNO , NAME , BAL , ODRAFT); 
        break;
    case 3:

        cout << "Enter Account Number: ";
        cin >> ACCNO;
        cout << "Enter Account Holder Name: ";
        cin >> NAME;
        cout << "Enter Initial Balance: ";
        cin >> BAL;
        cout << "Enter Term (months): ";
        cin >> TERM;
        cout << "Enter Interest Rate: ";
        cin >> RATE;
        fixedDepositAccount = FixedDepositAccount(ACCNO , NAME , BAL , TERM , RATE);
        break;
    default :
        cout << "Invalid selection!\n";
        return 0;
    }


    do{
        Menu();
        cout << "Enter your Choice: ";
        cin >> Choice;
        double amount;

        switch (Choice)
        {
        case 1:
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            if (Acc_Type == 1) {
                savingAccount.deposit(amount);
            } else if (Acc_Type == 2) {
                checkingAccount.deposit(amount);
            } else if (Acc_Type == 3) {
                fixedDepositAccount.deposit(amount);
            }
            

            break;

        case 2:
            cout << "Enter Withdrawal Amount: ";   
            cin >> amount;
            if (Acc_Type == 1) {
                savingAccount.withdraw(amount);
            } else if (Acc_Type == 2) {
                checkingAccount.withdraw(amount);
            } else if (Acc_Type == 3) {
                cout << "Withdrawals are not allowed from Fixed Deposit Accounts!" << endl;
            }
            break;

        case 3:
            if (Acc_Type == 1) {
                savingAccount.calculateInterest();
            } else if (Acc_Type == 2) {
                cout << "Interest calculation not applicable for Checking Accounts!" << endl;
            } else if (Acc_Type == 3) {
                fixedDepositAccount.calculateInterest();
            }
            
            break;

        case 4:
            if (Acc_Type == 1) {
                savingAccount.displayAccountDetails();
            } else if (Acc_Type == 2) {
                checkingAccount.displayAccountDetails();
            } else if (Acc_Type == 3) {
                fixedDepositAccount.displayAccountDetails();
            }
            break;
        
        case 5:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }
    while(Choice != 5);

    return 0 ;
}