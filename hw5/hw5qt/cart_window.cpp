#include <vector>
#include <sstream>
#include "cart_window.h"

CartWindow::CartWindow()
{

}

// CartWindow::CartWindow(std::vector<Product*>& cart, std::string userName)
CartWindow::CartWindow(MyDataStore &ds, std::string userName)
{
	// Title
	setWindowTitle("Cart");

	std::cout << "In cart" << std::endl;
	ds_ = &ds;
	userName_ = userName;
	balance = ds_->getUser(userName)->getBalance();

	std::cout << "In cart" << std::endl;
	// Overall layout
	overallLayout = new QVBoxLayout();

	// *********FIRST ROW*********
	// Layout
	firstRowLayout = new QHBoxLayout();
	overallLayout->addLayout(firstRowLayout);

		// User Name Label
		QString qstr = QString::fromStdString(userName_);
		QString qstr10 = QString::fromStdString("'s cart");
		QString qstr2 = QString::fromStdString(": $");
		double bal = ds_->getUser(userName_)->getBalance();
		std::stringstream ss; std::string s;
		ss << balance;
		ss >> s;
		QString qstr3 = QString::fromStdString(s);
		QString qstr4 = QString::fromStdString(" left");
		QString qstr5 = qstr + qstr10 + qstr2 + qstr3 + qstr4;
		userNameLabel = new QLabel(qstr5);
		userNameLabel->setAlignment(Qt::AlignRight);
		overallLayout->addWidget(userNameLabel);
	
		// Cart Label;
		// cartLabel = new QLabel("Cart");
		// firstRowLayout->addWidget(cartLabel);

	// *********SECOND ROW*********
	cartListWidget = new QListWidget();
	std::cout << "In cart" << std::endl;
	std::cout << "Cart real size = " << ds_->getCart(userName_).size() << std::endl;
	// displayCart();
	for (unsigned int i = 0; i < ds_->getCart(userName_).size(); i++)
	{
		std::cout << "In cart" << std::endl;
		std::string prod = (ds_->getCart(userName_))[i]->displayString();
		QString qstr = QString::fromStdString(prod);
		cartListWidget->addItem(qstr);
	} 
	overallLayout->addWidget(cartListWidget);
	std::cout << "In cart" << std::endl;

	// *********THIRD ROW*********
	// Layout
	thirdRowLayout = new QHBoxLayout();
	overallLayout->addLayout(thirdRowLayout);

		// Buy Cart Button
		buyCartButton = new QPushButton("Buy Cart");
		connect(buyCartButton, SIGNAL(clicked()), this, SLOT(buyShoppingCart()));
		// connect(buyCartButton, SIGNAL(clicked()), this, SLOT(updateBalance()));
		thirdRowLayout->addWidget(buyCartButton);

		// Remove Product Button
		removeProductButton = new QPushButton("Remove Product");
		connect(removeProductButton, SIGNAL(clicked()), this, SLOT(removeProduct()));
		thirdRowLayout->addWidget(removeProductButton);

		// Quit Cart Button
		quitCartButton = new QPushButton("Quit");
		thirdRowLayout->addWidget(quitCartButton);

		// connect(quitCartButton, SIGNAL(clicked()), this, SLOT(showCart()));
		connect(quitCartButton, SIGNAL(clicked()), this, SLOT(close()));


		setLayout(overallLayout);

}

CartWindow::~CartWindow()
{

}

QPushButton* CartWindow::getBuyCartButton()
{
	return buyCartButton;
}

QPushButton* CartWindow::getRemoveButton()
{
	return removeProductButton;
}

QListWidget* CartWindow::getCartListWidget()
{
	return cartListWidget;
}

// void CartWindow::removeProduct(std::vector<Product*>* cart)
void CartWindow::removeProduct()
{
	if (cartListWidget->currentItem() == 0)
	{
		return;
	}
	if (cartListWidget->currentRow() == -1)
	{
		return;
	}
	if (ds_->getCart(userName_).size() == 0)
	{
		return;
	}
	std::string s = (cartListWidget->currentItem())->text().toStdString();
	std::string prodName = getProductName(s);
	std::cout << prodName << std::endl;

	ds_->removeProduct(userName_, prodName);

	// std::cout << "Here" << std::endl;

	QListWidgetItem* item = cartListWidget->currentItem();
	delete item;

	// std::cout << "Got to end" << std::endl;

}

void CartWindow::buyShoppingCart()
{
	if (ds_->getCart(userName_).size() == 0)
	{
		return;
	}
	std::vector<int> rows = ds_->buyCart(userName_);
	if (rows.size() == 0)
	{
		return;
	}
	std::cout << "Rows size = " << rows.size() << std::endl;
	std::cout << rows[0] << std::endl;
	std::cout << rows[1] << std::endl;
	for (unsigned int i = 0; i < rows.size(); i++)
	{
		int currRow = rows[i];
		QListWidgetItem* temp = cartListWidget->item(currRow);
		delete temp;
	}

	userNameLabel->clear();

	balance = ds_->getUser(userName_)->getBalance();
	QString qstr = QString::fromStdString(userName_);
	QString qstr10 = QString::fromStdString("'s Cart");
	QString qstr2 = QString::fromStdString(": $");
	double bal = ds_->getUser(userName_)->getBalance();
	std::stringstream ss; std::string s;
	ss << balance;
	ss >> s;
	QString qstr3 = QString::fromStdString(s);
	QString qstr4 = QString::fromStdString(" left");
	QString qstr5 = qstr + qstr10 + qstr2 + qstr3 + qstr4;
	userNameLabel = new QLabel(qstr5);
	userNameLabel->setAlignment(Qt::AlignRight);
	firstRowLayout->addWidget(userNameLabel);

	cartListWidget->clear();
	std::cout << "Cart real size = " << ds_->getCart(userName_).size() << std::endl;
	// displayCart();
	for (unsigned int i = 0; i < ds_->getCart(userName_).size(); i++)
	{
		std::string prod = (ds_->getCart(userName_))[i]->displayString();
		QString qstr = QString::fromStdString(prod);
		cartListWidget->addItem(qstr);
	} 
}

std::string CartWindow::getProductName(std::string productString)
{
	std::stringstream ss;
	ss << productString;
	std::string name;
	std::getline(ss, name);

	return name;
}

void CartWindow::displayCart()
{
	cartListWidget->clear();
	for (unsigned int i = 0; i < ds_->getCart(userName_).size(); i++)
	{
		std::cout << "In cart" << std::endl;
		std::string prod = (ds_->getCart(userName_))[i]->displayString();
		QString qstr = QString::fromStdString(prod);
		cartListWidget->addItem(qstr);
	} 
}

void CartWindow::showCart()
{
	displayCart();
}


