#include "../include/DatabaseManager.h"
#include <QDebug>

bool addProduct(sqlite3 *db, const QString &name, double price, int quantity, const QString &category) {
    // Construct the SQL query
    QString sql = QString("INSERT INTO products (name, quantity, price, category, last_updated) "
                          "VALUES ('%1', %2, %3, '%4', datetime('now'));")
                          .arg(name).arg(quantity).arg(price).arg(category);

    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.toStdString().c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        qDebug() << "SQL error:" << zErrMsg;
        sqlite3_free(zErrMsg);
        return false;
    }

    qDebug() << "Product added successfully.";
    return true;
}