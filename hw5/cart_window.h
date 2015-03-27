#ifndef CART_WINDOW_H
#define CART_WINDOW_H
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

class CartWindow : public QWidget
{
	Q_OBJECT
public:
	CartWindow();
	~CartWindow();

public slots:
	// void quitCartWindow();

private:

	// // UI

	// Overall layout
	QVBoxLayout* overallLayout;

	// Other Layouts
	QHBoxLayout* thirdRowLayout;

	// *********FIRST ROW*********
	QLabel* cartLabel;

	// *********SECOND ROW*********
	QListWidget* cartListWidget;

	// *********THIRD ROW*********
	QPushButton* buyProductButton;
	QPushButton* removeProductButton;
	QPushButton* quitCartButton;

};

#endif