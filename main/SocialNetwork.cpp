// ************************** PROBLEM STATEMENT ***************************
//  Modelling a social networking site 
//     o Simulate the implementation of a social networking site 
//     o User management - add/delete/modify users (Name, Age, Location) 
//     o Manage friend requests - make a request, accept/reject request 
//     o Find out the distance between any 2 given users 


#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include<bits/stdc++.h>
#include <cstring>
#include <regex>
#include<unistd.h>

using namespace std;

class User {
    private: 
      string email;
      string name;
      int age;
      string location;
      string password;

    public:
      list<User*> friendsList;

      User() {}
      User(string email, string name, int age, string location, string password) {
          this->email = email;
          this->name = name;
          this->age = age;
          this->location = location;
          this->password = password;
      }

      void setEmail(string email);
      void setName(string name);
      void setAge(int age);
      void setLocation(string location);
      void setPassword(string password);

      string getEmail();
      string getName();
      int getAge();
      string getLocation();
      string getPassword();

      void addFriend(User* user);
      void displayFriendsList();
};


typedef struct UserNode
{
  	User user;
  	UserNode *next;
}UserNode;

// Linked list to store UserNodes
class User_LinkedList
{
  private:
    UserNode *head,*tail;
  public:
    UserNode* getHead() {
        return head;
    }

    User_LinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void push_back(User user)
    {
        UserNode *userNode = new UserNode;
        userNode->user = user;
        userNode->next = NULL;

        if(head == NULL)
        {
            head = userNode;
            tail = userNode;
        }
        else
        {
            tail->next = userNode;
            tail = tail->next;
        }
    }
};

class Validation {
	public:
        Validation() {}
		User* validateUserLogin(User_LinkedList allUsers, string email, string password);
		int validateEmail(string email);
        int validateSignUpEmail(User_LinkedList allUsers, string email);
        int validateInt(int choice);
        int validateAge(int age);
        int validatePassword(string password);
        int validateString(string);
        User* getUser(User_LinkedList, string);
        int findDistanceBetweenUsers(User_LinkedList allUsers, User* user1, User* user2);
        bool containsElement(vector<string> vc, string element);
};

class Pages {
    private:
		User* currentUser;
        User_LinkedList allUsers;
        Validation validation;
	public:
        Pages() {}
		void textWebsiteName();
		void textDevelopers();
        void showMenuOptions(string *options, int size);
		void landingPage();
		void loginPage();
		void signupPage();
		void userHomePage();
		void editProfilePage();
		void friendRequestPage();
        void findDistancePage();
};


// *********************************************************************************
// ******************************* Main Function ***********************************
// *********************************************************************************

int main() {
    Pages pages;
    pages.landingPage();
    return 0;
}



// *********************************************************************************
// ******************************* Class Pages *************************************
// *********************************************************************************

void Pages::textWebsiteName() {
	cout<<"\n \t\t\t FakeBook";
	cout<<"\n \t\t\t----------\n\n";
}

void Pages::textDevelopers() {
	cout<<"Developers - Avinash, Chetali, Garima, Jeet, Utpal \n";
}

void Pages::showMenuOptions(string *options, int size) {
    system("cls");
    this->textWebsiteName();
    this->textDevelopers();
    cout << endl;
    for (int i = 1; i <= size; i++) {
        cout <<  i << ". " << options[i-1] << "\t";
    }
    cout << endl << endl;
}

void Pages::landingPage() {
    while(true) {
        string options[] = {"Login", "Signup", "Exit"};
        int optionSize = 3;
        showMenuOptions(options, optionSize);
        int choice; string choicee;
        do {
            retrychoice1:
            int count=0;
            cout << "Enter your choice: ";
            cin >> choicee;
            for (int i=0; i<=choicee.length(); i++) {
                if (isdigit(choicee[i]))
               count ++;
             }
             if(count==choicee.length()) {
                stringstream convert(choicee);
                convert>>choice;
             }
            else {
                cout<<"Enter digit only!!"<<endl;
                goto retrychoice1;
             }

            switch(choice) {
                case 1: this->loginPage();
                        this->userHomePage();
                        showMenuOptions(options, optionSize);
                        break;
                case 2: this->signupPage(); 
                        this->userHomePage();
                        showMenuOptions(options, optionSize);
                        break;
                case 3: exit(0); break;
                default: cout << endl << "Please provide valid choice" << endl;
            }
        }while(true);
    }
}

