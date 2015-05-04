#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include "../util.h"
#include "../heap.h"
#include "main_window.h"

MainWindow::MainWindow()
{

}

MainWindow::MainWindow(MyDataStore &ds, std::string userName)
{	
	std::cout << "In constructor" << std::endl;
	ds_ = &ds;
	userName_ = userName;
	currentUser = ds_->getUser(userName_);

	calcSimilar();

	// Instantiate the parser
  	// DBParser parser;

 	// Instantiate the individual product parsers we want
  	// parser.addProductParser(new ProductBookParser);
  	// parser.addProductParser(new ProductClothingParser);
  	// parser.addProductParser(new ProductMovieParser);

  	// Now parse the database to populate the DataStore 
  	// if( parser.parse(input, ds_) )
  	// {
   //  	std::cerr << "Error parsing!" << std::endl;
  	// }

	// Title
	QString qstr = QString::fromStdString(userName_);
	QString qstr2 = QString::fromStdString("'s cart");
	QString qstr3 = qstr + qstr2;
	setWindowTitle(qstr3);

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
		alphaSortButton = new QRadioButton("Alphabetically");
		connect(alphaSortButton, SIGNAL(clicked()), this, SLOT(sortAlpha()));
		resultLayout->addWidget(alphaSortButton);

		// Rating Sort Button
		ratingSortButton = new QRadioButton("By Average Rating");
		connect(ratingSortButton, SIGNAL(clicked()), this, SLOT(sortAverageRating()));
		resultLayout->addWidget(ratingSortButton);

	// FOURTH ROW
	resultsListWidget = new QListWidget();
	firstColumnLayout->addWidget(resultsListWidget);

	connect(searchButton, SIGNAL(clicked()), this, SLOT(addSearchedProduct()));

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
	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(openCartWindow()));
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
	quitButton = new QPushButton("Logout");
	secondColumnLayout->addWidget(quitButton);

	// Set Overall Layout
	setLayout(overallLayout);

	// connect(viewCartButton, SIGNAL(clicked()), this, SLOT(openCartWindow()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(saveCartButton, SIGNAL(clicked()), this, SLOT(saveCart()));

}


MainWindow::~MainWindow()
{
	

	//TODO the delete UI objects
	delete myCartWindow;
	
}

void MainWindow::openCartWindow() 
{
	std::string userName = currentUser->getName();
	myCartWindow = new CartWindow(*ds_, userName);
	myCartWindow->show();
}

