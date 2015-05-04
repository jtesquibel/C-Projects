#include "cart_window.h"

CartWindow::CartWindow() 
{
	// Title
	setWindowTitle("Cart");

	// Overall layout
	overallLayout = new QVBoxLayout();

	// *********FIRST ROW*********
	cartLabel = new QLabel("Cart");
	overallLayout->addWidget(cartLabel);

	// *********SECOND ROW*********
	cartListWidget = new QListWidget();
	overallLayout->addWidget(cartListWidget);

	// *********THIRD ROW*********
	// Layout
	thirdRowLayout = new QHBoxLayout();
	overallLayout->addLayout(thirdRowLayout);

		// Buy Product Button
		buyProductButton = new QPushButton("Buy Product");
		thirdRowLayout->addWidget(buyProductButton);

		// Remove Product Button
		removeProductButton = new QPushButton("Remove Product");
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

