#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<tuple>
#include<sstream>
#include<fstream>
#include<string.h>
using namespace std ;

#define take(x) std::cin >> x ;
#define out(x) std::cout << x ;
#define in(x,y,z,w) out("Enter Your Name : ") ; std::cin >> x ; out("Enter Password : ") ; std::cin >> y ; out("Enter Mobile-No : ") ; std::cin >> z ; out("Enter Intial Amount : ") ; std::cin >> w ;


typedef long long int lli ;

// global variable for setting CustomerID
// Tuple order is std::tuple < password , phonenumber , name , bankbalance >

unsigned int Cardinality = 1 ;
std::map<int,std::tuple<std::string,lli,std::string,float>> Data_Source ;
std::vector<int> Current ;

class BankSys{

    private :

            std::string Name ;
            std::string Password ;
            int CustomerID ;
            lli MobileNumber ;
            float BankBal = 0.00 ;

    public :

            BankSys(std::string name, std::string pass, lli no, float bb){
                
                std::fstream collect("bankdata.txt",ios::app) ;

                this->Name = name ;
                this->Password = pass ;
                this->MobileNumber = no ;
                this->CustomerID = Cardinality ;

                try {
                    if ( bb < 1000 ){

                        std::string s = "Your Amount Is Not Suffcient." ;
                        throw s ;
                    }
                    else{
                        this->BankBal = bb ;
                    }
                }
                catch( std::string exception )
                {
                    out(exception) ;
                    exit(0) ;
                }
                
                Cardinality++ ;

                collect << this->CustomerID <<" "<< this->Password <<" " << this->MobileNumber <<" "<< this->Name <<" "<< this->BankBal <<" "<< "\n" ;

                collect.close() ;

                out("Your Account Is Created Succesfully.\nYour Customer-ID is : ") ;
                out(this->CustomerID) ;
                out("\nLogin Again For Access Your Account\n" ) ;
            }  

            BankSys(){
                out("\n-------------------------------------------------------------------- WELCOME TO JPA BANK --------------------------------------------------------------------\n")
            }  

            void Get_MyDeatils(int ID , std::string pass) ; 

            void Withdraw(int ID, std::string pass ) ;

            void Deposit( int ID , std::string pass) ;

            void Delete_account ( int ID , std::string pass ) ;

            void Modify_account ( int ID , std::string pass ) ;
};

void BankSys::Get_MyDeatils(int ID, std::string pass)
{
    auto  f = std::find( Current.begin() , Current.end() , ID) ;

    if ( get<0>(Data_Source[ID]) == pass && f != Current.end() ){

        std::cout << "\nYour Name is : " << get<2>(Data_Source[ID]) ;
        std::cout << "\nYour Mobile No : " << get<1>(Data_Source[ID]) ;
        std::cout << "\nYour Bank-Balance is : " << get<3>(Data_Source[ID]) << std::endl ;
    }
    else{

        std::cout << "\nYou Enter Wrong Password." ;
        std::abort() ;
    }
}

void BankSys::Withdraw(int ID , std::string pass)
{
    auto f = std::find( Current.begin() , Current.end() , ID ) ;

    if ( get<0>(Data_Source[ID] ) == pass && f != Current.end() ) 
    {
        int creadit ;

        out("Your Current Balance Is : ") ;
        out( get<3>(Data_Source[ID] ) ) ;
        out("\nEnter Amount You Want To Withdraw : ") ;

        take(creadit) ;

        if ( creadit > get<3>( Data_Source[ID] ) ){
            out("\nYou Don't Have Enough Amount.") ;
        }
        else
        {
            get<3>(Data_Source[ID]) -= creadit ;
            out("\nTake Your Money") ;
            out("\n\nYour Current Balance Is : ") ;
            out( get<3>(Data_Source[ID]) ) ;
        }

        // here i have to update all things 

        std::ofstream output("temp.txt") ;

        for ( int i = 1 ; i <= Data_Source.size() ; i++ )
        {
            auto x = std::find( Current.begin() , Current.end() , i ) ;

            if ( x != Current.end() )
            {
                output << i << " " << get<0>(Data_Source[i]) << " " << get<1>(Data_Source[i]) << " " ;
                output << get<2>(Data_Source[i]) << " " << get<3>(Data_Source[i]) << std::endl ;
            }
        }

        output.close() ;

        remove("bankdata.txt") ;
        rename("temp.txt","bankdata.txt") ;
    }
    else
    {
        out("\nYou Enter Wrong Password.") ;
        std::abort() ;
    }

}

void BankSys::Deposit( int ID , std::string pass )
{
    float Balance ;

    out("\nEnter Amount : ") ;
    take(Balance) ;

    get<3>(Data_Source[ID]) = get<3>(Data_Source[ID]) + Balance ;

    out("\nYour Current Balance Is : ") ;
    out( get<3>(Data_Source[ID]) ) ;

    // Here I Have To Update Account Balance 

    std::ofstream output("temp.txt") ;

    for ( int i = 1 ; i <= Data_Source.size() ; i++ )
    {
        auto x = std::find( Current.begin() , Current.end() , i ) ;

        if ( x != Current.end() ) 
        {
            output << i << " " << get<0>(Data_Source[i]) << " " << get<1>(Data_Source[i]) << " " ;
            output << get<2>(Data_Source[i]) << " " << get<3>(Data_Source[i]) << std::endl ;
        }
    }

    output.close() ;

    remove("bankdata.txt") ;
    rename("temp.txt","bankdata.txt") ;
}

