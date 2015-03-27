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

#include <string>
#include <vector>

#include "cart_window.h"

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();

public slots:
	void openCartWindow();
	// void quitWindow();

// private slots:
	// void on_viewCartButton_clicked();

private:

	CartWindow* myCartWindow;

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
	QPushButton* saveCartButton;

	// Quit cart button
	QPushButton* quitButton;



	/*
	// *********POKEMON OLD STUFF**********

	// Displayed pokemon
	QVBoxLayout* pokemonDisplayLayout;
	QLabel* pokemonImageContainer;
	QLabel* pokemonNameDisplay;

	// List of products
	// QListWidget* searchedProductWidget;

	// Form for new pokemon
	QVBoxLayout* formLayout;
	QLabel* pokemonNameLabel;
	QLineEdit* pokemonNameInput;
	QLabel* imageFilenameLabel;
	QLineEdit* imageFilenameInput;
	QPushButton* addButton;



	// // Data
	// note: the index of each name in `pokemonNames`
	// corresponds with the index of that pokemon's
	// image in `pokemonImages`

	// List of Search Results

	// List of Users

	// List of Reviews

	// *********POKEMON OLD STUFF**********

	// List of pokemon names
	std::vector<std::string> pokemonNames;
	// List of pokemon images
	std::vector<QImage*> pokemonImages;

	*/
};

#endif