// Page 2
void Pages::loginPage() {
    // showMenuOptions({}, 0);
    system("cls");
    cout << "\n\t\t Login Page\n";
    string email, pswd;
    User* user;

    string con="y";
    while(con.compare("y")==0){
            cout << "Enter your email: ";
            cin >> email;
            cout << "Password: ";
            cin >> pswd;
            user = validation.validateUserLogin(allUsers, email, pswd);
            if(user==NULL){
                cout<<"Your credentials are wrong. Do you want to retry? (y/n): ";
                cin>>con;
                transform(con.begin(), con.end(), con.begin(), ::tolower);
            }
            else{
                currentUser = user;
                return;
            }
        
    }
    landingPage();
}

// Page 3
void Pages::signupPage() {
    // showMenuOptions(, 0);
    system("cls");
	cout << "\n\t\t Signup Page\n";
    string email, name, location, pswd, agee;
    int age;
    string con="y"; int GoOn=0;
    while(con.compare("y")==0){
        cout << "Enter your email: ";
        getline(cin>>ws, email);

        cout << "Enter your name: ";
        getline(cin>>ws, name);

        retry:
        int count=0;
        cout << "Enter your age: ";
        cin >> agee;
        for (int i=0; i<=agee.length(); i++) {
            if (isdigit(agee[i]))
            count ++;
        }
        if(count==agee.length()) {
        stringstream convert(agee);
        convert>>age;
        }
        else {
        cout<<"Enter digits only!!"<<endl;
        goto retry;
        }

        cout << "Enter your location: ";
        getline(cin>>ws, location);

        cout << "Password: ";
        getline(cin>>ws, pswd);

        if(validation.validateSignUpEmail(allUsers, email)!=0){
            cout<<"\n Invalid email ";
            GoOn=1;
        }
        if(validation.validateString(name)!=0){
            cout<<"\n Invalid Name ";//no numbers
            GoOn=1;
        }
        if(validation.validateAge(age)!=0){
            cout<<"\n Age must be between 14 to 95 ";//14 to 95
            GoOn=1;
        }
        if(validation.validatePassword(pswd)!=0){
            cout<<"\n Minimum 6 char required in Password ";
            GoOn=1;
        }

        if(GoOn==0){
            User tempUser(email, name, age, location, pswd);
            allUsers.push_back(tempUser);
            currentUser = validation.validateUserLogin(allUsers, email, pswd);
            return;
        }
        else{
            GoOn = 0;
            cout<<"\n Do you want to retry? (y / Press any key to exit)) :";
            cin>>con;
            transform(con.begin(), con.end(), con.begin(), ::tolower);
        }
        
    }
    landingPage();

    User tempUser(email, name, age, location, pswd);
    allUsers.push_back(tempUser);
    currentUser = validation.validateUserLogin(allUsers, email, pswd);
    return;
}

// Page 4
void Pages::userHomePage() {
    string options[] = {"Friend Request", "Edit Profile Page", "Display friends", "Find distance", "Logout"};
    int optionSize = 5;
    showMenuOptions(options, optionSize);
	cout << "----------Welcome " << currentUser->getName() << "-------------" << endl << endl;
    int choice; string choicee;
    do {
        retrychoice2:
            int count=0;
            cout << "Enter your choice: ";
            cin >> choicee;
            for (int i=0; i<=choicee.length(); i++) {
                if (isdigit(choicee[i]))
               count ++;
             }
             if(count==choicee.length()) {
                stringstream convert(choicee);
                convert>>choice;
             }
            else {
                cout<<"Enter digit only!!"<<endl;
                goto retrychoice2;
             }
        switch(choice) {
            case 1: friendRequestPage();
                    showMenuOptions(options, optionSize);
                    break;
            case 2: editProfilePage(); 
                    showMenuOptions(options, optionSize);
                    break;
            case 3: if(currentUser->friendsList.size() == 0) {
                        cout << endl << "You have no friends added. Go to 'Friend Request' page to add friends" << endl;
                    } else {
                        cout << endl << "Your friend list: ";
                        currentUser->displayFriendsList(); 
                    }                   
                    cout << endl;     
                    break;
            case 4: findDistancePage(); 
                    showMenuOptions(options, optionSize);
                    break;
            case 5: return;
            default: cout << "Please provide valid choice";
        }
    }while(true);
}

