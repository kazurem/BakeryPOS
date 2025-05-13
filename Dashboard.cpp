#include "Dashboard.h"
#include "ui_Dashboard.h"

// Temporary Section --------------------------------------------
struct Item {
    QString name;
    int     quantity;
    double  unitPrice;
};

QList<Item> items = {
    {"Baguette",        2, 1.50 },
    {"Chocolate Cake",  1, 12.00},
    {"Croissant",       6, 0.90 },
    {"Muffin",          4, 1.25 },
    {"Sourdough Bread", 1, 3.75 },
    {"Apple Pie",       1, 5.50 },
    {"Cinnamon Roll",   3, 2.00 },
    {"Donut",           5, 1.10 }
};
//--------------------------------------------------------------
dashboard::dashboard(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::dashboard) {
    ui->setupUi(this);

    // Temporary Section
    // ------------------------------------------------------------
    ui->XPageTableWidget->setRowCount(0); // clear any existing rows
    ui->XPageTableWidget->setColumnCount(4);
    ui->XPageTableWidget->setHorizontalHeaderLabels(
        {"Product", "Quantity", "Unit Price", "Total"});

    for (const auto &item : items) {
        int row = ui->XPageTableWidget->rowCount();
        ui->XPageTableWidget->insertRow(row);

        double total = item.quantity * item.unitPrice;

        QTableWidgetItem *nameItem = new QTableWidgetItem(item.name);
        QTableWidgetItem *qtyItem =
            new QTableWidgetItem(QString::number(item.quantity));
        QTableWidgetItem *priceItem =
            new QTableWidgetItem(QString::number(item.unitPrice, 'f', 2));
        QTableWidgetItem *totalItem =
            new QTableWidgetItem(QString::number(total, 'f', 2));

        // Alignment & Read-Only
        for (QTableWidgetItem *it : {nameItem, qtyItem, priceItem, totalItem}) {
            it->setFlags(it->flags() & ~Qt::ItemIsEditable);
            it->setTextAlignment(Qt::AlignCenter);
        }

        ui->XPageTableWidget->setItem(row, 0, nameItem);
        ui->XPageTableWidget->setItem(row, 1, qtyItem);
        ui->XPageTableWidget->setItem(row, 2, priceItem);
        ui->XPageTableWidget->setItem(row, 3, totalItem);
    }
    //-----------------------------------------------------------------------------
}

dashboard::~dashboard() { delete ui; }

void dashboard::on_AddXButton_clicked() {
    ui->MainDisplayStackedWidget->setCurrentIndex(1);
}