void MainWindow::calcSimilar()
{
	std::cout << "hello" << std::endl;
	// std::map<std::string, double> similarities_;
	std::vector<User*> users = ds_->getUsers();
	// std::vector<Review*> currUserReviews;
	// for (int i = 0; i < ds_->getReviews().size(); i++)
	// {
	// 	if (ds_->getReviews()[i]->userName == userName_)
	// 	{
	// 		currUserReviews.push_back(ds_->getReviews()[i]);
	// 	}
	// }

	// if (currUserReviews.size() == 0)
	// {
	// 	QString qstr = QString::fromStdString("This username has no reviews!");
	// 	QMessageBox::about(this, "Error!", qstr);
	// 	return;
	// }

	for (int h = 0; h < users.size(); h++)
	{
		// User* currUser = ds_->getUser()
		std::cout << "hello2" << std::endl;
		std::string currUserName = users[h]->getName();

		std::vector<Review*> currUserReviews;
		for (int i = 0; i < ds_->getReviews().size(); i++)
		{
			if (ds_->getReviews()[i]->userName == currUserName)
			{
				currUserReviews.push_back(ds_->getReviews()[i]);
			}
		}

		if (currUserReviews.size() == 0)
		{
			QString qstr = QString::fromStdString("This user has no reviews!");
			QMessageBox::about(this, "Error!", qstr);
			return;
		}

		for (unsigned int i = 0; i < users.size(); i++)
		{
			std::vector<Review*> sharedReviews;
			std::vector<double> nums;
			if (users[i]->getName() == currUserName)
			{
				continue;
			}

			// std::vector<Review*> otherUserReviews = ds_->getUserReviews(users[i]->getName());
			std::vector<Review*> otherUserReviews;
			for (int j = 0; j < ds_->getReviews().size(); j++)
			{
				if (ds_->getReviews()[j]->userName == users[i]->getName())
				{
					otherUserReviews.push_back(ds_->getReviews()[j]);
				}
			}

			for (int j = 0; j < currUserReviews.size(); j++)
			{
				for (int k = 0; k < otherUserReviews.size(); k++)
				{
					if (currUserReviews[j]->prodName == otherUserReviews[k]->prodName)
					{
						sharedReviews.push_back(currUserReviews[j]);
						double rating1 = currUserReviews[j]->rating;
						double rating2 = otherUserReviews[k]->rating;
						double sim = (abs(rating1-rating2))/4;
						nums.push_back(sim);
					}
				}
			}

			double totalSim = 0;
			for (int l = 0; l < nums.size(); l++)
			{
				totalSim += nums[l];
			}

			if (totalSim == 0)
			{
				users[h]->setSimilarities(users[i]->getName(), 1.0);
				// users[i]->getSimilarities().insert(pair <std::string, double >(users[i]->getName(), 1.0));
				similarities2_.insert(pair <std::pair<std::string, std::string>, double >(std::make_pair(currUserName, users[i]->getName()), 1.0));
				// return;
			}
			else 
			{
				double avgSim = totalSim/nums.size();
				// map2_.insert(pair <std::string, std::vector<Review*> >(p->getName(), reviews));
				// avgRatings_.push_back(std::make_pair(getProduct(prodName), avgRating));

				users[h]->setSimilarities(users[i]->getName(), avgSim);
				// users[i]->getSimilarities().insert(pair <std::string, double >(users[i]->getName(), avgSim));
				similarities2_.insert(pair <std::pair<std::string, std::string>, double >(std::make_pair(currUserName, users[i]->getName()), avgSim));
				// similarities_.insert(pair <std::string, double >(ds_->getUsers()[i]->getName(), avgSim));
			}

			// std::cout << "user sim size = " << users[i]->getSimilarities().size() << std::endl;
			std::cout << "sim2 size = " << similarities2_.size() << std::endl;
		}

	}

	for (int i = 0; i < users.size(); i++)
	{
		std::cout << "user sim size = " << users[i]->getSimilarities().size() << std::endl;
	}

	// std::cout << "sim size = " << similarities_.size() << std::endl;

	// std::map<std::pair<std::string, std::string>, double>::iterator it;
	// for (it = similarities_.begin(); it != similarities_.end(); ++it)
	// {
	// 	std::cout << it->second << std::endl;
	// }




	// vector<User*> sameReviews;
	// vector<Review*> prodReviews = ds_->getProdReviews();


	// for (int i = 0; i < )

	less<double> comp;
	
	Heap<double, less<double> > heap(2, comp);

	for (int h = 0; h < users.size(); h++)
	{
		// std::cout << "hello2" << std::endl;
		std::string currUserName = users[h]->getName();
		double startUserDist = 0;
		User* userPred = NULL;
		heap.push(startUserDist);

		for (int i = 0; i < users.size(); i++)
		{
			if (users[i]->getName() == currUserName)
			{
				continue;
			}

			double nextUserDist = 1000;
			heap.push(nextUserDist);
		}

		while (!heap.empty())
		{
			double v = heap.top();
			heap.pop();
		}

	}

	vector<Product*> products = ds_->getProducts();
	vector<Review*> reviews = ds_->getReviews();
	std::vector<Review*> currUserReviews;
	for (int i = 0; i < ds_->getReviews().size(); i++)
	{
		if (ds_->getReviews()[i]->userName == userName_)
		{
			currUserReviews.push_back(ds_->getReviews()[i]);
		}
	}


	vector<Product*> nonReviewedProducts;

	for (int i = 0; i < products.size(); i++)
	{
		bool same = false;
		for (int j = 0; j < currUserReviews.size(); j++) 
		{
			if (products[i]->getName() == currUserReviews[j]->prodName)
			{
				same = true;
			}
		}

		if (same == false)
		{
			nonReviewedProducts.push_back(products[i]);
		}
	}

	std::cout << "non reviewed prods = " << nonReviewedProducts.size() << std::endl;

	// vector<int> interestingness;
	std::map<Product*, double> interestingness;

	for (int i = 0; i < nonReviewedProducts.size(); i++)
	{
		vector<Review*> sameReviews;
		vector<Review*> reviews2 = ds_->getProdReviews(nonReviewedProducts[i]->getName());

		for (int j = 0; j < reviews2.size(); j++)
		{
			sameReviews.push_back(reviews2[j]);			
		}

		std::cout << "same reviews = " << sameReviews.size() << std::endl;

		double r = 0;
		double w = 0;

		for (int j = 0; j < sameReviews.size(); j++)
		{
			double rating = sameReviews[j]->rating;
			std::pair<std::string, std::string> p;
			double sim = similarities2_.find(p)->second;
			double temp = (1-sim)*rating;
			r += temp;
			double temp2 = (1-sim);
			w += temp2;
		}
		
		if (w == 0.0)
		{
			double temp3 = 0.0;
			interestingness.insert(pair <Product*, double >(std::make_pair(nonReviewedProducts[i], temp3)));
		}
		else
		{
			double temp3 = r/w;
			interestingness.insert(pair <Product*, double >(std::make_pair(nonReviewedProducts[i], temp3)));
		}
		// double sim = userName_.getSimilarities()	
	}

	std::cout << "int size = " << interestingness.size() << std::endl;

	std::map<Product*, double>::iterator it = interestingness.begin();
	double highDouble = it->second;
	Product* highProd = it->first;

	std::cout << "init high double = " << highDouble << std::endl;

	for (it = interestingness.begin(); it != interestingness.end(); ++it)
	{
		if (it->second > highDouble)
		{
			highDouble = it->second;
			highProd = it->first;
		}
	}

	std::cout << "after high double = " << highDouble << std::endl;



	std::string str1 = "You should check out ";
	std::string quote = "\"";
	std::string name = highProd->getName();
	std::string str2 = "! It is highly recommended";
	std::string str3 = str1 + quote + name + quote + str2;
	QString qstr = QString::fromStdString(str3);
	QMessageBox::about(this, "Product Recommendation!", qstr);



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
		if (term.size() < 3)
		{
			QString qstr = QString::fromStdString("One or more of your searches was too short");
			QMessageBox::about(this, "Error!", qstr);
			resultsListWidget->clear();
			return;
		}
		term = convToLower(term);
		std::cout << term << std::endl;
		terms.push_back(term);
	}
	
	std::vector<Product*> hits_;

	if (andSearchButton->isChecked())
	{
		hits_ = ds_->search(terms, 0);
		searchProductInput->clear(); 
	}
	else if (orSearchButton->isChecked())
	{
		hits_ = ds_->search(terms, 1);
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
	if (resultsListWidget->currentItem() == 0)
	{
		return;
	}
	if (resultsListWidget->currentRow() == -1)
	{
		return;
	}
	std::string s = (resultsListWidget->currentItem())->text().toStdString();
	std::string name = findProductName(s);

	std::string quote = "\"";
	std::string m = "Successfully added ";
	std::string m2 =  " to cart";
	std::string m3 = m + quote + name + quote + m2;

	QString qstr = QString::fromStdString(m3);
	QMessageBox::about(this, "Success!", qstr);
}