// Page 5
void Pages::editProfilePage() {
    cout << "----------Welcome " << currentUser->getName() << "-------------" << endl;
    cout << "---------------- Edit Profile Page---------------" << endl << endl;
    string temp;
    int choice, tempAge, userInput=0;string choicee;
    string agee;
    do {
        string options[] = {"Name: "+currentUser->getName(), 
                        "Age: " + to_string(currentUser->getAge()), 
                        "Location: " + currentUser->getLocation(), 
                        "Password", 
                        "Go back"};
         int optionSize = 5;
        showMenuOptions(options, optionSize);
        while(true) {
            retrychoice3:
            int count=0;
            cout << "Enter your choice: ";
            cin >> choicee;
            for (int i=0; i<=choicee.length(); i++) {
                if (isdigit(choicee[i]))
               count ++;
             }
             if(count==choicee.length()) {
                stringstream convert(choicee);
                convert>>choice;
             }
            else {
                cout<<"Enter digit only!!"<<endl;
                goto retrychoice3;
             }
            if(validation.validateInt(choice)==1){
                break;
            }
            else{
                cout<<"choice between 1 to 5 only!";
            }
        }
        int count1;
        
        switch(choice) {
            case 1: 
                cout << "Enter Name: ";
                cin >> temp;
                validation.validateString(temp);
                currentUser->setName(temp);
                cout << "Name updated successfully";
                sleep(1);
                break;
            case 2: 
                retry1:
                  count1=0;
                  cout << "Enter your age: ";
                  cin >> agee;
                 for (int i=0; i<=agee.length(); i++) {
                       if (isdigit(agee[i]))
                       count1 ++;
                }
                if(count1==agee.length()) {
                    stringstream convert(agee);
                    convert>>tempAge;
                }
                else {
                    cout<<"Enter digits only!!"<<endl;
                    goto retry1;
                }
                validation.validateAge(tempAge);
                currentUser->setAge(tempAge);
                cout << "Age updated successfully";
                sleep(1);
                break;
            case 3: 
                cout << "Enter location: ";
                cin >> temp;
                currentUser->setLocation(temp);
                cout << "Location updated successfully";
                sleep(1);
                break;
            case 4: 
                cout << "Enter current password: ";
                getline(cin>>ws, temp);
                if(currentUser->getPassword().compare(temp) == 0) {
                    cout << "Enter new password: ";
                    getline(cin>>ws, temp);
                    validation.validatePassword(temp);
                    currentUser->setPassword(temp);
                    cout << "Password updated successfully";
                    sleep(1);
                } 
                else {
                    cout << "Incorrect current password" << endl;
                    sleep(1);
                }
                break;
            case 5: 
                return;
            default: cout << "Please provide valid choice" << endl; sleep(1);
        }
    } while(true);
}

// Page 6
void Pages::friendRequestPage() {
    string options[1];
	showMenuOptions(options, 0);
    cout << " \t ----------Welcome " << currentUser->getName() << "-------------" << endl<< endl;
    cout << "---------------- Friend Request Page---------------" << endl << endl;
    string email;
    cout << "Enter user's email: ";
    getline(cin>>ws, email);
    if(validation.validateEmail(email) == 0) {
        int uniqueFriend = 1;
        User* friendUser = validation.getUser(allUsers, email);
        if(friendUser != NULL) {
            for(auto i = currentUser->friendsList.begin(); i != currentUser->friendsList.end(); ++i) {
                User* tempUser = *i;
                if(email == tempUser->getEmail()) {
                    uniqueFriend = 0;
                    cout << "Already your friend" << endl;
                    sleep(1);
                }
            }

            // UserNode* usernode = allUsers.getHead();
            // while (usernode != NULL)
            // {
            string tempEmail = currentUser->getEmail();
            if(tempEmail.compare(email) == 0) {
                uniqueFriend = 2;
                cout << "You can not send friend request to yourself.";
                sleep(1);
            }
            //     usernode = usernode->next;
            // }

            if(uniqueFriend == 1) {
                currentUser->addFriend(friendUser);
                cout << friendUser->getEmail() << " has been added to your friend list :)" << endl;
                sleep(1);
            }

        } 
        else {
            cout << "No user with this email" << endl;
            sleep(1);
        }
    }
    else {
        cout << "Invalid email" << endl;
        sleep(1);
    }
    return;
}

void Pages::findDistancePage() {
    string options[1];
	showMenuOptions(options, 0);
    cout << " \t ----------Welcome " << currentUser->getName() << "-------------" << endl<< endl;
    cout << "---------------- Find Distance Page---------------" << endl << endl;
    string email;
    cout << "Enter user's email: ";
    getline(cin>>ws, email);
    if(validation.validateEmail(email) == 0) {
        User* friendUser = validation.getUser(allUsers, email);
        if(friendUser != NULL) {
            int distance = validation.findDistanceBetweenUsers(allUsers, currentUser, friendUser);
            if (distance == -1) 
                cout << "Not linked by any of your friend" << endl << endl;
            else
                cout << "Distance: " << distance << endl << endl;
        } 
        else {
            cout << "No user with this email" << endl;
        }
    }
    else {
        cout << "Invalid email" << endl;
    }
    cout << "Press any key to continue";
    char temp;
    cin >> temp;
    return;
}

