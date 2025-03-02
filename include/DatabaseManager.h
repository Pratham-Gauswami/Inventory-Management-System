#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <QString>

// Function to add a product to the database
bool addProduct(sqlite3 *db, const QString &name, double price, int quantity, const QString &category);

#endif // DATABASE_H