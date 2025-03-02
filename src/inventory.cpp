#include "../include/inventory.h"

Product::Product(int id, const QString& name, double price, int quantity, const QString& category)
    : id(id), name(name), price(price), quantity(quantity), category(category) {
    updateLastUpdated();
}

void Product::setQuantity(int newQuantity) {
    quantity = newQuantity;
    updateLastUpdated();
}

void Product::setPrice(double newPrice) {
    price = newPrice;
    updateLastUpdated();
}

void Product::updateLastUpdated() {
    lastUpdated = QDateTime::currentDateTime();
}

InventoryManager::InventoryManager() : nextProductId(1) {}

void InventoryManager::addProduct(const QString& name, double price, int quantity, const QString& category) {
    products.append(Product(nextProductId++, name, price, quantity, category));
}

void InventoryManager::removeProduct(int id) {
    for (int i = 0; i < products.size(); ++i) {
        if (products[i].getId() == id) {
            products.removeAt(i);
            break;
        }
    }
}

void InventoryManager::updateQuantity(int id, int newQuantity) {
    for (auto& product : products) {
        if (product.getId() == id) {
            product.setQuantity(newQuantity);
            break;
        }
    }
}

void InventoryManager::updatePrice(int id, double newPrice) {
    for (auto& product : products) {
        if (product.getId() == id) {
            product.setPrice(newPrice);
            break;
        }
    }
}

QVector<Product> InventoryManager::getAllProducts() const {
    return products;
}

QVector<Product> InventoryManager::searchProducts(const QString& query) const {
    QVector<Product> results;
    QString lowercaseQuery = query.toLower();
    
    for (const auto& product : products) {
        if (product.getName().toLower().contains(lowercaseQuery) ||
            product.getCategory().toLower().contains(lowercaseQuery)) {
            results.append(product);
        }
    }
    return results;
}