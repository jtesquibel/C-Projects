#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include "main_window.h"
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
/** Add other #includes here **/
#include "user.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include <QApplication>

// using namespace std;

int main(int argc, char* argv[])
{
	
	MyDataStore ds;

	// Instantiate the parser
  	DBParser parser;

 	// Instantiate the individual product parsers we want
  	parser.addProductParser(new ProductBookParser);
  	parser.addProductParser(new ProductClothingParser);
  	parser.addProductParser(new ProductMovieParser);

  	// Now parse the database to populate the DataStore
  	if( parser.parse(argv[1], ds) )
  	{
    	std::cerr << "Error parsing!" << std::endl;
    	return 1;
  	}
  	

	QApplication app(argc, argv);

	MainWindow mainWindow;

	mainWindow.show();

	return app.exec();
}