#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include "../util.h"
#include "main_window.h"

MainWindow::MainWindow()
{

}

MainWindow::MainWindow(std::string input)
{	

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
	setWindowTitle("Amazon");

	// Overall layout
	overallLayout = new QHBoxLayout();

	// *********FIRST COLUMN*********
	// Layout
	firstColumnLayout = new QVBoxLayout();
	overallLayout->addLayout(firstColumnLayout);

	// FIRST ROW
	// Layout
	searchLayout = new QHBoxLayout();
	firstColumnLayout->addLayout(searchLayout);

		// Search Label
		searchProductLabel = new QLabel("Search: ");
		searchLayout->addWidget(searchProductLabel);

		// Search text
		searchProductInput = new QLineEdit();
		searchLayout->addWidget(searchProductInput);

	// SECOND ROW
	// Layout
	andOrLayout = new QHBoxLayout();
	firstColumnLayout->addLayout(andOrLayout);

		// AND Radio Button
		andSearchButton = new QRadioButton("AND");
		andOrLayout->addWidget(andSearchButton);

		// OR Radio Button
		orSearchButton = new QRadioButton("OR");
		andOrLayout->addWidget(orSearchButton);

		// Search Button
		searchButton = new QPushButton("Search");
		// connect(searchButton, SIGNAL(clicked()), this, SLOT(addSearchedProduct()));
		andOrLayout->addWidget(searchButton);

	// THIRD ROW
	// Layout
	resultLayout = new QHBoxLayout();
	firstColumnLayout->addLayout(resultLayout);

		// Results Label
		resultsLabel = new QLabel("Results: ");
		resultLayout->addWidget(resultsLabel);

		// Alpha Sort Button
		alphaSortButton = new QPushButton("Alpha");
		resultLayout->addWidget(alphaSortButton);

		// Rating Sort Button
		ratingSortButton = new QPushButton("Average Rating");
		resultLayout->addWidget(ratingSortButton);

	// FOURTH ROW
	resultsListWidget = new QListWidget();
	firstColumnLayout->addWidget(resultsListWidget);

	connect(searchButton, SIGNAL(clicked()), this, SLOT(addSearchedProduct()));

	// FIFTH ROW
	// Layout
	userLayout = new QHBoxLayout();
	firstColumnLayout->addLayout(userLayout);

		// Users Label
		usersLabel = new QLabel("Users: ");
		userLayout->addWidget(usersLabel);

		// Users Combo Box
		usersComboBox = new QComboBox();
	
		std::vector<User*> names = ds_.getUsers();
		for (unsigned int i = 0; i < names.size(); i++)
		{
			std::cout << "Loop" << std::endl;
			std::string name = names[i]->getName();
			QString qstr = QString::fromStdString(name);
			usersComboBox->addItem(qstr);
		}
		currentUser = ds_.getUser(usersComboBox->currentText().toStdString());
		connect(usersComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeUser()));
		userLayout->addWidget(usersComboBox);

	// SIXTH ROW
	reviewsLabel = new QLabel("Reviews: ");
	firstColumnLayout->addWidget(reviewsLabel);

	// SEVENTH ROW
	reviewsListWidget = new QListWidget();
	connect(resultsListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(displayReviews()));
	firstColumnLayout->addWidget(reviewsListWidget);

	// EIGTH ROW
	addReviewLabel = new QLabel("Add Review: ");
	firstColumnLayout->addWidget(addReviewLabel);

	//NINTH ROW
	// Layout
	addReviewLayout = new QHBoxLayout();
	firstColumnLayout->addLayout(addReviewLayout);

		// Add Rating Label
		addRatingLabel = new QLabel("Rating (1-5): ");
		addReviewLayout->addWidget(addRatingLabel);

		// Add Rating Input
		addRatingInput = new QLineEdit();
		addReviewLayout->addWidget(addRatingInput);

		// Add Date Label
		addDateLabel = new QLabel("Date (YYYY-MM-DD): ");
		addReviewLayout->addWidget(addDateLabel);

		// Add Date Input
		addDateInput = new QLineEdit();
		addReviewLayout->addWidget(addDateInput);

	// TENTH ROW
	addReviewInputLabel = new QLabel("Review Text: ");
	firstColumnLayout->addWidget(addReviewInputLabel);

	// ELEVENTH ROW
	addReviewInput = new QTextEdit();
	firstColumnLayout->addWidget(addReviewInput);

	// TWELTH ROW
	submitReviewButton = new QPushButton("Submit Review");
	connect(submitReviewButton, SIGNAL(clicked()), this, SLOT(addReview()));
	firstColumnLayout->addWidget(submitReviewButton);

	// *********SECOND COLUMN*********
	// Layout
	secondColumnLayout = new QVBoxLayout();
	overallLayout->addLayout(secondColumnLayout);

	// FIRST ROW
	addToCartButton = new QPushButton("Add To Cart");
	connect(addToCartButton, SIGNAL(clicked()), this, SLOT(addCart()));
	connect(addToCartButton, SIGNAL(clicked()), this, SLOT(showAdded()));
	secondColumnLayout->addWidget(addToCartButton);

	// SECOND ROW
	viewCartButton = new QPushButton("View Cart");
	secondColumnLayout->addWidget(viewCartButton);

	// THIRD ROW
	// Layout
	saveCartLayout = new QVBoxLayout();
	secondColumnLayout->addLayout(saveCartLayout);

		// Save File Label
		saveFileLabel = new QLabel("Filename");
		saveCartLayout->addWidget(saveFileLabel);

		// Save File Input
		saveCartInput = new QLineEdit();
		saveCartLayout->addWidget(saveCartInput);

		// Save Cart Button
		saveCartButton = new QPushButton("Save Cart");
		saveCartLayout->addWidget(saveCartButton);

		saveCartLayout->addStretch();

	// FOURTH ROW
	quitButton = new QPushButton("Quit");
	secondColumnLayout->addWidget(quitButton);

	// Set Overall Layout
	setLayout(overallLayout);

	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(openCartWindow()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(saveCartButton, SIGNAL(clicked()), this, SLOT(saveCart()));

}


