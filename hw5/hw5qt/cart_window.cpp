#include <vector>
#include <sstream>
#include "cart_window.h"

CartWindow::CartWindow()
{

}

CartWindow::CartWindow(std::vector<Product*> *cart, std::string userName)
{
	// Title
	setWindowTitle("Cart");

	cart_ = cart;

	// Overall layout
	overallLayout = new QVBoxLayout();

	// *********FIRST ROW*********
	// Layout
	firstRowLayout = new QHBoxLayout();
	overallLayout->addLayout(firstRowLayout);

		// User Name Label
		QString qstr = QString::fromStdString(userName);
		userNameLabel = new QLabel(qstr);
		firstRowLayout->addWidget(userNameLabel);
	
		// Cart Label;
		cartLabel = new QLabel("Cart");
		firstRowLayout->addWidget(cartLabel);

	// *********SECOND ROW*********
	cartListWidget = new QListWidget();
	
	std::cout << "Cart real size = " << cart_->size() << std::endl;
	for (unsigned int i = 0; i < cart_->size(); i++)
	{
		std::string prod = (*cart_)[i]->displayString();
		QString qstr = QString::fromStdString(prod);
		cartListWidget->addItem(qstr);
	} 
	overallLayout->addWidget(cartListWidget);

	// *********THIRD ROW*********
	// Layout
	thirdRowLayout = new QHBoxLayout();
	overallLayout->addLayout(thirdRowLayout);

		// Buy Cart Button
		buyCartButton = new QPushButton("Buy Product");
		thirdRowLayout->addWidget(buyCartButton);

		// Remove Product Button
		removeProductButton = new QPushButton("Remove Product");
		connect(removeProductButton, SIGNAL(clicked()), this, SLOT(removeProduct()));
		thirdRowLayout->addWidget(removeProductButton);

		// Quit Cart Button
		quitCartButton = new QPushButton("Quit");
		thirdRowLayout->addWidget(quitCartButton);

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

QListWidget* CartWindow::getCartListWidget()
{
	return cartListWidget;
}

void CartWindow::removeProduct()
{
	std::cout << "In remove product" << std::endl;
	std::string s = (cartListWidget->currentItem())->text().toStdString();
	std::string prodName = getProductName(s);
	std::cout << prodName << std::endl;

	std::cout << "Here" << std::endl;

	std::cout << cart_->size() << std::endl;

	for (unsigned int i = 0; i < cart_->size(); i++)
	{
		// std::cout << "Inside" << std::endl;
		// // std::string name2 = (*cart_[i])->getName();
		// // if (name2 == prodName)
		// {
		// 	cart_->erase(cart_->begin()+i);
		// 	std::cout << "Erased from vector" << std::endl;
		// 	break;
		// }
	}

	// QListWidgetItem* item = new QListWidgetItem(this, cartListWidget->currentItem());
	cartListWidget->removeItemWidget(cartListWidget->currentItem());
	std::cout << "Got to end" << std::endl;

}

std::string CartWindow::getProductName(std::string productString)
{
	std::stringstream ss;
	ss << productString;
	std::string name;
	std::getline(ss, name);

	return name;
}



/*
void CartWindow::fillCart()
{
	std::vector<Product*> cart = mainWindow.ds_.getCart();
	for (ungned int i = 0; i < cart.size(); i++)
	{
		std::cout << "In cart loop" << std::endl;
		std::string name = cart[i]->getName();
		QString qstr = QString::fromStdString(name);
		cartListWidget->addItem(qstr);
	}
} */

