#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <queue>
// hi
using namespace std;
class UserAccountType
{
  protected:string userId;
  string encrypted_password;
  string firstname;
  string lastname;
public:
    UserAccountType ();
    UserAccountType (string id, string pass, string fname, string lname);
  void setUserId (string id);
  void setFirstName (string fname);
  void setLastName (string lname);
  void setPassword (string pass);
  string getUserId () const;
  bool isCompleteUserAccount () const;
  string encryptPassword (string pass);
  void printUserInfo ();
  bool isValidPassword (string pw);
};
UserAccountType::UserAccountType ()
{				//O(1)
  userId = "";
  encrypted_password = "";
  firstname = "";
  lastname = "";
}

UserAccountType::UserAccountType (string id, string pass, string fname,
 string lname)
{				//O(n)
  userId = id;
  firstname = fname;
  lastname = lname;
  if (isValidPassword (pass))
    encrypted_password = encryptPassword (pass);
  else
    encrypted_password = "";
}

void UserAccountType::setUserId (string id)
{				//O(1)
  userId = id;
}

void UserAccountType::setFirstName (string fname)
{				//O(1)
  firstname = fname;
}

void UserAccountType::setLastName (string lname)
{				//O(1)
  lastname = lname;
}

void UserAccountType::setPassword (string pass)
{				//O(n)
  if (isValidPassword (pass))
    encrypted_password = encryptPassword (pass);
  else
    encrypted_password = "";
}

string UserAccountType::getUserId () const 
{				//O(1)
  return userId;
}

bool UserAccountType::isCompleteUserAccount () const 
{				//O(1)
  if (userId != "" && firstname != "" && lastname != ""
      && encrypted_password != "")
    return true;
  return false;
}

string UserAccountType::encryptPassword (string pass)
{				//O(n)
  list < char >obj;
  for (int i = 0; i < pass.size (); i++)
    obj.push_back (pass[i]);
  char temp;
  temp = obj.front ();
  obj.front () = obj.back ();
  obj.back () = temp;
  queue < char >q;
  stack < char >s;
  int size = obj.size ();
  for (int i = 0; i < size; i++)
    {
      q.push (obj.front ());
      obj.pop_front ();
    }
  for (int i = 0; i < size; i++)
    {
      if (q.front () != q.back ())
	{
	  s.push (q.front ());
	  q.pop ();
	  obj.push_back (int (s.top ()) + int (q.front ()) % 10);
	}
      else
	obj.push_back (q.front ());
    }
  queue < char >q2;
  stack < char >s2;
  for (int i = 0; i < size; i++)
    {
      if (i % 2 == 0)
	s2.push (obj.front ());
      else
	q2.push (obj.front ());
      obj.pop_front ();
    }
  for (int i = 0; i < size; i++)
    {
      if (i % 2 == 0)
	{
	  obj.push_back (s2.top ());
	  s2.pop ();
	}
      else
	{
	  obj.push_back (q2.front ());
	  q2.pop ();
	}
    }
  string e_p;
  for (int i = 0; i < size; i++)
    {
      e_p += obj.front ();
      obj.pop_front ();
    }
  return e_p;
}

void UserAccountType::printUserInfo ()
{				//O(1)
  cout << "user's id :" << userId << endl;
  cout << "first name :" << firstname << endl;
  cout << "last name :" << lastname << endl;
  cout << "password :" << encrypted_password << endl;
}

bool UserAccountType::isValidPassword (string pw)
{				//O(n)
  int d = 0, ph = 0, c = 0;
  for (int i = 0; i < pw.length (); i++)
    {
      if (isdigit (pw[i]))
	d++;
      else if (isalpha (pw[i]))
	ph++;
      else if (pw[i] == '#' || pw[i] == '$' || pw[i] == '*')
	c++;
    }
  if (d == 1 && c == 1 && ph >= 4 && ph <= 6)
    return true;
  else
    return false;
}

class UserAccountNode
{
public:
  UserAccountType user_account;
  UserAccountNode *link;
};

class UserAccountListType
{
  UserAccountNode *first;
  UserAccountNode *last;
  int counter;
public:
    UserAccountListType ();
  void destroyList ();
   ~UserAccountListType ();
  void print () const;
  bool IsUserIdExist (string id);
  void insertUserAccount (const UserAccountType newItem);
  void deleteUserAccount (string id);
  void printInfo_of_UserId (string id);
};
UserAccountListType::UserAccountListType ()
{				//O(1)
  first = NULL;
  last = NULL;
  counter = 0;
}

