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

using namespace std;

class User {
    private: 
      string email;
      string name;
      int age;
      string location;
      string password;

    public:
      vector<User> friendsList;

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

class Validation {
	public:
        Validation() {}
		int validateUserLogin(vector<User> allUsers, string email, string password);
		int validateEmail(string email);
        int validateAge(int age);
        int validatePassword(string password);
        int validateString(string);
        User* getUser(vector<User>*, string);
};

class Pages {
    private:
		int currentUser;
        vector<User> allUsers;
        Validation validation;
	public:
        Pages() {}
		void textWebsiteName();
		void textDevelopers();
        int showMenuOptions(string *options, int size);
		// void userChoice(int);
		// void checkForMenuOption(int, string);

		void landingPage();
		void loginPage();
		void signupPage();
		void userHomePage();
		void editProfilePage();
		void friendRequestPage();
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

int Pages::showMenuOptions(string *options, int size) {
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
        int choice;
        do {
            cout << "Enter your choice: ";
            cin >> choice;

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
    int userIndex;
    do {
        do {
            cout << "Enter your email: ";
            cin >> email;
        } while(validation.validateEmail(email) != 0);

        do {
            cout << "Password: ";
            cin >> pswd;
        } while(validation.validatePassword(pswd) != 0);    
        userIndex = validation.validateUserLogin(allUsers, email, pswd);
    } while(userIndex == -1);
    currentUser = userIndex;
    return;
}

// Page 3
void Pages::signupPage() {
    // showMenuOptions(, 0);
    system("cls");
	cout << "\n\t\t Signup Page\n";
    string email, name, location, pswd;
    int age;
    do {
        cout << "Enter your email: ";
        getline(cin>>ws, email);
    } while(validation.validateEmail(email) != 0);

    do {
        cout << "Enter your name: ";
        getline(cin>>ws, name);
    } while(validation.validateString(name) != 0);

    do {
        cout << "Enter your age: ";
        cin >> age;
    } while(validation.validateAge(age) != 0);

    cout << "Enter your location: ";
    getline(cin>>ws, location);

    do {
        cout << "Password: ";
        getline(cin>>ws, pswd);
    } while(validation.validatePassword(pswd) != 0);    

    User tempUser(email, name, age, location, pswd);
    allUsers.push_back(tempUser);
    currentUser = validation.validateUserLogin(allUsers, email, pswd);
    return;
}

// Page 4
void Pages::userHomePage() {
    string options[] = {"Friend Request", "Edit Profile Page", "Display friends", "Logout"};
    int optionSize = 4;
    showMenuOptions(options, optionSize);
	cout << "----------Welcome " << allUsers[currentUser].getName() << "-------------" << endl;
    int choice;
    do {
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: friendRequestPage();
                    showMenuOptions(options, optionSize);
                    break;
            case 2: editProfilePage(); 
                    showMenuOptions(options, optionSize);
                    break;
            case 3: allUsers[currentUser].displayFriendsList(); break;
            case 4: return;
            default: cout << "Please provide valid choice";
        }
    }while(true);
}

// Page 5
void Pages::editProfilePage() {
    string options[] = {"Name: "+allUsers[currentUser].getName(), 
                        "Age: " + allUsers[currentUser].getAge(), 
                        "Location: " + allUsers[currentUser].getLocation(), 
                        "Password", 
                        "Go back"};
    int optionSize = 5;
    string temp;
    int choice, tempAge;
    do {
        showMenuOptions(options, optionSize);
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: 
                cout << "Enter Name: ";
                cin >> temp;
                validation.validateString(temp);
                allUsers[currentUser].setName(temp);
                cout << "Name updated successfully";
                break;
            case 2: 
                cout << "Enter age: ";
                cin >> tempAge;
                validation.validateAge(tempAge);
                allUsers[currentUser].setAge(tempAge);
                cout << "Age updated successfully";
                break;
            case 3: 
                cout << "Enter location: ";
                cin >> temp;
                allUsers[currentUser].setLocation(temp);
                cout << "Location updated successfully";
                break;
            case 4: 
                cout << "Enter current password: ";
                getline(cin>>ws, temp);
                if(allUsers[currentUser].getPassword().compare(temp) == 0) {
                    cout << "Enter new password: ";
                    getline(cin>>ws, temp);
                    validation.validatePassword(temp);
                    allUsers[currentUser].setPassword(temp);
                    cout << "Password updated successfully";
                } 
                else {
                    cout << "Incorrect current password" << endl;
                }
                break;
            case 5: 
                return;
            default: cout << "Please provide valid choice" << endl;
        }
    } while(true);
}

// Page 6
void Pages::friendRequestPage() {
    string options[1];
	showMenuOptions(options, 0);
    cout << "---------------- Friend Request Page---------------" << endl << endl;
    string email;
    cout << "Enter user's email: ";
    getline(cin>>ws, email);
    if(validation.validateEmail(email) == 0) {
        User* friendUser = validation.getUser(&allUsers, email);
        if(friendUser != NULL) {
            allUsers[currentUser].addFriend(friendUser);
        } 
        else {
            cout << "No user with this email" << endl;
        }
    }
    else {
        cout << "Invalid email" << endl;
    }
    return;
}

// *********************************************************************************
// ******************************* Class Validation ********************************
// *********************************************************************************

int Validation::validateUserLogin(vector<User> allUsers, string email, string password) {
    for (int i=0; i < allUsers.size(); ++i) {
        User tempUser = allUsers[i];
        if(email.compare(tempUser.getEmail()) == 0 && password.compare(tempUser.getPassword()) == 0) {
            return i;
        } 
    }
    return -1;
}

int Validation::validateEmail(string email) {
    return 0;
}

int Validation::validateAge(int age) {
    string tempAge = to_string(age);
    if(age>=12 && age<=95)
        return 0;
    else {
        cout << "Age must be between 12 to 95.";
        return -1;
    }
}

int Validation::validatePassword(string password) {
    return 0;
}

int Validation::validateString(string str) {
    return 0;
}

User* Validation::getUser(vector<User>* allUsersPtr, string email) {
    for (int i=0; i < (*allUsersPtr).size(); ++i) {
        User* userPtr = &(*allUsersPtr)[i];
        if(email.compare(userPtr->getEmail()) == 0) {
            return userPtr;
        } 
    }
    return NULL;
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
    friendsList.push_back(*friendUser);
    (*friendUser).friendsList.push_back(*this);
}

void User::displayFriendsList() {
    cout << endl;
    for (int i=0; i<friendsList.size(); i++) {
        cout << friendsList[i].getName() << "\t";
    }
    cout << endl;
    return;
}