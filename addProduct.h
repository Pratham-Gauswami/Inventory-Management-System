#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QFormLayout>
#include <QDialogButtonBox>

class AddProductDialog : public QDialog {
    Q_OBJECT

public: 
    AddProductDialog(QWidget * parent = nullptr);

    QString getName() const;
    double getPrice() const;
    int getQuantity() const;
    QString getCategory() const;

private:
    QLineEdit *nameEdit;
    QDoubleSpinBox *priceEdit;
    QSpinBox *quantityEdit;
    QComboBox *categoryEdit;
};

#endif 