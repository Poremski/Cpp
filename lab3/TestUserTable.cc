#include "UserTable.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;

void print_user(std::string f, User u)
{
	cout << f << ": " << u.getName() << ", " << u.getCardNbr() << endl;
}

int main()
{
	std::string outName{"testFile.txt"};
	std::string inName{"users.txt"};
	std::ofstream os(outName);
	UserTable userTable(inName);
	User u1 = userTable.find(21330);
	print_user("21330", u1);
	User u2 = userTable.find(21331);
	print_user("21331", u2);
	User u3 = userTable.find("Jens Holmgren");
	print_user("Jens Holmgren", u3);
	User u4(1234, "Johannes Sunnanvaeder");
	cout << "getNbrUsers before addUser: " << userTable.getNbrUsers() << std::endl;
	userTable.addUser(u4);
	cout << "getNbrUsers after addUser: " << userTable.getNbrUsers() << std::endl;
	userTable.print(os);
	int tFN = userTable.testFindNumber();
	cout << "testFindNumber finds " << tFN << " users. Right? " << (tFN == 0) << endl;
	User u5 = userTable.find(21331);
	print_user("21331",u5);
}