void UserAccountListType::destroyList ()
{				//O(n)
  UserAccountNode *p;
  while (first != NULL)
    {
      p = first;
      first = first->link;
      delete p;
    }
  last = NULL;
  counter = 0;
}

UserAccountListType::~UserAccountListType ()
{				//O(n)
  destroyList ();
}

void UserAccountListType::print () const 
{				//O(n)
  UserAccountNode *c;
  c = first;
  while (c != NULL)
    {
      c->user_account.printUserInfo ();
      cout << endl;
      c = c->link;
    }
}

bool UserAccountListType::IsUserIdExist (string id)
{				//O(n)
  UserAccountNode *c;
  c = first;
  while (c != NULL)
    {
      if (id.compare (c->user_account.getUserId ()) == 0)
	return true;
      else
	c = c->link;
    }
  return false;
}

void UserAccountListType::insertUserAccount (const UserAccountType newItem)
{				//O(1)
  if (newItem.isCompleteUserAccount ())
    {
      if (!IsUserIdExist (newItem.getUserId ()))
	{
	  UserAccountNode *c;
	  c = new UserAccountNode;
	  c->user_account = newItem;
	  c->link = NULL;
	  if (first == NULL)
	    {
	      first = c;
	      last = c;
	      counter++;
	    }
	  else
	    {
	      last->link = c;
	      last = c;
	      counter++;
	    }
	}
      else
	cout << "\ncant add this account ; because it is  exist\n";
    }
  else
    cout << "\ncant add this account ; because it is incomplete account\n";
}

void UserAccountListType::deleteUserAccount (string id)
{
  if (IsUserIdExist (id))
    {				//O(n)
      UserAccountNode* current;
	UserAccountNode* trailCurrent;
	bool found;
	if (first->user_account.getUserId().compare(id) == 0) {
		current = first;
		first = first->link;
		counter--;
		if (first == NULL)
			last = NULL;
		delete current;
	}
	else if (last->user_account.getUserId().compare(id) == 0) {
		UserAccountNode* second_last = first;
		while (second_last->link->link != NULL)
			second_last = second_last->link;
 
		delete (second_last->link);
		second_last->link = NULL;
	}
	else {
		found = false;
		trailCurrent = first;
		current = first->link;
		while (current != NULL /* && found != true*/) {
			if (current->user_account.getUserId().compare(id) == 0) {
				found = true;
				break;
			}
			else {
				trailCurrent = current;
				current = current->link;
			}
		}
		if (found == true) {
			if (last == current) {
				last = trailCurrent;
				delete current;
			}
			else {
				trailCurrent->link = current->link;
				counter--;
				delete current;
			}
 
		}
		
	}
}
else
			cout << "The item to be deleted is not in "
			<< "the list." << endl;
}
void UserAccountListType::printInfo_of_UserId (string id)
{
  if (IsUserIdExist (id))
    {				//O(n)
      UserAccountNode *c;
      c = first;
      bool found = false;
      while (found != true)
	{
	  if ((c->user_account.getUserId ()).compare (id) == 0)
	    {
	      c->user_account.printUserInfo ();
	      found = true;
	    }
	  else
	    c = c->link;
	}
    }
  else
    cout << "\nthis account is not existed\n";
}

int main ()
{

  UserAccountListType list;
  /* string fname[3] = { "osama", "ahmed", "yara" };
  string lname[3] = { "yousuf", "raed", "essa" };
  string id[3] = { "osama_02", "ahmed19", "yara1990" };
  string password[3] = { "osama#1", "aread$2", "yara#9" };
  for (int i = 0; i < 3; i++)
    {
      UserAccountType a (id[i], password[i], fname[i], lname[i]);
      list.insertUserAccount (a);
    }
  list.print ();

  list.printInfo_of_UserId ("yara1990");

  if (list.IsUserIdExist ("ali23"))	//isnt exist
    cout << "\nthe account founded\n";
  else
    cout << "\nthe account is not existed\n";

  UserAccountType b ("ali12", "ali12#", "ali", "ahmed");	//incorrect password
  list.insertUserAccount (b);

  list.deleteUserAccount ("osama_02");
  list.printInfo_of_UserId ("osama_02");*/
  string namef,namel,id,pass;
  cout<<"enter first name :"<<endl;
  cin>>namef;
  cout<<"enter last name :"<<endl;
  cin>>namel;
  cout<<"enter id :"<<endl;
  cin>>id;
  cout<<"enter password :"<<endl;
  cin>>pass;
  UserAccountType a(id,pass,namef,namel);
  list.insertUserAccount (a);
  list.print ();
}