#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DatabaseManger {
public:
    
    void initalizeDatabase() {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS products ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name TEXT NOT NULL, "
                "price REAL NOT NULL, "
                "quantity INTEGER NOT NULL, "
                "category TEXT NOT NULL, "
                "last_updated TEXT NOT NULL)");
    }

    DatabaseManger(const QString& path) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path);

        if(!db.open()){
            qDebug() << "Error: Could not open database.";
        } else {
            initializeDatabase();
        }
    }

    ~DatabaseManger() {
        db.close;
    }

    bool addProduct(const QString& name, double price, int quantity, const QString& category) 
    {
        QSqlQuery query;
        query.prepare("INSERT INTO products (name, price, quantity, category, last_updated) "
                      "VALUES (:name, :price, :quantity, :category, :last_updated)");
        query.bindValue(":name", name);
        query.bindValue(":price", price);
        query.bindValue(":quantity", quantity);
        query.bindValue(":category", category);
        query.bindValue(":last_updated", QDateTime::currentDateTime().toString());

        return query.exec();

    }

    QVector<Product> getAllProducts() {
        QVector<Product> products;
        QSqlQuery query("SELECT * FROM products");

        while (query.next()) {
            Product product(
                query.value("id").toInt(),
                query.value("name").toString(),
                query.value("price").toDouble(),
                query.value("quantity").toInt(),
                query.value("category").toString()
            );
            products.append(product);
        }

        return products;
    }

private:
    QSqlDatabase db;
};