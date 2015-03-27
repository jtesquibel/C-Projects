#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>
#include "main_window.h"
#include "../product.h"
#include "../datastore.h"
#include "../db_parser.h"
#include "../product_parser.h"
#include "../util.h"
/** Add other #includes here **/
#include "../user.h"
#include "../book.h"
#include "../clothing.h"
#include "../movie.h"
#include <QApplication>

// using namespace std;

int main(int argc, char* argv[])
{
  
  std::string input = argv[1];

	QApplication app(argc, argv);

	MainWindow mainWindow(input);

	mainWindow.show();

  // std::cout << "Hello" << std::endl;

	return app.exec();
}