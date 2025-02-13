#pragma once

#include <QString>
#include <QVector>
#include <QDateTime>

class Product {
private: 
    int id;
    QString name;
    double price;
    int quantity;
    QString category;
    QDateTime lastUpdated;

public:
    Product(int id, const QString& name, double price, int quantity, const QString& category);

    //Getters
    int getId() const {return id;}
    QString getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    QString getCategory() const { return category; }
    QDateTime getLastUpdated() const {return lastUpdated; }

    //Setters
    void setQuantity(int newQuantity);
    void setPrice(double newPrice);
    void updateLastUpdated();
};

class InventoryManager {
private:
    QVector<Product> products;
    int nextProductId;

public:
    InventoryManager();
    void addProduct(const QString& name, double price, int quantity, const QString& category);
    void removeProduct(int id);
    void updateQuantity(int id, int newQuantity);
    void updatePrice(int id, double newPrice);
    QVector<Product> getAllProducts() const;
    QVector<Product> searchProducts(const QString& query) const;
};