MainWindow::~MainWindow()
{
	/*
	// Delete the images
	for(std::vector<QImage*>::iterator i = pokemonImages.begin();
		i != pokemonImages.end();
		++i)
	{
		delete *i;
	}

	//TODO the delete UI objects
	delete overallLayout;
	delete pokemonDisplayLayout;
	delete pokemonNameDisplay;
	delete pokemonListWidget;
	delete formLayout;
	delete pokemonNameLabel;
	delete pokemonNameInput;
	delete imageFilenameLabel;
	delete imageFilenameInput;
	delete addButton;
	delete pokemonImageContainer;
	*/
}

void MainWindow::openCartWindow() 
{
	// std::cout << "current user = " << currentUser->getName() << std::endl;
	std::vector<Product*> cart = ds_.getCart(currentUser->getName());
	std::cout << "cart size" << cart.size() << std::endl;
	std::string userName = currentUser->getName();
	myCartWindow = new CartWindow(&cart, userName);
	myCartWindow->show();
}

void MainWindow::addSearchedProduct()
{
	if (searchProductInput->text().isEmpty())
	{
		return;
	}

	std::string term;
	std::vector<std::string> terms;

	std::string line = searchProductInput->text().toStdString();
	std::cout << line << std::endl;
	std::stringstream ss(line);
	std::cout << ss << std::endl;
	while(ss >> term)
	{
		term = convToLower(term);
		std::cout << term << std::endl;
		terms.push_back(term);
	}
	
	std::vector<Product*> hits_;

	if (andSearchButton->isChecked())
	{
		hits_ = ds_.search(terms, 0);
		searchProductInput->clear(); 
	}
	else if (orSearchButton->isChecked())
	{
		hits_ = ds_.search(terms, 1);
		searchProductInput->clear(); 
	}
	else if (!andSearchButton->isChecked() && !orSearchButton->isChecked())
	{
		searchProductInput->clear(); 
	}

	resultsListWidget->clear();
	
	for (unsigned int i = 0; i < hits_.size(); i++)
	{
		QString qstr = QString::fromStdString(hits_[i]->displayString());
		resultsListWidget->addItem(qstr);
	}
} 

void MainWindow::showAdded() 
{
	std::string s = (resultsListWidget->currentItem())->text().toStdString();
	std::string name = findProductName(s);

	std::string quote = "\"";
	std::string m = "Successfully added ";
	std::string m2 =  " to cart";
	std::string m3 = m + quote + name + quote + m2;

	QString qstr = QString::fromStdString(m3);
	QMessageBox::about(this, "Success!", qstr);
}

void MainWindow::displayReviews()
{
	reviewsListWidget->clear();

	std::string s = (resultsListWidget->currentItem())->text().toStdString();
	std::string name = findProductName(s);
	
	std::vector<Review*> reviews = ds_.getReviews(name);

	for (unsigned int i = 0; i < reviews.size(); i++)
	{
		QString qstr2 = QString::fromStdString(reviews[i]->displayReview());
		reviewsListWidget->addItem(qstr2);
	}
}