// *********************************************************************************
// ******************************* Class Validation ********************************
// *********************************************************************************

User* Validation::validateUserLogin(User_LinkedList allUsers, string email, string password) {
    UserNode* usernode = allUsers.getHead();
    while (usernode != NULL)
    {
        string tempEmail = usernode->user.getEmail();
        string tempPassword = usernode->user.getPassword();
        if(tempEmail.compare(email) == 0 && tempPassword.compare(password) == 0) {
            return &(usernode->user);
        }
        usernode = usernode->next;
    }
    return NULL;
}

int Validation::validateSignUpEmail(User_LinkedList allUsers, string email) {
    if(validateEmail(email) == 0) {
        // Traverse all the users that is presently in queue
        UserNode* usernode = allUsers.getHead();
        while (usernode != NULL)
        {
            string tempEmail = usernode->user.getEmail();
            if(tempEmail.compare(email) == 0) {
                cout << "This email is already registered.";
                sleep(1);
                return -1;
            }
            usernode = usernode->next;
        }
        return 0;
    }
    else {
        return -1;
    }
}

int Validation::validateEmail(string email) {
   const std::regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

   // try to match the string with the regular expression
  //  return std::regex_match(email, pattern);
   if(std::regex_match(email, pattern)){
       return 0;
   }
   else{
       return -1;
   }
}

int Validation::validateInt(int choice) {
    if(choice>=1 && choice<=5)
        return 1;
    else {
        return 0;
    }
}

int Validation::validateAge(int age) {
    if(age>=12 && age<=95)
        return 0;
    else {
        return -1;
    }
}

int Validation::validatePassword(string password) {
    if(password.length()<=5){
        return -1;
    }
    else{
        return 0;
    }
}

int Validation::validateString(string str) {
    int count=0;
    for (int i=0; i<=str.length(); i++)
    {
        if (isalpha(str[i]))
            count ++;
    }
    if(count==str.length()){
        return 0;
    }
    else{
        return -1;
    }
}

User* Validation::getUser(User_LinkedList allUsers, string email) {
    UserNode* usernode = allUsers.getHead();
    while (usernode != NULL)
    {
        string tempEmail = usernode->user.getEmail();
        if(tempEmail.compare(email) == 0) {
            return &(usernode->user);
        }
        usernode = usernode->next;
    }
    return NULL;
}

int Validation::findDistanceBetweenUsers(User_LinkedList allUsers, User* user1, User* user2) {

    int distance = 0;
    vector<string> checkedUsers;
    list<User*> queue;

    queue.push_back(user1);
    
    while(!queue.empty()) {
        // Traverse all the users that is presently in queue
        int initialSize = queue.size();
        for(int i=0; i < initialSize; i++) {
            User* currentUser = queue.front();
            queue.pop_front();

            //check currentUser's email against required email
            if (currentUser->getEmail().compare(user2->getEmail()) == 0) {
                return distance;
            }
            checkedUsers.push_back(currentUser->getEmail());

            // Add all the unchecked friends of currentUser to queue
            for(auto i = currentUser->friendsList.begin(); i != currentUser->friendsList.end(); ++i) {
                User* tempUser = *i;
                bool tempUserIsAlreadyChecked = containsElement(checkedUsers, tempUser->getEmail());
                if(!tempUserIsAlreadyChecked) {
                    queue.push_back(tempUser);
                }
            }
        }
        distance++;
    }
    return -1;
}

bool Validation::containsElement(vector<string> vc, string element) {
    for(auto it = vc.begin(); it != vc.end(); it++) {
        if((*it).compare(element) == 0) {
            return true;
        }
    }
    return false;
}

// *********************************************************************************
// ******************************* Class User **************************************
// *********************************************************************************


//other functions here


string User::getEmail() {
    return email;
}


string User::getName() {
    return name;
}

int User::getAge() {
    return age;
}

string User::getLocation() {
    return location;
}

string User::getPassword() {
    return password;
}

void User::setEmail(string email) {

}

void User::setName(string name) {
    this->name = name;
}

void User::setLocation(string loc) {
    this->location = loc;
}

void User::setAge(int age) {
    this->age = age;
}

void User::setPassword(string pswd) {
    this->password = pswd;
}

void User::addFriend(User* friendUser) {
    friendsList.push_back(friendUser);
    friendUser->friendsList.push_back(this);
}

void User::displayFriendsList() {
    for(auto i = friendsList.begin(); i != friendsList.end(); ++i) {
        cout << (*i)->getName() << "\t" ;
    }
    cout << endl;
    return;
}
