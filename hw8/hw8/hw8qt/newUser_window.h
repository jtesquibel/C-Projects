#ifndef NEWUSER_WINDOW_H
#define NEWUSER_WINDOW_H
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
#include "../product.h"
#include "../datastore.h"

class NewUserWindow : public QWidget
{
	Q_OBJECT
public:
	NewUserWindow();
	// NewUserWindow(std::vector<Product*>& cart, std::string userName);
	NewUserWindow(MyDataStore &ds, std::string, std::string);
	~NewUserWindow();

public slots:
	void checkValid();

private:

	// // UI

	MyDataStore* ds_;
	std::string userName_;
	std::string password_;

	long long password2_;

	double balance;

	std::vector<Product*> cart_;

	// Overall layout
	QVBoxLayout* overallLayout;

	// Other Layouts
	// QHBoxLayout* firstRowLayout;
	// QHBoxLayout* thirdRowLayout;

	// *********FIRST ROW*********
	QLabel* ageLabel;

	// *********SECOND ROW*********
	QLineEdit* ageInput;

	// *********THIRD ROW*********
	QLabel* creditLabel;;

	// *********FOURTH ROW*********
	QLineEdit* creditInput;

	// *********FIFTH ROW*********
	QPushButton* createButton;

	// *********SIXTH ROW*********
	QPushButton* goBackButton;

};

#endif