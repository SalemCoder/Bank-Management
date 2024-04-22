#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>

using namespace std;

struct stClient{
	string AccountNumber;
	string PinCode;
	string Name;
	string phone;
	double AccountBalance;
};
struct stUser{
	string Username;
	string Password;
	string permissions;
};
vector <string> SplitString_User(string line, string led){
	vector <string> vWords;
	short pos = 0;
	string sWord="";
	while((pos=line.find(led)) != std::string::npos){
		sWord = line.substr(0,pos);
		if(sWord!=""){
			vWords.push_back(sWord);
		}
		line.erase(0,pos+led.length());
	}
	if(line != ""){
		vWords.push_back(line);
		
	}
	return vWords;
}
stUser LineToRecord_User(string line){
	stUser user1;
	vector <string> vLine = SplitString_User(line, "<<@>>");
	
	user1.Username = vLine[0];
	user1.Password = vLine[1];
	user1.permissions = vLine[2];
	
	
	return user1;
	
}
vector <stUser> FileToVector_User(string FileName){
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	
	vector <stUser> vUser;
	stUser User;

	if(MyFile.is_open()){
		string line;
		while(getline(MyFile, line)){
			User = LineToRecord_User(line);
			vUser.push_back(User);
		}
		MyFile.close();
	}
	return vUser;
}
vector <string> SplitString(string line, string led){
	vector <string> vWords;
	short pos = 0;
	string sWord="";
	while((pos=line.find(led)) != std::string::npos){
		sWord = line.substr(0,pos);
		if(sWord!=""){
			vWords.push_back(sWord);
		}
		line.erase(0,pos+led.length());
	}
	if(line != ""){
		vWords.push_back(line);
		
	}
	return vWords;
}
stClient LineToRecord(string line){
	stClient Client;
	vector <string> vLine = SplitString(line, "<<@>>");
	
	Client.AccountNumber = vLine[0];
	Client.PinCode = vLine[1];
	Client.Name = vLine[2];
	Client.phone = vLine[3];
	Client.AccountBalance = stod(vLine[4]);
	
	return Client;
	
}
string RecordToLine(stClient Client, string led){
	string s="";
	s += Client.AccountNumber + led;
	s += Client.PinCode + led;
	s += Client.Name + led;
	s += Client.phone + led;
	s += to_string(Client.AccountBalance);
	return s;
}

