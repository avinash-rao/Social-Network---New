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
};

class Validation {
	public:
        Validation() {}
		User validateUserLogin(User[], string email, string password);
		int validateEmail(string email);
        int validateAge(int age);
        int validatePassword(string password);
};

class Pages {
    private:
		User currentUser;
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
    
}

void Pages::landingPage() {
    while(true) {
        string options[] = {"Login", "Signup", "Exit"};
        showMenuOptions(options, 3);
        int choice;
        cout << endl << endl << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: this->loginPage(); break;
            case 2: this->signupPage(); break;
            case 3: exit(0); break;
        }

    }
}

// Page 2
void Pages::loginPage() {
    cout << "\n\t\t Login Page\n";
    string email, pswd;
    do {
        cout << "Enter your email: ";
        cin >> email;
    } while(validation.validateEmail(email) != 0);

    do {
        cout << "Password: ";
        cin >> pswd;
    } while(validation.validatePassword(pswd) != 0);    
}

// Page 3
void Pages::signupPage() {
	while(true) {

    }
}

// Page 4
void Pages::userHomePage() {
	
}

// Page 5
void Pages::editProfilePage() {
	
}

// Page 6
void Pages::friendRequestPage() {
	
}

// *********************************************************************************
// ******************************* Class Validation ********************************
// *********************************************************************************

User Validation::validateUserLogin(User allUsers[], string email, string password) {
    return allUsers[0];
}

int Validation::validateEmail(string email) {
    return 0;
}

int Validation::validateAge(int age) {
    return 0;
}

int Validation::validatePassword(string password) {
    return 0;
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
