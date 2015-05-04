#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget> 
#include <QRadioButton>
#include <QComboBox>
#include <QMessageBox>

#include <string>
#include <vector>

#include "main_window.h"
#include "newUser_window.h"
// #include "cart_window.h"
#include "../msort.h"
#include "../datastore.h"
#include "../db_parser.h"

class LoginWindow : public QWidget
{
	Q_OBJECT
public:
	LoginWindow();
	// LoginWindow(std::vector<Product*>& cart, std::string userName);
	LoginWindow(std::string input);
	~LoginWindow();

public slots:
	void checkLogin();
	void openMainWindow();
	void openNewUserWindow();
	void falseUsername(std::string);
	void incorrectPW(std::string);

private:

	MyDataStore ds_;

	MainWindow* myMainWindow;
	NewUserWindow* myNewUserWindow;

	// std::string userName_;
	User* currentUser;

	// // UI

	// MyDataStore* ds_;
	// std::string userName_;

	// double balance;

	std::vector<Product*> cart_;

	// Overall layout
	QVBoxLayout* overallLayout;

	// Other Layouts
	QHBoxLayout* lastRowLayout;

	// *********FIRST ROW*********
	QLabel* welcomeLabel;

	// *********SECOND ROW*********
	QLabel* usernameLabel;

	// *********THIRD ROW*********
	QLineEdit* usernameInput;

	// *********FOURTH ROW*********
	QLabel* passwordLabel;

	// *********FIFTH ROW*********
	QLineEdit* passwordInput;

	// *********SIXTH ROW*********
	QPushButton* loginButton;

	// *********SEVENTH ROW*********
	QPushButton* newUserButton;

	// *********EIGTH ROW*********
	QPushButton* quitButton;

};

#endif