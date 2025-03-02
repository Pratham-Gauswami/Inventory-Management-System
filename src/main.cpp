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
#include <sqlite3.h> //#include sqllite3 header file
#include <QDebug> //For debugging output
#include "../include/addProduct.h"
#include "../include/DatabaseManager.h"


//Function to initlaize the database and create the products table
bool initializeDatabase(sqlite3 *&db) {
    int rc = sqlite3_open("inventory.db", &db); //Open or create the database file
    if (rc) {
        qDebug() << "Can't open Database:" << sqlite3_errmsg(db);
        return false;
    }

    //SQL statemnts/queries to create the products table
    const char *sql = "CREATE TABLE IF NOT EXISTS products ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "name TEXT NOT NULL, "
                      "quantity INTEGER NOT NULL, "
                      "price REAL NOT NULL, "
                      "category TEXT NOT NULL, "
                      "last_updated TEXT NOT NULL);";

    char *zErrMsg = 0;
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg); //Execute the sql statement
    if(rc != SQLITE_OK) {
        qDebug() << "SQL error:" << zErrMsg;
        sqlite3_free(zErrMsg);
        return false;
    }

    qDebug() << "Database initialized successfully.";
    return true;

}

void refreshInventoryTable(sqlite3 *db, QTableWidget *inventoryTable) {

    //Clear the table
    inventoryTable->setRowCount(0);

    //SQL statement to fetch all the products
    const char *sql = "SELECT * FROM products;";
    sqlite3_stmt *stmt;

    //Prepare the SQL statement
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) 
    {
        qDebug() << "Failed to fetch the data:" << sqlite3_errmsg(db);
        return;
    }

    //Execute the statement and fetch rows
    int row = 0;
    while(sqlite3_step(stmt) == SQLITE_ROW) {
        inventoryTable->insertRow(row);

        //fetch columns and populate the rows
        for(int col = 0; col < 6; col++)
        {
            QString value = QString::fromUtf8((const char *)sqlite3_column_text(stmt, col));
            inventoryTable->setItem(row, col, new QTableWidgetItem(value));
        }
        row++;
    }

    //Finalize the statement
    sqlite3_finalize(stmt);
    qDebug() << "Inventory table refreshed.";
    
}


bool deleteProduct(sqlite3 *db, int id) {
    QString sql = QString("DELETE FROM products WHERE id = %1;").arg(id);

    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.toStdString().c_str(), 0, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        qDebug() << "SQL error:" << zErrMsg;
        sqlite3_free(zErrMsg);
        return false;
    }

    qDebug() << "Product(s) deleted successfully.";
    return false;
}


int main(int argc, char *argv[]) {

    sqlite3 *db;
    if(!initializeDatabase(db)) {
        return 1;
    }

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
        
        //Add the product to the database
        if(addProduct(db, name, price, quantity, category)) {
            //Refresh the table
            refreshInventoryTable(db, inventoryTable);
        }
    }
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
        int id = inventoryTable->item(inventoryTable->currentRow(), 0)->text().toInt();
        auto reply = QMessageBox::question(&window, "Confirm Delete", 
            "Are you sure you want to delete this product?",
            QMessageBox::Yes|QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            QMessageBox::information(&window, "Delete Product", "Delete functionality will be implemented here");
        }
        if(reply == QMessageBox::Yes) {
            if(deleteProduct(db, id)) {
                refreshInventoryTable(db, inventoryTable); //Refresh the table
            }
        }
    });

    QObject::connect(searchButton, &QPushButton::clicked, [&]() {
        QString searchText = searchBar->text();
        QMessageBox::information(&window, "Search", 
            "Searching for: " + searchText + "\nSearch functionality will be implemented here");
    });

    QObject::connect(refreshButton, &QPushButton::clicked, [&]() {
        refreshInventoryTable(db, inventoryTable);
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
    sqlite3_close(db);

    return app.exec();
}
