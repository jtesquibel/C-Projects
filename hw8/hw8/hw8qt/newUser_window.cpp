#include <vector>
#include <sstream>
#include <math.h>
#include "newUser_window.h"

NewUserWindow::NewUserWindow()
{

}

// NewUserWindow::NewUserWindow(std::vector<Product*>& cart, std::string userName)
NewUserWindow::NewUserWindow(MyDataStore &ds, std::string userName, std::string password)
{
	// Title
	setWindowTitle("New User");

	std::cout << "In new user" << std::endl;
	ds_ = &ds;
	userName_ = userName;
	password_ = password;

	std::cout << "password = " << password_ << std::endl;


	long long num = 0;
	unsigned int digits[4] = {0};
	int count = 2;

	for (int j = 0; j < password_.size(); j++)
	{
		char c = password_[password_.size()-j-1];
		std::cout << "after" << std::endl;
		std::cout << c << std::endl;
		int letter = c;
		long long temp = c * pow(128, j);
		num += temp;
	}

	std::cout << "out" << std::endl;
	std:: cout << "num = " << num << std::endl;

	digits[3] = num % 65521;
	while (num/65521 != 0)
	{
		std::cout << "in while" << std::endl;
		digits[count] = (num/65521) % 65521;
		num = num/65521;
		count--;
	}

	std::cout << "after while" << std::endl;

	for (int u = 0; u < 4; u++)
	{
		std::cout << digits[u] << " ";
		std::cout << rand() << " ";
	}
	std::cout << std::endl;


	long long num2 = (45912 * digits[0] + 35511 * digits[1] + 65169 * digits[2] + 4625 * digits[3]) % 65521;
	// int num2 = (rand() * digits[0]) + (rand() * digits[1]) + (rand() * digits[2]) + (rand() * digits[3]);
	num2 = num2 % 65521;

	password2_ = num2;

	std::cout << "password2 = " << password2_ << std::endl;



	// balance = ds_->getUser(userName)->getBalance();

	// std::cout << "In cart" << std::endl;

	// Overall layout
	overallLayout = new QVBoxLayout();

	// *********FIRST ROW*********
	ageLabel = new QLabel("Age");
	overallLayout->addWidget(ageLabel);

	// *********SECOND ROW*********
	ageInput = new QLineEdit();
	overallLayout->addWidget(ageInput);

	// *********THIRD ROW*********
	creditLabel = new QLabel("Credit Amount");
	overallLayout->addWidget(creditLabel);

	// *********FOURTH ROW*********
	creditInput = new QLineEdit();
	overallLayout->addWidget(creditInput);

	// *********FIFTH ROW*********
	createButton = new QPushButton("Create Your Account");
	connect(createButton, SIGNAL(clicked()), this, SLOT(checkValid()));
	overallLayout->addWidget(createButton);

	// *********SIXTH ROW*********
	goBackButton = new QPushButton("Back to Login");
	overallLayout->addWidget(goBackButton);

	
	connect(goBackButton, SIGNAL(clicked()), this, SLOT(close()));


	setLayout(overallLayout);

}

NewUserWindow::~NewUserWindow()
{

}

void NewUserWindow::checkValid()
{
	std::string temp = ageInput->text().toStdString();
	bool goodAge = true; bool goodCredit = true;
	int age;
	if (temp.size() == 0)
	{
		QString qstr = QString::fromStdString("No age provided!");
		QMessageBox::about(this, "Error!", qstr);
		return;
	}

	for (int i = 0; i < temp.size(); i++)
	{
		char c = temp[i];
		int d = c - '0';
		if (d < 0 || d > 9)
		{
			QString qstr = QString::fromStdString("Invalid age provided!");
			QMessageBox::about(this, "Error!", qstr);
			return;
		}
	}

	std::stringstream ss(temp);
	ss >> age;

	if (age < 0)
	{
		QString qstr = QString::fromStdString("Too young! You can't be 0 or less");
		QMessageBox::about(this, "Error!", qstr);
		goodAge = false;
	}

	if (age > 122)
	{
		QString qstr = QString::fromStdString("Too old! The oldest person ever was 122");
		QMessageBox::about(this, "Error!", qstr);
		goodAge = false;
	}
	

	std::string temp2 = creditInput->text().toStdString();
	if (temp2.size() < 0)
	{
		QString qstr = QString::fromStdString("No Credit Amount Provided!");
		QMessageBox::about(this, "Error!", qstr);
		goodCredit = false;
	}

	for (int i = 0; i < temp2.size(); i++)
	{
		char c = temp2[i];
		int d = c - '0';
		if (d < 0 || d > 9)
		{
			goodCredit = false;
			QString qstr = QString::fromStdString("Invalid Credit Amount Provided!");
			QMessageBox::about(this, "Error!", qstr);
			return;
		}
	}

	std::stringstream ss2(temp2);
	double creditAmount;
	ss2 >> creditAmount;

	// long long password2_;
	std::cout << "password 2 = " << password2_ << std::endl;

	if (goodAge == true && goodCredit == true)
	{
		User* u = new User(userName_, age, creditAmount, 0, password2_);
		ds_->addUser(u);
		QString qstr = QString::fromStdString("Successfully created account");
		QMessageBox::about(this, "Success!", qstr);
		close();
	}
}

