#include "main_window.h"
// #include "cart_window.cpp"

MainWindow::MainWindow() 
{
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

	// FIFTH ROW
	// Layout
	userLayout = new QHBoxLayout();
	firstColumnLayout->addLayout(userLayout);

		// Users Label
		usersLabel = new QLabel("Users: ");
		userLayout->addWidget(usersLabel);

		// Users Combo Box
		usersComboBox = new QComboBox();
		userLayout->addWidget(usersComboBox);

	// SIXTH ROW
	reviewsLabel = new QLabel("Reviews: ");
	firstColumnLayout->addWidget(reviewsLabel);

	// SEVENTH ROW
	reviewsListWidget = new QListWidget();
	firstColumnLayout->addWidget(reviewsListWidget);

	// EIGTH ROW
	addReviewLabel = new QLabel("Add Review: ");
	firstColumnLayout->addWidget(addReviewLabel);

	//NINTH ROW
	// Layout
	addReviewLayout = new QHBoxLayout();
	firstColumnLayout->addLayout(addReviewLayout);

		// Add Rating Label
		addRatingLabel = new QLabel("Rating: ");
		addReviewLayout->addWidget(addRatingLabel);

		// Add Rating Input
		addRatingInput = new QLineEdit();
		addReviewLayout->addWidget(addRatingInput);

		// Add Date Label
		addDateLabel = new QLabel("Date: ");
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
	firstColumnLayout->addWidget(submitReviewButton);

	// *********SECOND COLUMN*********
	// Layout
	secondColumnLayout = new QVBoxLayout();
	overallLayout->addLayout(secondColumnLayout);

	// FIRST ROW
	addToCartButton = new QPushButton("Add To Cart");
	secondColumnLayout->addWidget(addToCartButton);

	// SECOND ROW
	viewCartButton = new QPushButton("View Cart");
	secondColumnLayout->addWidget(viewCartButton);

	// THIRD ROW
	saveCartButton = new QPushButton("Save Cart");
	secondColumnLayout->addWidget(saveCartButton);

	// FOURTH ROW
	quitButton = new QPushButton("Quit");
	secondColumnLayout->addWidget(quitButton);

	// Set Overall Layout
	setLayout(overallLayout);

	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(openCartWindow()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

}








	/*
	// *********POKEMON OLD STUFF**********

	// // Selected pokemon display
	// Layout
	pokemonDisplayLayout = new QVBoxLayout();
	overallLayout->addLayout(pokemonDisplayLayout);

	// Pokemon image
	//TODO
	pokemonImageContainer = new QLabel();
	pokemonDisplayLayout->addWidget(pokemonImageContainer);
	// overallLayout->addLayout(pokemonImageContainer);


	// Pokemon name
	//TODO
	pokemonNameDisplay = new QLabel();
	pokemonDisplayLayout->addWidget(pokemonNameDisplay);

	// Make it so image and name are at the top
	pokemonDisplayLayout->addStretch();




	// // List of all pokemon
	//TODO
	searchedProductWidget = new QListWidget();
	connect(pokemonListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(displayPokemon(int)));
	overallLayout->addWidget(pokemonListWidget);



	// // Form to add pokemon
	// Layout
	formLayout = new QVBoxLayout();
	overallLayout->addLayout(formLayout);


	// Pokemon name label
	pokemonNameLabel = new QLabel("Pokemon's Name:");
	formLayout->addWidget(pokemonNameLabel);

	// Pokemon name input
	//TODO
	pokemonNameInput = new QLineEdit();
	formLayout->addWidget(pokemonNameInput);

	// Image filename label
	imageFilenameLabel = new QLabel("Image Filename:");
	formLayout->addWidget(imageFilenameLabel);

	// Image filename input
	//TODO
	imageFilenameInput = new QLineEdit();
	formLayout->addWidget(imageFilenameInput);

	// Add button
	//TODO
	addButton = new QPushButton("Add Pokemon");
	connect(addButton, SIGNAL(clicked()), this, SLOT(addPokemon()));
	formLayout->addWidget(addButton);



	// Set overall layout
	setLayout(overallLayout);
} */

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
	myCartWindow = new CartWindow();
	myCartWindow->show();
}

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



void MainWindow::displayPokemon(int pokemonIndex)
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
}

*/