vector <stClient> FileToVector(string FileName){
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	
	vector <stClient> vClients;
	stClient Client;

	if(MyFile.is_open()){
		string line;
		while(getline(MyFile, line)){
			Client = LineToRecord(line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

void VectorToFile(string FileName, vector <stClient> &vClients){
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	
	if(MyFile.is_open()){
		for (stClient &i : vClients){
			MyFile << RecordToLine(i,"<<@>>");
			MyFile << endl;
		}
		MyFile.close();
	}
}
void ShowClientList(string FileName){
	
	vector <stClient> vClients;
	vClients = FileToVector(FileName);
	
	cout << "\t\tClient List ("<< vClients.size()<< ") Client(s)." << endl<<endl;
	cout << "_________________________________________________________________________________________________"<<endl<<endl;
	cout << "| " << left << setw(15) << "Account Number" ;
	cout << "| " << left << setw(10) << "Pin Code" ;
	cout << "| " << left << setw(40) << "Client Name" ;
	cout << "| " << left << setw(12) << "Phone" ;
	cout << "| " << left << setw(12) << "Balance" <<endl<<endl;
	cout << "_________________________________________________________________________________________________"<<endl<<endl;
	for(stClient &i : vClients){
		cout << "| " << left << setw(15) << i.AccountNumber ;
		cout << "| " << left << setw(10) << i.PinCode ;
		cout << "| " << left << setw(40) << i.Name ;
		cout << "| " << left << setw(12) << i.phone ;
		cout << "| " << left << setw(12) << i.AccountBalance <<endl;

	}
	cout << endl;
	 
}


stClient ReadClientInfo(){
	stClient Client;
	
	cout << "Please Enter Client Data: \n" << endl;
	cout << "Enter Account Number: ";
	cin >> Client.AccountNumber;
	cout << "Enter PinCode: ";
	cin >> Client.PinCode;
	cout << "Enter Name: ";
	cin.ignore(1,'\n');
	getline(cin,Client.Name);
	cout << "Enter Phone: ";
	cin >> Client.phone;
	cout << "Enter Account Balance: ";
	cin >> Client.AccountBalance;
	cout << endl;
	
	return Client;
	
}
void AddNewClient(string FileName){
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if(MyFile.is_open()){
		MyFile << RecordToLine(ReadClientInfo(),"<<@>>");
		MyFile << endl;
		MyFile.close();
	}
	system("clear");
}
void ShowClientInfo(stClient &Client){
	cout << "The Following are the Client Details:" << endl;
	cout << "_____________________________________" << endl;
	cout << "Account Number: " << Client.AccountNumber << endl;
	cout << "Pin Code: " << Client.PinCode << endl;
	cout << "Name: " << Client.Name << endl;
	cout << "Phone: " << Client.phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
	cout << "_____________________________________" << endl;
}
bool FindClient(string FileName,short &c){
	string accNum;
	cout << "\nEnter Client's Account Number: " ;
	cin >> accNum;
	vector <stClient> vClients= FileToVector(FileName);
	for(stClient &i : vClients){
		if(i.AccountNumber == accNum){
			ShowClientInfo(i);
			return true;
		}
		c++;
	}
	return false;
}
void DeletClient(string FileName){
	
	vector <stClient> vClients;
	vClients = FileToVector(FileName);
	

	short c=0;
	if(FindClient(FileName, c)) {
		char x='y';
		cout << "Are you sure you want delete this Client? y/n";
		cin >> x;
		if (x=='y' || x=='Y') vClients.erase(vClients.begin()+c);
	}
	else cout << "Client not found" << endl;
	VectorToFile(FileName, vClients);
	system("clear");
}
void UpdateClientInfo(string FileName){
	vector <stClient> vClients= FileToVector(FileName);
	short c=0;
	if(FindClient(FileName, c)){
		cout << "Update Client Info: " << endl;
		vClients[c] = ReadClientInfo();
	}
	else cout << "Client not found" << endl;

	VectorToFile(FileName, vClients);
	system("clear");
}
void DepositeOrWithdraw(string FileName, string DepositeOrWithDraw){
	system("clear");
	vector <stClient> vClients= FileToVector(FileName);
	cout << "==================================================="<<endl;
	cout << "\t\t"<<DepositeOrWithDraw<<" Screen"<<endl;
	cout << "==================================================="<<endl<<endl;
	short c=0;
	while(!FindClient(FileName, c)){
		cout << "\n\nClient Does Not Exist" <<endl<<endl;
	}
	double DepAmount=0;
	if(DepositeOrWithDraw == "Deposite"){
		cout << "Enter Deposit Amount: ";
		cin >> DepAmount;
		vClients[c].AccountBalance += DepAmount; 
	}
	else if (DepositeOrWithDraw == "Withdraw"){
		do
		{
			cout << "Enter Withdraw Amount: ";
			cin >> DepAmount;
			if (vClients[c].AccountBalance < DepAmount) cout << "Amount Exceeds the balance, you can withdraw up to : " << vClients[c].AccountBalance << endl;
			
		}while(vClients[c].AccountBalance < DepAmount);
		vClients[c].AccountBalance -= DepAmount;
	}
	VectorToFile(FileName, vClients);
	
}

void TotalBalance(string FileName){
	system("clear");
		
	vector <stClient> vClients;
	vClients = FileToVector(FileName);
	cout << "_________________________________________________________________________________________________"<<endl<<endl;
	cout << "\t\t\tClient List ("<< vClients.size()<< ") Client(s)." << endl<<endl;
	cout << "_________________________________________________________________________________________________"<<endl<<endl;
	cout << "| " << left << setw(15) << "Account Number" ;
	cout << "| " << left << setw(40) << "Client Name" ;
	cout << "| " << left << setw(12) << "Balance" <<endl<<endl;
	cout << "_________________________________________________________________________________________________"<<endl<<endl;
	for(stClient &i : vClients){
		cout << "| " << left << setw(15) << i.AccountNumber ;
		cout << "| " << left << setw(40) << i.Name ;
		cout << "| " << left << setw(12) << i.AccountBalance <<endl;
	}
	cout << endl;
	cout << "_________________________________________________________________________________________________"<<endl;
	double sum=0;
	for(stClient &i : vClients){
		sum += i.AccountBalance;
	}
	cout << "\t\t\t\tTotat Blances = " << sum << endl;
}
void TransactionsMenueScreen(string FileName){
	system("clear");
	cout << "==================================================="<<endl;
	cout << "\t\transactions Menue Screen"<<endl;
	cout << "==================================================="<<endl;
	short n;
	do{
		cout << "\t\t[1] Deposite." << endl;
		cout << "\t\t[2] Withdraw." << endl;
		cout << "\t\t[3] Total Balances." << endl;
		cout << "\t\t[4] Main  Menue." << endl;
		cout << "==================================================="<<endl;
		cout << "Chose What do you want to do [1 to 4]: ";
		cin >> n;
		if ( n == 1) DepositeOrWithdraw(FileName, "Deposite");
		if ( n == 2) DepositeOrWithdraw(FileName, "Withdraw");
		if ( n == 3) TotalBalance(FileName);
	}while (n!=4);
	
}
void ManageUsers(){
	cout << "Managine users " << endl;
}
void printMainScreen(string FileName){	
	cout << "==================================================="<<endl;
	cout << "\t\tMain Menue Screen"<<endl;
	cout << "==================================================="<<endl;
	short n;
	do{
		cout << "\t\t[1] Show Client List." << endl;
		cout << "\t\t[2] Add New Client." << endl;
		cout << "\t\t[3] Delete Client." << endl;
		cout << "\t\t[4] Update Client Info." << endl;
		cout << "\t\t[5] Find Client." << endl;
		cout << "\t\t[6] Transactions." << endl;
		cout << "\t\t[7] Manage Users." << endl;
		cout << "\t\t[8] Logout." << endl;
		cout << "Chose What do You want to do[1 to 8]: "; 
		cin >> n;
		if ( n == 1) ShowClientList(FileName);
		if ( n == 2) AddNewClient(FileName);
		if ( n == 3) DeletClient(FileName);
		if ( n == 4) UpdateClientInfo(FileName);
		if ( n == 5) {
			short c=0; 
			if(FindClient(FileName, c)) cout << "Client is Founded" << endl;
			else cout << "Client is NOT Founded " << endl;
		}
		if (n == 6) {
			TransactionsMenueScreen(FileName);
			system("clear");

		}
		if (n == 7){
			ManageUsers();
		}
			
	}while(n!=8);
	system("clear");
	cin.ignore(1,'\n');
}
bool FindUser(string UserList, string Username, string Password){
	vector <stUser> vUsers;
	vUsers = FileToVector_User(UserList);
	for (stUser &i : vUsers){
		if (i.Username == Username && i.Password == Password) return true;
	}
	return false;	
}

void Login(){
	cout << "---------------------" << endl;
	cout << "\tLogin" << endl;
	cout << "---------------------" << endl;
	while (true){
		string UserName,Password;
		cout << "Enter Username: "	;

		getline(cin, UserName);
		cout << "Enter Password: ";
		getline(cin, Password);
		if(FindUser("UserList.txt",UserName, Password)){
			printMainScreen("MyFile.txt");
			cout << "---------------------" << endl;
			cout << "\tLogin" << endl;
			cout << "---------------------" << endl;
		}
		else
		{
			system("clear");
			cout << "---------------------" << endl;
			cout << "\tLogin" << endl;
			cout << "---------------------" << endl;
			cout << "Invalid Username/Password!" << endl;
		}
	}
}
int main(){
		Login();
		
		return 0;
}
