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
#include "../datastore.h"

class CartWindow : public QWidget
{
	Q_OBJECT
public:
	CartWindow();
	// CartWindow(std::vector<Product*>& cart, std::string userName);
	CartWindow(MyDataStore &ds, std::string userName);
	~CartWindow();

	QPushButton* getBuyCartButton();
	QPushButton* getRemoveButton();
	QListWidget* getCartListWidget();

	void displayCart();
	// QPushButton* 

public slots:
	// void removeProduct(std::vector<Product*>* cart);
	void removeProduct();
	void buyShoppingCart();
	std::string getProductName(std::string productString);
	void showCart();
	// void updateBalance();
	// void quitCartWindow();
	// void fillCart();

private:

	// // UI

	MyDataStore* ds_;
	std::string userName_;

	double balance;

	std::vector<Product*> cart_;

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