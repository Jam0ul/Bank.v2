#include <iostream>
#include<string>
#include <vector>
#include<fstream>
#include <iomanip>
#include <limits>
using namespace std;
const string FileName = "Client.txt";
const string FileName2 = "User.txt";
struct stClient
{
	string name;
	string phone;
	string pincode;
	string AccountNum;
	double AccountBalance;
	bool flag = false;
};
struct stUser 
{
	string name;
	int permission;
	string password;
	bool flag = false;
};
stUser CurrentUser;
enum enChose {Show = 1 , Add = 2 , Delete = 3 , Update = 4 , Find = 5 ,Transaction = 6 , MangeUsers = 7 ,  Exit = 8 };
enum enUserOptions {ListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,eUpdateUser = 4, eFindUser = 5, eMainMenue = 6};
enum enExtensions { eDeposite = 1, eWithdraw = 2, Total = 3, Main = 4 };
enum enMainMenuePermissions {
	eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
	pUpdateClients = 8, pFindClient = 16, pTranactions = 32,
	pManageUsers = 64
};
void Login();
stClient ReadClientInfo();
string ReadAccountNumber();
double ReadBalance();
string ConvertClientInfoInOneLine(stClient client, string delmiter = "#//#");
void AddDataLineInfoToFile(string fileName, string line);
vector<string> Split(string line, string delmiter = "#//#");
stClient SaveClientInfoToStructer(string line);
vector<stClient> LoadClientDataFromFileToVector(string fileName);
void AddNewClient();
void AddClients();
bool FindAccountNum(string findAccNum, vector<stClient>& v, stClient& client);
bool MarkFlag(string AccNum, vector<stClient>& v);
void SaveClientDataAfterUpdate(string filename, vector<stClient> s);
void PrintClientCard(stClient Client);
bool DeleteClient(string AccNum, vector<stClient>& v);
stClient UpdateInClientInfo(string AccNum);
bool UpdateClientInfoByAccNum(string AccNum, vector<stClient>& v);
void AddScreen();
void DeleteScreen();
void UpdateScreen();
void FindScreen();
void ShowEndScreen();
void PrintClientRecord(stClient Client);
void PrintAllClientsDataScreen(vector<stClient> vClients);
void PrintAllData();
void TotalBalnce(vector<stClient> vClients);
void PrintClientBalnceCard(stClient Client);
void MainMenue();
void MainMenueCoice(enChose choice);
short ReadMainMenueOption();
void GoBackToMainMenue();
bool Depostie(string AccNum, vector<stClient>& v);
bool Withdraw(string AccNum, vector<stClient>& v);
void DepostieScreen();
void WithdrawScreen();
int ReadTransectionMenu();
void GoBackToTransactionMenue();
void PrintAllBalanceInfo();
void TransactionCoice(enExtensions choice);
void TransactionMenu();
void UserMenue();
short ReadUserMenueOption();
string ReadUserName();
void PrintUserRecord(stUser User);
void ListScreen(vector<stUser> vUser);
void PrintAllUserData();
stUser SaveUserInfoToStructer(string line);
bool UserExistsByUsername(string Username, string FileName);
int ReadPermissions();
stUser ReadUserInfo();
string ConvertUserInfoInOneLine(stUser User, string delmiter = "#//#");
vector<stUser> LoadUserDataFromFileToVector(string fileName);
void AddNewUser();
void AddUsers();
void AddUserScreen();
bool FindUserName(string findUser, vector<stUser>& v, stUser& User);
void FindUserScreen();
void SaveUserDataAfterUpdate(string filename, vector<stUser> s);
void PrintUserCard(stUser User);
bool MarkFlagUser(string UserName, vector<stUser>& v);
bool DeleteUser(string UserName, vector<stUser>& v);
void DeleteUserScreen();
stUser UpdateInUserInfo(string UserName);
bool UpdateUserInfo(string UserName, vector<stUser>& v);
void UpdateUserScreen();
void UserMenueCoice(enUserOptions choice);
bool CheckAccessPermission(enMainMenuePermissions Permission);
void ShowAccessDeniedMessage()
{
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this, \nPlease Conact Your Admin.";
		cout << "\n------------------------------------\n";
}
stClient ReadClientInfo() 
{
	stClient client;
	cout << "enter account number :  ";
	getline(cin >> ws, client.AccountNum);
	cout << "\nenter PinCode : ";
	getline(cin >> ws, client.pincode);
	cout << "\nenter Name : ";
	getline(cin >> ws, client.name);
	cout << "\nenter PhoneNumber : ";
	getline(cin >> ws, client.phone);
	cout << "enter Account Balance :  ";
	cin >> client.AccountBalance;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return client;
}
string ReadAccountNumber() 
{
	string AccountNum;
	cout << "please enter Account Number\n";
	cin >> AccountNum;
	return AccountNum;

}
double ReadBalance() 
{
	double balance;
	cout << " please enter balance amount\n";
	cin >> balance;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return balance;
}
string ConvertClientInfoInOneLine(stClient client , string delmiter)
{
	string word = "";
	word = word + client.AccountNum + delmiter;
	word = word + client.pincode + delmiter;
	word = word + client.name + delmiter;
	word = word + client.phone + delmiter;
	word = word + to_string(client.AccountBalance) + delmiter;

	return word;

}
void AddDataLineInfoToFile(string fileName , string line) 
{
	fstream file;
	file.open(fileName, ios::out | ios::app);
	if (file.is_open()) 
	{
		file << line<<endl;
		file.close();
	}
}
vector <string> Split (string line , string delmiter )
{
	string word;
	int pos;
	vector <string> v;
	while ((pos = line.find(delmiter)) != std::string::npos)
	{
		word = line.substr(0, pos);
		if (!word.empty())
		{
			v.push_back(word);
		}
		line.erase(0, pos + delmiter.length());
	}
	if (!line.empty())
		v.push_back(line);

	return v;
}
stClient SaveClientInfoToStructer(string line)
{
	vector <string> v = Split(line);
	stClient client;
	client.AccountNum = v[0];
	client.pincode = v[1];
	client.name = v[2];
	client.phone = v[3];
	client.AccountBalance = stod(v[4]);

	return client;

}
vector <stClient> LoadClientDataFromFileToVector(string fileName)
{
	vector <stClient> v;
	fstream file;
	stClient client;
	
	file.open(FileName, ios::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line)) 
		{
			client = SaveClientInfoToStructer(line);
			v.push_back(client);
		
		}
		file.close();
	}
	return v;
}
void AddNewClient() 
{
	stClient client = ReadClientInfo();
	AddDataLineInfoToFile(FileName, ConvertClientInfoInOneLine(client));

}
void AddClients()
{
	char add = 'y';
	do 
	{
		system("cls");
		cout << "Adding new Client : \n";
		AddNewClient();
		cout << "added has been successfully\npress [Y] if you want to add more\npress [N] if you dont\n";
		cin>> add;
	
	} 
	while (toupper(add)=='Y');

}
bool FindAccountNum(string findAccNum , vector <stClient> &v, stClient &client)
{
	
	for (stClient & C : v) 
	{
		if (C.AccountNum == findAccNum)
		{
			client = C;
			return true;
			
		}
	}
	return false;

}
bool MarkFlag(string AccNum, vector <stClient> &v)
{
	
	for (stClient& c : v)
	{
		if (c.AccountNum == AccNum)
		{
			c.flag = true;
			return true;
		}
			
	}
	return false;
}
void SaveClientDataAfterUpdate(string filename,vector<stClient> s)
{

	fstream file;
	string line;
	file.open(FileName, ios::out);
	if (file.is_open())
	{
		for (stClient &st : s)
		{
			if (st.flag == false)
			{
				line = ConvertClientInfoInOneLine(st);
				file << line << endl;
			}

		}
		file.close();
	}
}
void PrintClientCard(stClient Client) 
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNum;
	cout << "\nPin Code : " << Client.pincode;
	cout << "\nName : " << Client.name;
	cout << "\nPhone : " << Client.phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;

}
bool DeleteClient(string AccNum, vector <stClient> &v)
{
	stClient client;
	char sure = 'Y';
	if (FindAccountNum(AccNum, v, client))
	{
		PrintClientCard(client);
		cout << "Are you sure you want to delete this client account\npress [Y] if you are sure\npress [N] if you don't want to delete \n";
		cin >> sure;
		if (toupper(sure) == 'Y')
		{
			MarkFlag(AccNum,v);
			SaveClientDataAfterUpdate(FileName, v);
			v = LoadClientDataFromFileToVector(FileName);
			cout << "delete was done successfully";
			return true;
		}

	}
	else cout << "\nClient with Account Number (" << AccNum<< ") is Not Found!";
	return false;

}
stClient UpdateInClientInfo(string AccNum)
{
	stClient client;
	client.AccountNum = AccNum;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\nenter PinCode : ";
	getline(cin>>ws, client.pincode);
	cout << "\nenter Name : ";
	getline(cin >> ws, client.name);
	cout << "\nenter PhoneNumber : ";
	getline(cin >> ws, client.phone);
	cout << "enter Account Balance :  ";
	cin >> client.AccountBalance;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return client;


}
bool UpdateClientInfoByAccNum(string AccNum, vector <stClient> &v)
{
	stClient client;
	char sure = 'Y';
	if (FindAccountNum(AccNum, v, client)) 
	{
		PrintClientCard(client);
		cout << "Are you sure you want to Update in this client account\npress [Y] if you are sure\npress [N] if you don't want to Update\n";
		cin >> sure;
		if (toupper(sure) == 'Y')
		{
			for (stClient& st : v)
			{
				if (st.AccountNum == AccNum)
				{
					st = UpdateInClientInfo(AccNum);
					break;
				}
			}
			SaveClientDataAfterUpdate(FileName, v);
			v = LoadClientDataFromFileToVector(FileName);
			cout << "Update was done successfully";
			return true;
		}
		
	}
	else cout << "\nClient with Account Number (" << AccNum << ") is Not Found!";
	return false;

}
void AddScreen()
{
	if
		(!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n-----------------------------------\n";
	cout << "\tAdd Client Screen";
	cout << "\n-----------------------------------\n";

	AddClients();

}
void DeleteScreen()
{
	if
		(!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector <stClient> v = LoadClientDataFromFileToVector(FileName);
	char tryAgain = 'Y';

	do
	{
		string accnum = ReadAccountNumber();

		if (DeleteClient(accnum, v))
			break;  
		
		cout << "\nDo you want to try again? [Y/N]: ";
		cin >> tryAgain;

	} while (toupper(tryAgain) == 'Y');
}
void UpdateScreen()
{
	if
		(!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Screen";
	cout << "\n-----------------------------------\n";
	vector <stClient> v = LoadClientDataFromFileToVector(FileName);
	
	char tryAgain = 'Y';
	do 
	{
		string accnum = ReadAccountNumber();
		if (UpdateClientInfoByAccNum(accnum, v))
			break;
		
		    cout << "\nDo you want to try again? [Y/N]: ";
		    cin >> tryAgain;

	}
	while (toupper(tryAgain) == 'Y');

}
void FindScreen()
{

	if
		(!CheckAccessPermission(enMainMenuePermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";
	vector <stClient> v = LoadClientDataFromFileToVector(FileName);
	stClient s;
	string accnum = ReadAccountNumber();
	if (FindAccountNum(accnum, v, s))
		PrintClientCard(s);
	else cout << "the client with Acoount Number [" << accnum << "] is not found " << endl;

}
void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}
void MainMenueCoice(enChose choice)
{
	switch (choice)
	{
	case enChose::Add:
	{
		system("cls");
		AddScreen();
		GoBackToMainMenue();
		break;
	}
	case enChose::Delete:
	{
		system("cls");
		DeleteScreen();
		GoBackToMainMenue();
		break;
	}
	case enChose::Find:
	{
		system("cls");
		FindScreen();
		GoBackToMainMenue();
		break;
	}
	case enChose::Exit:
	{
		system("cls");
		//ShowEndScreen();
		Login();
		//exit(0);
	}
	case enChose::Update:
	{
		system("cls");
		UpdateScreen();
		GoBackToMainMenue();
		break;
	}
	case enChose::Show:
	{
		system("cls");
		PrintAllData();
		GoBackToMainMenue();
		break;
	}
	case enChose::Transaction:
	{
		system("cls");
		TransactionMenu();
		GoBackToMainMenue();
		break;
	}
	case enChose::MangeUsers:
	{
		system("cls");
		UserMenue();
		GoBackToMainMenue();
		break;
	}

	}
	
}
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 8]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
void PrintClientRecord(stClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNum;
	cout << "| " << setw(10) << left << Client.pincode;
	cout << "| " << setw(40) << left << Client.name;
	cout << "| " << setw(12) << left << Client.phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
bool CheckAccessPermission(enMainMenuePermissions Permission) 
{
	if (CurrentUser.permission == enMainMenuePermissions::eAll)
		return true;
	if ((Permission & CurrentUser.permission) == Permission)
		return true;
	else
		return false;
}
void PrintAllClientsDataScreen(vector <stClient> vClients)
{

	if
		(!CheckAccessPermission(enMainMenuePermissions::pListClients))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n\t\t\t\t\tClient List (" << static_cast<int>(vClients.size()) << ")Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;


	for (stClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;


}
void PrintAllData()
{
	vector <stClient> v = LoadClientDataFromFileToVector(FileName);
	PrintAllClientsDataScreen(v);

}
void MainMenue()
{

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Mange Users.\n";
	cout << "\t[8] LogOut.\n";
	cout << "===========================================\n";

	cout << "chose what do you want to do \n";
	int chose = ReadMainMenueOption();
	MainMenueCoice(enChose(chose));
}
void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	MainMenue();
}
bool Depostie(string AccNum, vector <stClient> &v)
{
	char sure = 'Y';
	stClient client;
	if (FindAccountNum(AccNum, v, client))
	{
		PrintClientCard(client);
		cout << "\nAre you sure you want to Depsite in this client account\npress [Y] if you are sure\npress [N] if you don't want to  \n";
		cin >> sure;
		if (toupper(sure) == 'Y')
		{
			for (stClient& c : v)
			{
				double amount;

				if (c.AccountNum == AccNum)
				{
					do
					{
						cout << "Enter Deposite amount: ";
						amount = ReadBalance();
						if (amount <= 0)
							cout << "Invalid amount!\n";
					}
					while (amount <= 0);
					c.AccountBalance  +=  amount;
					cout << "New Balance: " << c.AccountBalance << endl;
					break;
				}
			}
			SaveClientDataAfterUpdate(FileName, v);
			v = LoadClientDataFromFileToVector(FileName);
			cout << "Deposite was done successfully";
			return true;
		}
	}
	else cout << "\nClient with Account Number (" << AccNum << ") is Not Found!";
	return false;

}
bool Withdraw(string AccNum, vector <stClient>& v)
{
	char sure = 'Y';
	stClient client;
	if (FindAccountNum(AccNum, v, client))
	{
		PrintClientCard(client);
		cout << "\nAre you sure you want to Withdraw in this client account\npress [Y] if you are sure\npress [N] if you don't want to  \n";
		cin >> sure;
		if (toupper(sure) == 'Y')
		{
			double amount ;

			for (stClient& c : v)
			{
				if (c.AccountNum == AccNum)
				{
					do
					{
						cout << "Enter withdraw amount: ";
						amount = ReadBalance();
						if (amount > c.AccountBalance || amount <= 0)
							cout << "Invalid amount!\n";
					} 
					while (amount > c.AccountBalance ||  amount <= 0);

					c.AccountBalance -= amount;
					cout << "New Balance: " << c.AccountBalance << endl;
					break;
				}
			}
			SaveClientDataAfterUpdate(FileName, v);
			v = LoadClientDataFromFileToVector(FileName);
			cout << "WithDraw was done successfully";
			return true;
		}
	}
	else cout << "\nClient with Account Number (" << AccNum << ") is Not Found!";
	return false;
}
void DepostieScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDepsite in Balance Screen";
	cout << "\n-----------------------------------\n";

	vector <stClient> v = LoadClientDataFromFileToVector(FileName);
	char tryAgain = 'Y';

	do
	{
		string accnum = ReadAccountNumber();

		if (Depostie(accnum, v))
			break;

		cout << "\nDo you want to try again? [Y/N]: ";
		cin >> tryAgain;

	}
	while (toupper(tryAgain) == 'Y');

}
void WithdrawScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw in Balance Screen";
	cout << "\n-----------------------------------\n";

	vector <stClient> v = LoadClientDataFromFileToVector(FileName);
	char tryAgain = 'Y';

	do
	{
		string accnum = ReadAccountNumber();

		if (Withdraw(accnum, v))
			break;

		cout << "\nDo you want to try again? [Y/N]: ";
		cin >> tryAgain;

	} 
	while (toupper(tryAgain) == 'Y');

}
int ReadTransectionMenu() 
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	int Choice = 0;
	cin >> Choice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Choice;
}
void GoBackToTransactionMenue()
{
	cout << "\n\nPress any key to go back to Transaction Menue...";
	system("pause>0");
	TransactionMenu();
}
void PrintAllBalanceInfo()
{
	vector <stClient> v = LoadClientDataFromFileToVector(FileName);
	TotalBalnce(v);

}
void TransactionCoice(enExtensions choice) 
{
	switch (choice)
	{
	case enExtensions::eDeposite:
	{
		system("cls");
		DepostieScreen();
		GoBackToTransactionMenue();
		break;
	}
	case enExtensions::eWithdraw: 
	{
		system("cls");
		WithdrawScreen();
		GoBackToTransactionMenue();
		break;
	}
	case enExtensions::Total: 
	{
		system("cls");
		PrintAllBalanceInfo();
		GoBackToTransactionMenue();
		break;
	}
	case enExtensions::Main: 
	{
		//system("cls");
		GoBackToMainMenue();
		break;
	}

	}
}
void TransactionMenu() 
{
	if
		(!CheckAccessPermission(enMainMenuePermissions::pTranactions))
	{
		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Depostie List.\n";
	cout << "\t[2] Withdraw List.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Exit to MainMenue\n";
	cout << "===========================================\n";

	int chose = ReadTransectionMenu();
	TransactionCoice(enExtensions(chose));

}
void PrintClientBalnceCard(stClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNum;
	cout << "| " << setw(40) << left << Client.name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void TotalBalnce(vector <stClient> vClients)
{

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (stClient Client : vClients)
	{
		PrintClientBalnceCard(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}
short ReadUserMenueOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
string ReadUserName()
{
	string UserName;
	cout << "please enter User Name\n";
	cin >> UserName;
	return UserName;

}
void UserMenue()
{
	if
		(!CheckAccessPermission(enMainMenuePermissions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMange Users Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User Info.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] MainMenue.\n";
	cout << "===========================================\n";
	cout << "chose what do you want to do \n";
	int chose = ReadUserMenueOption();
	UserMenueCoice(enUserOptions(chose));

}
void PrintUserRecord(stUser User)
{
	cout << "| " << setw(15) << left << User.name;
	cout << "| " << setw(10) << left << User.password;
	cout << "| " << setw(40) << left << User.permission;
}
void ListScreen(vector <stUser> vUser)
{
	cout << "\n\t\t\t\t\tClient List (" << static_cast<int>(vUser.size()) << ")Client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "passoword";
	cout << "| " << left << setw(40) << "permission";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (stUser User : vUser)
	{
		PrintUserRecord(User);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;


}
void PrintAllUserData()
{
	vector <stUser> v = LoadUserDataFromFileToVector(FileName2);
	ListScreen(v);

}
stUser SaveUserInfoToStructer(string line)
{
	vector <string> v = Split(line);
	stUser User;
	User.name = v[0];
	User.password = v[1];
	User.permission = stoi(v[2]);
	return User;
}
bool UserExistsByUsername(string Username, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName2, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stUser User;
		while (getline(MyFile, Line))
		{
			User = SaveUserInfoToStructer(Line);
			if (User.name == Username)
			{
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}
int ReadPermissions()
{
	int Permissions = 0;
	char Answer = 'n';
	cout << "\nDo you want to give full access? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		return -1;
	}
	cout << "\nDo you want to give access to : \n ";
	cout << "\nShow Client List? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuePermissions::pListClients;
	}
	cout << "\nAdd New Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuePermissions::pAddNewClient;
	}
	cout << "\nDelete Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuePermissions::pDeleteClient;
	}
	cout << "\nUpdate Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuePermissions::pUpdateClients;
	}
	cout << "\nFind Client? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuePermissions::pFindClient;
	}
	cout << "\nTransactions? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuePermissions::pTranactions;
	}
	cout << "\nManage Users? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permissions += enMainMenuePermissions::pManageUsers;
	}
	return Permissions;

}
stUser ReadUserInfo()
{
	stUser User;
	cout << "enter User Name :  ";
	getline(cin >> ws, User.name);

	while (UserExistsByUsername(User.name,FileName2))
	{
		cout << "\nClient with [" <<User.name << "]already exists, Enter another Account Number ? ";
		getline(cin >> ws, User.name);
	}
	cout << "\nenter Password : ";
	getline(cin >> ws,User.password);
	cout << "\nenter permission : ";
	 User.permission= ReadPermissions();
	return User;
}
string ConvertUserInfoInOneLine(stUser User , string delmiter)
{
	string word = "";
	word = word +  User.name + delmiter;
	word = word +	User.password + delmiter;
	word = word + to_string(User.permission) + delmiter;
	return word;
}
vector <stUser> LoadUserDataFromFileToVector(string fileName)
{
	vector <stUser> v;
	fstream file;
	stUser User;

	file.open(FileName2, ios::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			User = SaveUserInfoToStructer(line);
			v.push_back(User);
		}
		file.close();
	}
	return v;
}
void AddNewUser()
{
	stUser User = ReadUserInfo();
	AddDataLineInfoToFile(FileName2, ConvertUserInfoInOneLine(User));
}
void AddUsers()
{
	char add = 'y';
	do
	{
		system("cls");
		cout << "Adding new User : \n";
		AddNewUser();
		cout << "added has been successfully";
		cout << "\npress[Y] if you want to add more\npress[N] if you dont\n";
		cin >> add;

	} while (toupper(add) == 'Y');

}
void AddUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd User Screen";
	cout << "\n-----------------------------------\n";

	AddUsers();

}
bool FindUserName(string findUser, vector <stUser>& v, stUser& User)
{

	for (stUser& C : v)
	{
		if (C.name == findUser)
		{
			User = C;
			return true;
		}
	}
	return false;

}
bool FindUserByNameAndPass(string findUser, string password, stUser& User)
{
	vector <stUser> v = LoadUserDataFromFileToVector(FileName2);
	for (stUser& C : v)
	{
		if (C.name == findUser&&C.password==password)
		{
			User = C;
			return true;
		}
	}
	return false;

}
void FindUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n-----------------------------------\n";
	vector <stUser> v = LoadUserDataFromFileToVector(FileName2);
	stUser s;
	string UserName = ReadUserName();
	if (FindUserName(UserName, v, s))
		PrintUserCard(s);
	else cout << "the client with Acoount Number [" << UserName << "] is not found " << endl;

}
void SaveUserDataAfterUpdate(string filename, vector<stUser> s) 
{

	fstream file;
	string line;
	file.open(FileName2, ios::out);
	if (file.is_open())
	{
		for (stUser& st : s)
		{
			if (st.flag == false)
			{
				line = ConvertUserInfoInOneLine(st);
				file << line << endl;
			}
		}
		file.close();
	}
}
void PrintUserCard(stUser User)
{
	cout << "\nThe following are the User details:\n";
	cout << "\nUserName: " << User.name;
	cout << "\npassword : " << User.password;
	cout << "\nPermission : " << User.permission;
}
bool MarkFlagUser(string UserName, vector <stUser>& v)
{

	for (stUser& c : v)
	{
		if (c.name == UserName)
		{
			c.flag = true;
			return true;
		}

	}
	return false;
}
bool DeleteUser(string UserName, vector <stUser>& v)
{
	stUser User;
	char sure = 'Y';

	if (UserName == "Admin")
	{
		cout << "you cant delete this user ";
		return false;
	}

	if (FindUserName(UserName, v, User))
	{
		PrintUserCard(User);
		cout << "Are you sure you want to delete this User account\npress [Y] if you are sure\npress [N] if you don't want to delete \n";
		cin >> sure;
		
		if (toupper(sure) == 'Y')
		{
			MarkFlagUser(UserName, v);
			SaveUserDataAfterUpdate(FileName2, v);
			v = LoadUserDataFromFileToVector(FileName2);
			cout << "delete was done successfully";
			return true;
		}

	}
	else cout << "\nUser with Name (" << UserName << ") is Not Found!";
	return false;

}
void DeleteUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n-----------------------------------\n";

	vector <stUser> v = LoadUserDataFromFileToVector(FileName2);
	char tryAgain = 'Y';

	do
	{
		string UserName = ReadUserName();

		if (DeleteUser(UserName, v))
			break;

		cout << "\nDo you want to try again? [Y/N]: ";
		cin >> tryAgain;

	} while (toupper(tryAgain) == 'Y');
}
stUser UpdateInUserInfo(string UserName)
{
	stUser User;
	User.name = UserName;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\nenter Password : ";
	getline(cin >> ws, User.password);
	////
	cout << "\nenter Permission : ";
	User.permission = ReadPermissions();
	return	User;
}
bool UpdateUserInfo(string UserName, vector <stUser>& v)
{
	stUser User;
	char sure = 'Y';
	if (FindUserName(UserName, v, User))
	{
		PrintUserCard(User);
		cout << "Are you sure you want to Update in this User account\npress [Y] if you are sure\npress [N] if you don't want to Update\n";
		cin >> sure;
		if (toupper(sure) == 'Y')
		{
			for (stUser& st : v)
			{
				if (st.name == UserName)
				{
					st = UpdateInUserInfo(UserName);
					break;
				}
			}
			SaveUserDataAfterUpdate(FileName2, v);
			v = LoadUserDataFromFileToVector(FileName2);
			cout << "Update was done successfully";
			return true;
		}

	}
	else cout << "\nClient with Account Number (" << UserName << ") is Not Found!";
	return false;

}
void UpdateUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate User Screen";
	cout << "\n-----------------------------------\n";
	vector <stUser> v = LoadUserDataFromFileToVector(FileName2);

	char tryAgain = 'Y';
	do
	{
		string UserName = ReadUserName();
		if (UpdateUserInfo(UserName, v))
			break;

		cout << "\nDo you want to try again? [Y/N]: ";
		cin >> tryAgain;

	} while (toupper(tryAgain) == 'Y');

}
void UserMenueCoice(enUserOptions choice)
{
	switch(choice) 
	{
	case enUserOptions::eAddNewUser:
	{
		system("cls");
		AddUserScreen();
		GoBackToMainMenue();
		break;
	}
	case enUserOptions::eDeleteUser:
	{
		system("cls");
		DeleteUserScreen();
		GoBackToMainMenue();
		break;
	}
	case enUserOptions::eFindUser:
	{
		system("cls");
		FindUserScreen();
		GoBackToMainMenue();
		break;
	}
	case enUserOptions::eUpdateUser:
	{
		system("cls");
		UpdateUserScreen();
		GoBackToMainMenue();
		break;
	}
	case enUserOptions::ListUsers:
	{
		system("cls");
		PrintAllUserData();
		GoBackToMainMenue();
		break;
	}
	case enUserOptions::eMainMenue:
	{
		system("cls");
		GoBackToMainMenue();
		break;
	}

	
	
	}


}
void Login()
{
	bool LoginFaild = false;
	string Username, Password;
	do
	{
		system("cls");
		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";
		if (LoginFaild)
		{
			cout << "Invlaid Username/Password!\n";
		}
		cout << "Enter Username? ";
		cin >> Username;
		cout << "Enter Password? ";
		cin >> Password;
		LoginFaild = !FindUserByNameAndPass(Username, Password ,CurrentUser);
	} while (LoginFaild);
	MainMenue();
}
int main()
{
	Login();
}
