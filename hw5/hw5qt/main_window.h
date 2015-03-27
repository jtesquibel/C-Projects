#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
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

#include "cart_window.h"
#include "../datastore.h"
#include "../db_parser.h"


class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	MainWindow(std::string);
	~MainWindow();

public slots:
	void openCartWindow();
	// void andClicked();
	// void orClicked();
	void addSearchedProduct();
	void showAdded();
	void displayReviews();
	std::string findProductName(std::string productString);
	void addReview();
	// Product* findProduct(std::string productString);
	void addCart();
	void changeUser();
	void saveCart();
	

private:

	CartWindow* myCartWindow;

	MyDataStore ds_;

	User* currentUser;

	// // UI

	// Overall layout
	QHBoxLayout* overallLayout;

	// Other Layouts
	QVBoxLayout* firstColumnLayout;
	QVBoxLayout* secondColumnLayout;

	QHBoxLayout* searchLayout;
	QHBoxLayout* andOrLayout;
	QHBoxLayout* resultLayout;
	QHBoxLayout* userLayout;
	QHBoxLayout* addReviewLayout;


	// *********FIRST COLUMN*********

	// Search Function
	QLabel* searchProductLabel;
	QLineEdit* searchProductInput;

	// AND/OR Radio Buttons
	QRadioButton* andSearchButton;
	QRadioButton* orSearchButton;

	// Search Button
	QPushButton* searchButton;

	// Result Buttons
	QLabel* resultsLabel;
	QPushButton* alphaSortButton;
	QPushButton* ratingSortButton;

	// Result List
	QListWidget* resultsListWidget;

	// User Label
	QLabel* usersLabel;

	// User Drop Down List
	QComboBox* usersComboBox;

	// Review Label
	QLabel* reviewsLabel;

	// Review List
	QListWidget* reviewsListWidget;

	// Add Review
	QLabel* addReviewLabel;
	QLabel* addRatingLabel;
	QLabel* addDateLabel;
	QLineEdit* addRatingInput;
	QLineEdit* addDateInput;

	// New Review Text
	QLabel* addReviewInputLabel;
	QTextEdit* addReviewInput;

	// Submit Review
	QPushButton* submitReviewButton;

	
	// *********SECOND COLUMN*********

	// Add to cart button
	QPushButton* addToCartButton;

	// View cart button
	QPushButton* viewCartButton;

	// Save cart button
	QVBoxLayout* saveCartLayout;
	QLabel* saveFileLabel;
	QLineEdit* saveCartInput;
	QPushButton* saveCartButton;

	// Quit cart button
	QPushButton* quitButton;

	////////////////////////////////////////

	std::vector<Product*> hits_;

	
	// List of Search Results
	// std::vector<Product*> hits_;

	// List of Users

	// List of Reviews
};

#endif