void BankSys::Delete_account( int ID , std::string pass )
{
    if ( get<0>(Data_Source[ID]) == pass )
    {
        std::ofstream outfile("temp.txt") ;

        for ( int i = 1 ; i <= Data_Source.size() ; i++ )
        {
            if ( i != ID )
            {
                outfile << i << " " << get<0>(Data_Source[i]) << " " << get<1>(Data_Source[i]) << " " ;
                outfile << get<2>(Data_Source[i]) << " " << get<3>(Data_Source[i]) << std::endl ;
            }
        }

        outfile.close() ;

        remove("bankdata.txt") ;
        rename("temp.txt","bankdata.txt") ;
    }
}

void BankSys::Modify_account( int ID , std::string pass )
{
    out("\n\t\t\t\t\t1 . Change Password ") ;
    out("\n\t\t\t\t\t2 . Change Mobile Number") ;

    int choice ;

    out("\nEnter Choice : ") ;
    cin >> choice ;

    if ( choice == 1 )
    {
        std::ifstream ins("instruction.txt") ;

        while ( ! ins.eof() )
        {
            string s ;

            ins >> s ;

            std::cout << s << " " ;
        }

        std::string Old_pass ;
        std::string new_pass ;
        
        out("\nEnter Old PassWord : ") ;
        
        std::cin >> Old_pass ;

        if ( Old_pass == pass )
        {
            out("\nEnter New PassWord : ") ;
            cin >> new_pass ;

            get<0>(Data_Source[ID]) = new_pass ;
            get<3>(Data_Source[ID]) -= 150 ;

            // Here I Have To Update Account Balance 

            std::ofstream outfile("temp.txt") ;

            for ( int i = 1 ; i <= Data_Source.size() ; i++ )
            {
                auto x = std::find( Current.begin() , Current.end() , i ) ;

                if ( x != Current.end() )
                {
                    outfile << i << " " << get<0>(Data_Source[i]) << " " << get<1>(Data_Source[i]) << " " ;
                    outfile << get<2>(Data_Source[i]) << " " << get<3>(Data_Source[i]) << std::endl ;
                }
            }

            outfile.close() ;

            remove("bankdata.txt") ;
            rename("temp.txt","bankdata.txt") ;

            std::cout << "\nYour Password Is Change.\nLogin Again To Check." ;
        }
        else
        {
            out("\nWrong!!") ;
            std::abort() ;
        }
        
    }
}

int main()
{
    // First I Have To Load All Data
    // ios::in Open File In Read-Mod

    std::ifstream infile("D:\\bankdata.txt",ios::in) ;
    std::string x ;

    int count = 1 ;

    while ( getline( infile , x ,'\n') )
    {
        std::string str[5] ;
        int time = 0 ;

        for ( auto it : x )
        {
            if ( it == ' ' )
            {
                time += 1 ;
            }
            else{
                str[time] = str[time] + it ;
            }
        } 

        std::stringstream a(str[0]) ;
        std::stringstream b(str[2]) ;
        std::stringstream c(str[4]) ;

        int ID ;
        std::string bankpass = str[1];
        lli no ;
        std::string name = str[3];
        float bb ;

        a >> ID ;
        b >> no ;
        c >> bb ;

        Data_Source.insert( { ID , std::make_tuple(bankpass,no,name,bb)} ) ;
        Current.push_back( ID ) ;

        count++ ;
    }

    // Data Loading Over--

    infile.close() ;

    Cardinality = count ;

    int *choice = new int ;
    BankSys* obj ;

    out("1 . New Account \n2 . Access Acount") ;
    out("\nEnter Your Choice ( 1 | 2 ) : ") ;
    take(*choice) ;

    if ( *choice == 1 ){

        std::string newname ;
        std::string newpass ;
        lli no ;
        float intial_amount ;

        in(newname,newpass,no,intial_amount) ;

        obj = new BankSys(newname,newpass,no,intial_amount) ;

        delete obj ;

    }  
    else if ( *choice == 2 ){

        int attmpt = 3 ;

        start :

        obj = new BankSys() ;

        int ID ;
        std::string pass ;

        out("\nEnter Your Customer-ID : ") ;
        take(ID) ; 
        out("Enter Your Password : ") ;
        take(pass) ;

        if ( get<0>(Data_Source[ID]) != pass ){

            std::cout << "\nYou Enter Wrong Details.." ;
            attmpt-- ;
            std::cout << "\nAttmpt Left :- " << attmpt << std::endl ;

            if ( attmpt == 0 ){
                std::abort();
            }
            goto start ;

        }

        int choose ;
        char c ;

        do
        {
            out("\n\t\t\t\t\t1 . Get Your Details") ;
            out("\n\t\t\t\t\t2 . WithDraw Money") ;
            out("\n\t\t\t\t\t3 . Credit Money") ;
            out("\n\t\t\t\t\t4 . Close Account") ;
            out("\n\t\t\t\t\t5 . Modify Account") ;

            out("\n\nEnter Your Choice : ") ;
            take(choose) ;

            switch(choose){
                
                case 1 : 
                            obj->Get_MyDeatils( ID , pass ) ;

                            break ;

                case 2 :
                            obj->Withdraw( ID , pass ) ;

                            break ;

                case 3 :
                            obj->Deposit( ID , pass ) ;             

                            break ;

                case 4 :
                            obj->Delete_account( ID,pass) ;
                            break ; 

                case 5 :
                            obj->Modify_account( ID , pass ) ;
                            break ;                       

                default :

                            goto endwithhappness ;
            }

            out("\nFor Continue Press [Y|N] : ") ;
            take(c) ;
        } 
        while ( c == 'Y' || c == 'y' );

    }
    else{
        
        endwithhappness :

        out("\n-------------------------------------------------------------------- Come Again -------------------------------------------------------------------- ") ;

        std::abort() ;
    }

    return 0 ;
}