void MainWindow::sortAlpha()
{
	if (andSearchButton->isChecked() || orSearchButton->isChecked())
	{
		return;
	}
	if (resultsListWidget->currentItem() == 0)
	{
		return;
	}
	// if (resultsListWidget->currentRow() == -1)
	// {
	// 	return;
	// }
	AlphaStrComp comp1;
	std::vector<Product*> results;
	for (unsigned int i = 0; i < resultsListWidget->count(); i++)
	{
		std::string text = resultsListWidget->item(i)->text().toStdString();
		results.push_back(findProduct(text));
	}

	mergeSort(results, comp1);
	std::cout << "Here" << std::endl;

	resultsListWidget->clear();
	
	for (unsigned int i = 0; i < results.size(); i++)
	{
		QString qstr = QString::fromStdString(results[i]->displayString());
		resultsListWidget->addItem(qstr);
	}
}

void MainWindow::sortAverageRating()
{
	if (andSearchButton->isChecked() || orSearchButton->isChecked())
	{
		return;
	}
	if (resultsListWidget->currentItem() == 0)
	{
		return;
	}
	// if (resultsListWidget->currentRow() == -1)
	// {
	// 	return;
	// }
	RatingComp comp;
	std::vector<std::pair<double, Product*> > prodNames;
	for (unsigned int i = 0; i < resultsListWidget->count(); i++)
	{
		std::string text = resultsListWidget->item(i)->text().toStdString();
		// Product p = findProduct(text);
		std::string name = findProductName(text);
		double d = ds_->calculateAvgRating(name);
		prodNames.push_back(std::make_pair(d, findProduct(text)));
	}

	// resultsListWidget->clear();
	// std::vector<std::pair<Product*, double> > prodNames = ds_.getAverageprodNames();
	for (unsigned int i = 0; i < prodNames.size(); i++)
	{
		cout << "Avg rating = " << prodNames[i].first << std::endl;
		// QString qstr = QString::fromStdString(prodNames[i].second->displayString());
		// resultsListWidget->addItem(qstr);
	}
	std::cout << std::endl;
	mergeSort(prodNames, comp);


	resultsListWidget->clear();

	// std::vector<Product*> sortedRatings = ratings.first;
	
	for (unsigned int i = 0; i < prodNames.size(); i++)
	{
		cout << "Avg rating = " << prodNames[i].first << std::endl;
		QString qstr = QString::fromStdString(prodNames[i].second->displayString());
		resultsListWidget->addItem(qstr);
	}
}

