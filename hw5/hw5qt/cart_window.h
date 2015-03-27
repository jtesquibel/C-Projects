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
#include "../product.h"

class CartWindow : public QWidget
{
	Q_OBJECT
public:
	CartWindow();
	CartWindow(std::vector<Product*> *cart, std::string userName);
	~CartWindow();

	QPushButton* getBuyCartButton();
	QListWidget* getCartListWidget();
	// QPushButton* 

public slots:
	void removeProduct();
	std::string getProductName(std::string productString);
	// void quitCartWindow();
	// void fillCart();

private:

	// // UI

	std::vector<Product*>* cart_;

	// Overall layout
	QVBoxLayout* overallLayout;

	// Other Layouts
	QHBoxLayout* firstRowLayout;
	QHBoxLayout* thirdRowLayout;

	// *********FIRST ROW*********
	QLabel* userNameLabel;
	QLabel* cartLabel;

	// *********SECOND ROW*********
	QListWidget* cartListWidget;

	// *********THIRD ROW*********
	QPushButton* buyCartButton;
	QPushButton* removeProductButton;
	QPushButton* quitCartButton; 

};