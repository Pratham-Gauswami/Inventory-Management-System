#include "../include/addProduct.h"

AddProductDialog::AddProductDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add Product");

    QFormLayout *form = new QFormLayout(this);
    nameEdit = new QLineEdit(this);
    priceEdit = new QDoubleSpinBox(this);
    priceEdit->setRange(0, 999999);
    quantityEdit = new QSpinBox(this);
    quantityEdit->setRange(0, 999999);
    categoryEdit = new QComboBox(this);
    categoryEdit->addItems({"Electronics", "Clothing", "Food", "Other"});

    form->addRow("Name:", nameEdit);
    form->addRow("Price:", priceEdit);
    form->addRow("Quantity:", quantityEdit);
    form->addRow("Category:", categoryEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    form->addRow(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QString AddProductDialog::getName() const {
    return nameEdit->text();
}

double AddProductDialog::getPrice() const {
    return priceEdit->value();
}

int AddProductDialog::getQuantity() const {
    return quantityEdit->value();
}

QString AddProductDialog::getCategory() const {
    return categoryEdit->currentText();
}