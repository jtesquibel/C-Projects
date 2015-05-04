#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <string>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../util.h"
#include "login_window.h"

LoginWindow::LoginWindow()
{

}

// LoginWindow::LoginWindow(std::vector<Product*>& cart, std::string userName)
LoginWindow::LoginWindow(std::string input)
{

	srand (time(NULL));

	// Instantiate the parser
  	DBParser parser;

 	// Instantiate the individual product parsers we want
  	parser.addProductParser(new ProductBookParser);
  	parser.addProductParser(new ProductClothingParser);
  	parser.addProductParser(new ProductMovieParser);

  	// Now parse the database to populate the DataStore 
  	if( parser.parse(input, ds_) )
  	{
    	std::cerr << "Error parsing!" << std::endl;
  	}

	// Title
	setWindowTitle("Login");

	// std::cout << "In login window" << std::endl;
	// ds_ = &ds;
	// userName_ = userName;
	// balance = ds_->getUser(userName)->getBalance();

	// std::cout << "In cart" << std::endl;


	// Overall layout
	overallLayout = new QVBoxLayout();

	// *********FIRST ROW*********
	// Layout
	welcomeLabel = new QLabel("Welcome");
	overallLayout->addWidget(welcomeLabel);

	// *********SECOND ROW*********
	usernameLabel = new QLabel("Username");
	overallLayout->addWidget(usernameLabel);

	// *********THIRD ROW*********
	usernameInput = new QLineEdit();
	overallLayout->addWidget(usernameInput);

	// *********FOURTH ROW*********
	passwordLabel = new QLabel("Password");
	overallLayout->addWidget(passwordLabel);
	
	// *********FIFTH ROW*********
	passwordInput = new QLineEdit();
	overallLayout->addWidget(passwordInput);

	// *********SIXTH ROW*********
	loginButton = new QPushButton("Login");
	// connect(loginButton, SIGNAL(clicked()), this, SLOT(openMainWindow()));
	overallLayout->addWidget(loginButton);

	// *********SEVENTH ROW*********
	newUserButton = new QPushButton("New User? Create An Account");
	overallLayout->addWidget(newUserButton);

	// *********EIGTH ROW*********
	quitButton = new QPushButton("Quit");
	overallLayout->addWidget(quitButton);

	connect(loginButton, SIGNAL(clicked()), this, SLOT(checkLogin()));
	connect(newUserButton, SIGNAL(clicked()), this, SLOT(openNewUserWindow()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

	// currentUser = ds_.getUser(usernameInput->text().toStdString());

	setLayout(overallLayout);

}

LoginWindow::~LoginWindow()
{

}

void LoginWindow::checkLogin() 
{
	std::string userName_ = usernameInput->text().toStdString();

	bool found = false;
	bool correct = false;
	long long num = 0;
	
	unsigned int digits[4] = {0};
	int count = 2;
	for (unsigned int i = 0; i < ds_.getUsers().size(); i++)
	{
		if (ds_.getUsers()[i]->getName() == userName_)
		{
			found = true;
			std::string password_ = passwordInput->text().toStdString();
			
			std::cout << password_.size() << std::endl;
			for (int j = 0; j < password_.size(); j++)
			{
				char c = password_[password_.size()-j-1];
				int letter = c;
				long long temp = c * pow(128, j);
				num += temp;
			}

			digits[3] = num % 65521;
			while (num/65521 != 0)
			{
				digits[count] = (num/65521) % 65521;
				num = num/65521;
				count--;
			}


			for (int u = 0; u < 4; u++)
			{
				std::cout << digits[u] << " ";
				std::cout << rand() << " ";
			}
			std::cout << std::endl;


			long long num2 = (45912 * digits[0] + 35511 * digits[1] + 65169 * digits[2] + 4625 * digits[3]) % 65521;
			num2 = num2 % 65521;


			// check for right password
			if (ds_.getUser(userName_)->getPassword() == num2)
			{
				correct = true;
				openMainWindow();
			}
			else
			{
				incorrectPW(userName_);
			}
		}
	}

	if (found == false)
	{
		falseUsername(userName_);
		// usernameInput->clear();	// this is optional
	}
	
}

void LoginWindow::openMainWindow()
{
	std::string userName_ = usernameInput->text().toStdString();
	myMainWindow = new MainWindow(ds_, userName_);
	myMainWindow->show();
}

void LoginWindow::openNewUserWindow()
{
	std::string userName_ = usernameInput->text().toStdString();
	bool found = false;
	for (unsigned int i = 0; i < ds_.getUsers().size(); i++)
	{
		if (ds_.getUsers()[i]->getName() == userName_)
		{
			QString qstr = QString::fromStdString("This username already has an account!");
			QMessageBox::about(this, "Error!", qstr);
			found = true;
		}
	}

	bool space = false;
	std::string password_ = passwordInput->text().toStdString();
	if (password_.size() > 8)
	{
		QString qstr = QString::fromStdString("Password is too long!");
		QMessageBox::about(this, "Error!", qstr);
		return;
	}

	for (unsigned int i = 0; i < password_.size(); i++)
	{
		char c = password_[i];
		if (c == ' ')
		{
			QString qstr = QString::fromStdString("Cannot have white spaces in password!");
			QMessageBox::about(this, "Error!", qstr);
			space = true;
		}
	}

	if (found == false && space == false)
	{
		myNewUserWindow = new NewUserWindow(ds_, userName_, password_);
		myNewUserWindow->show();
	}
}	

void LoginWindow::falseUsername(std::string name)
{
	std::string s = "Invalid username! ";
	std::string quote = "\"";
	std::string m = " does not exist in the database";
	std::string m3 = s + quote + name + quote + m;

	QString qstr = QString::fromStdString(m3);
	QMessageBox::about(this, "Error!", qstr);
}

void LoginWindow::incorrectPW(std::string name)
{
	std::string s = "Incorrect password for ";
	std::string quote = "\"";
	std::string m3 = s + quote + name + quote;

	QString qstr = QString::fromStdString(m3);
	QMessageBox::about(this, "Error!", qstr);
}