std::string MainWindow::findProductName(std::string productString)
{
	std::stringstream ss;
	ss << productString;
	std::string name; std::string rightName;
	std::getline(ss, name);

	return name;
}

void MainWindow::addReview()
{
	if (addRatingInput->text().isEmpty() || addDateInput->text().isEmpty() || addReviewInput->toPlainText().isEmpty())
	{
		return;
	}
	else
	{
		std::string s = (resultsListWidget->currentItem())->text().toStdString();
		std::string prodName = findProductName(s);

		std::string rating(addRatingInput->text().toStdString());
		std::string date(addDateInput->text().toStdString());
		std::string text(addReviewInput->toPlainText().toStdString());

		int rating2 = atoi(rating.c_str());
		if (rating2 < 1 || rating2 > 5)
		{
			return;
		}

		if (date[4] != '-' || date[7] != '-')
		{
			return;
		}

		Review* r = new Review(prodName, rating2, date, text);
		ds_.addReview(r);

		QString qstr = QString::fromStdString(r->displayReview());
		reviewsListWidget->addItem(qstr);

		addRatingInput->clear();
		addDateInput->clear();
		addReviewInput->clear();

	}
}

void MainWindow::addCart()
{
	std::cout << "sdfdsf " << std::endl;
	std::string str = (resultsListWidget->currentItem())->text().toStdString();
	std::cout << "sdfdsf " << std::endl;
	std::string prodName = findProductName(str);
	std::cout << "sdfdsf " << std::endl;
	Product* p = ds_.getProduct(prodName);
	std::cout << "sdfdsf " << std::endl;

	ds_.addToCart(currentUser->getName(), p);
}

void MainWindow::changeUser()
{
	std::string user = (usersComboBox->currentText().toStdString());
	currentUser = ds_.getUser(user);

}

void MainWindow::saveCart()
{
	if (saveCartInput->text().isEmpty() == 0)
	{
		std::string filename(saveCartInput->text().toStdString());
		std::ofstream ofile(filename.c_str());
		ds_.dump(ofile);
		ofile.close();
	}
}


// void MainWindow::andClicked()
// {
	// if ()
// }

// void MainWindow::orClicked()
// {

// }

/*
void MainWindow::displayProducts(int productIndex)
{
	// Get the pokemon specified by the index,
	// which is passed into the function when
	// the user clicks on pokemonListWidget

	// Image
	//TODO
	// pokemonImageContainer = new QLabel();
	pokemonImageContainer->setPixmap(QPixmap::fromImage(*pokemonImages[pokemonIndex]));
	// overallLayout->addWidget(pokemonImageContainer);

	// Pokemon name
	//TODO
	QString pokemonText;
	pokemonText = QString::fromStdString(pokemonNames[pokemonIndex]);
	pokemonNameDisplay->setText(pokemonText);
} */

/*
void displayProducts(vector<Product*>& hits)
{
  int resultNo = 1;
  for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it){
    cout << "Hit " << setw(3) << resultNo << endl;
    cout << (*it)->displayString() << endl;
    cout << endl;
    resultNo++;
  }
} */

/*

void MainWindow::addPokemon()
{
	// Do nothing if user left at least one input blank
	//TODO
	if(pokemonNameInput->text().isEmpty() || imageFilenameInput->text().isEmpty())
	{
		return;
	}

	// // Get form values
	// Pokemon name
	//TODO
	pokemonNames.push_back(pokemonNameInput->text().toStdString());
	// pokemonImages.push_back(pokemonFilenameInput->text().toStdString());
	
	// Image
	// QString filename = imageFilenameInput->text();
	QImage* newImage = new QImage();
	//TODO what should go right here?
	newImage->load(imageFilenameInput->text());
	pokemonImages.push_back(newImage);



	// Create a new list item with the pokemon's name
	//TODO
	pokemonListWidget->addItem(pokemonNameInput->text());

	// Clear the form inputs
	//TODO
	pokemonNameInput->setText("");
	imageFilenameInput->setText("");
}

*/

/*
Product* MainWindow::findProduct(std::string productString)
{
	std::stringstream ss;
	ss << productString;
	std::string name; std::string rightName;
	std::getline(ss, name);

	std::vector<Product*> products = ds_.getProducts();
	for (unsigned int i = 0; i < products.size(); i++)
	{
		if (products[i]->getName() == name)
		{
			rightName = name;
			return products[i];
		}
	}
} */

/*
void MainWindow::fillCart()
{

} */



