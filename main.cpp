// # Main entry point

#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QHeaderView>
#include <QMessageBox>
#include "addProduct.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    std::cout << "Starting Automated Inventory Management System...\n";

    // Create main window
    QMainWindow window;
    window.setWindowTitle("Inventory Management System");
    window.setMinimumSize(800, 600);

    // Create central widget and layout
    QWidget *centralWidget = new QWidget(&window);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create search section
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLineEdit *searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Search products...");
    QPushButton *searchButton = new QPushButton("Search");
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(searchButton);
    mainLayout->addLayout(searchLayout);

    // Create table for inventory
    QTableWidget *inventoryTable = new QTableWidget();
    inventoryTable->setColumnCount(6);
    inventoryTable->setHorizontalHeaderLabels({"ID", "Product Name", "Quantity", "Price", "Category", "Last Updated"});
    
    // Set table properties
    inventoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    inventoryTable->setSelectionBehavior(QTableWidget::SelectRows);
    inventoryTable->setSelectionMode(QTableWidget::SingleSelection);
    inventoryTable->setEditTriggers(QTableWidget::NoEditTriggers);
    mainLayout->addWidget(inventoryTable);

    // Create buttons section
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    
    QPushButton *addButton = new QPushButton("Add Product");
    QPushButton *editButton = new QPushButton("Edit Product");
    QPushButton *deleteButton = new QPushButton("Delete Product");
    QPushButton *refreshButton = new QPushButton("Refresh");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(refreshButton);
    mainLayout->addLayout(buttonLayout);

    // Create status bar
    QLabel *statusLabel = new QLabel("Total Products: 0");
    mainLayout->addWidget(statusLabel);

    // Connect button signals
    QObject::connect(addButton, &QPushButton::clicked, [&]() {
        AddProductDialog dialog(&window);
        if(dialog.exec() == QDialog::Accepted) {
            QString name = dialog.getName();
            double price = dialog.getPrice();
            int quantity = dialog.getQuantity();
            QString category = dialog.getCategory();
        }
        // Add the product to the inventory
        DatabaseManager.addProduct(name, price, quantity, category);

        // Refresh the table (you'll need to implement this)
        // refreshInventoryTable(inventoryTable, inventoryManager);
    });

    QObject::connect(editButton, &QPushButton::clicked, [&]() {
        if (inventoryTable->selectedItems().isEmpty()) {
            QMessageBox::warning(&window, "Warning", "Please select a product to edit");
            return;
        }
        QMessageBox::information(&window, "Edit Product", "Edit Product functionality will be implemented here");
    });

    QObject::connect(deleteButton, &QPushButton::clicked, [&]() {
        if (inventoryTable->selectedItems().isEmpty()) {
            QMessageBox::warning(&window, "Warning", "Please select a product to delete");
            return;
        }
        auto reply = QMessageBox::question(&window, "Confirm Delete", 
            "Are you sure you want to delete this product?",
            QMessageBox::Yes|QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            QMessageBox::information(&window, "Delete Product", "Delete functionality will be implemented here");
        }
    });

    QObject::connect(searchButton, &QPushButton::clicked, [&]() {
        QString searchText = searchBar->text();
        QMessageBox::information(&window, "Search", 
            "Searching for: " + searchText + "\nSearch functionality will be implemented here");
    });

    // Add some sample data
    inventoryTable->setRowCount(3);
    
    // Row 1
    inventoryTable->setItem(0, 0, new QTableWidgetItem("1"));
    inventoryTable->setItem(0, 1, new QTableWidgetItem("Laptop"));
    inventoryTable->setItem(0, 2, new QTableWidgetItem("10"));
    inventoryTable->setItem(0, 3, new QTableWidgetItem("$999.99"));
    inventoryTable->setItem(0, 4, new QTableWidgetItem("Electronics"));
    inventoryTable->setItem(0, 5, new QTableWidgetItem("2024-03-20"));

    // Row 2
    inventoryTable->setItem(1, 0, new QTableWidgetItem("2"));
    inventoryTable->setItem(1, 1, new QTableWidgetItem("Mouse"));
    inventoryTable->setItem(1, 2, new QTableWidgetItem("50"));
    inventoryTable->setItem(1, 3, new QTableWidgetItem("$29.99"));
    inventoryTable->setItem(1, 4, new QTableWidgetItem("Electronics"));
    inventoryTable->setItem(1, 5, new QTableWidgetItem("2024-03-20"));

    // Row 3
    inventoryTable->setItem(2, 0, new QTableWidgetItem("3"));
    inventoryTable->setItem(2, 1, new QTableWidgetItem("Keyboard"));
    inventoryTable->setItem(2, 2, new QTableWidgetItem("30"));
    inventoryTable->setItem(2, 3, new QTableWidgetItem("$49.99"));
    inventoryTable->setItem(2, 4, new QTableWidgetItem("Electronics"));
    inventoryTable->setItem(2, 5, new QTableWidgetItem("2024-03-20"));

    statusLabel->setText("Total Products: " + QString::number(inventoryTable->rowCount()));

    window.setCentralWidget(centralWidget);
    window.show();

    return app.exec();
}