void MainWindow::displayReviews()
{
	reviewsListWidget->clear();

	DateComp comp;

	std::string s = (resultsListWidget->currentItem())->text().toStdString();
	std::string name = findProductName(s);
	
	std::vector<Review*> reviews = ds_->getProdReviews(name);

	std::cout << "After getUsers()" << std::endl;

	if (reviews.size() == 0)
	{
		return;
	}

	mergeSort(reviews, comp);

	std::cout << "After mergeSort" << std::endl;

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
	if (resultsListWidget->currentItem() == 0)
	{
		return;
	}
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

		Review* r = new Review(prodName, rating2, userName_, date, text);
		ds_->addReview(r);

		displayReviews();

		addRatingInput->clear();
		addDateInput->clear();
		addReviewInput->clear();

	}
}

void MainWindow::addCart()
{
	if (resultsListWidget->currentItem() == 0)
	{
		return;
	}
	if (resultsListWidget->currentRow() == -1)
	{
		return;
	}
	std::cout << "sdfdsf = " << resultsListWidget->currentItem() << std::endl;
	std::string str = (resultsListWidget->currentItem())->text().toStdString();
	// std::cout << "sdfdsf " << std::endl;
	std::string prodName = findProductName(str);
	// std::cout << "sdfdsf " << std::endl;
	Product* p = ds_->getProduct(prodName);
	// std::cout << "sdfdsf " << std::endl;

	ds_->addToCart(currentUser->getName(), p);
}

// void MainWindow::changeUser()
// {
// 	std::string user = (usersComboBox->currentText().toStdString());
// 	currentUser = ds_->getUser(user);
// }

void MainWindow::saveCart()
{
	if (saveCartInput->text().isEmpty() == 0)
	{
		std::string filename(saveCartInput->text().toStdString());
		std::ofstream ofile(filename.c_str());
		ds_->dump(ofile);
		ofile.close();
	}
}

Product* MainWindow::findProduct(std::string productString)
{
	std::stringstream ss;
	ss << productString;
	std::string name; std::string rightName;
	std::getline(ss, name);

	std::vector<Product*> products = ds_->getProducts();
	for (unsigned int i = 0; i < products.size(); i++)
	{
		if (products[i]->getName() == name)
		{
			rightName = name;
			return products[i];
		}
	}
}



