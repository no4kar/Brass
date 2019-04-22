#include<iostream>
//#include<vector>
//#include<list>
#include"acct.h"

using std::cout;
using std::cin;
//using std::vector;
//using std::list;
using std::shared_ptr;

int main() {
	int client = 3;
	/*cout << "How many will client be crieted?\n";
	cin >> client;*/
	//std::shared_ptr<Acct>;
	//list<shared_ptr<Acct>> arr(client);
	//std::list<std::shared_ptr<Acct>>::iterator it = arr.begin();
	
	shared_ptr<Acct*[]> sp_Acct(new Acct*[client]);
	//shared_ptr<Acct> sp_Acct(new Brass);
	//Acct* ptr_Acct = new Brass;
	sp_Acct[0] = new Brass("Somebody Brass", 000000, 5000);
	sp_Acct[1] = new BrassPlus("Somebody_1 BrassPlus", 111111, 1000, 200, 0.15);
	sp_Acct[2] = new BrassPlus(*sp_Acct[0], 300, 0.05);

	for (int i = 0; i < client; i++) {
		sp_Acct[i]->view_account();
	}

	for (int i = 0; i < client; i++) {
		delete sp_Acct[i];
	}
	
	system("pause");
	return 0;
}