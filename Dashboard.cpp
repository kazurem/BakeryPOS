#include "Dashboard.h"
#include "EditProductForm.h" // Add this include
#include "ui_Dashboard.h"

#include "Utils.h"
#include <login.h>

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>

#include <QButtonGroup>
#include <QMessageBox>
#include <QPushButton>

dashboard::dashboard(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::dashboard) {
    ui->setupUi(this);

    QSqlDatabase db =
        QSqlDatabase::addDatabase("QMYSQL"); // Or QSQLITE, QPSQL, etc.
    db.setHostName("localhost");
    db.setDatabaseName("mydb");
    db.setUserName("root");
    db.setPassword("khalid");
    db.open();

    this->Model     = new QSqlQueryModel(this);
    this->BaseQuery = "SELECT * FROM products";
    Model->setQuery(BaseQuery);
    ui->ProductPageTableView->setModel(Model);
    UpdateProductRecordCountLabel();

    SetupUI();
}

dashboard::~dashboard() { delete ui; }

void dashboard::SetupUI() {

    // painting the table

    ui->ProductPageTableView->setItemDelegate(
        new CustomTableDelegate(ui->ProductPageTableView));
    ui->UserPageTableView->setItemDelegate(
        new CustomTableDelegate(ui->ProductPageTableView));

    // Distribute columns based on content size
    ui->ProductPageTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    // left-align header text, vertically centered
    ui->ProductPageTableView->horizontalHeader()->setDefaultAlignment(
        Qt::AlignLeft | Qt::AlignVCenter);
    // Distribute columns based on content size
    ui->UserPageTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    // left-align header text, vertically centered
    ui->UserPageTableView->horizontalHeader()->setDefaultAlignment(
        Qt::AlignLeft | Qt::AlignVCenter);

    QButtonGroup *SidebarGroup = new QButtonGroup(this);
    SidebarGroup->setExclusive(true);

    SidebarGroup->addButton(ui->UsersButton);
    SidebarGroup->addButton(ui->InvoiceButton);
    SidebarGroup->addButton(ui->ProductsButton);
    SidebarGroup->addButton(ui->CategoriesButton);
    SidebarGroup->addButton(ui->AnalyticsButton);

    // Remove this line - using auto-connection instead
    // connect(ui->EditProductButton, &QPushButton::clicked, this,
    //         &dashboard::onEditButtonClicked);
    connect(ui->ProductPageTableView->horizontalHeader(),
            &QHeaderView::sectionClicked, this,
            &dashboard::OnProductHeaderSectionClicked);
    connect(ui->UserPageTableView->horizontalHeader(),
            &QHeaderView::sectionClicked, this,
            &dashboard::OnUserHeaderSectionClicked);
    ui->MainDisplayStackedWidget->setCurrentIndex(0);
}

// Removed onEditButtonClicked() method - using on_EditProductButton_clicked()
// instead

void dashboard::refreshProductData() {
    // Refresh the product data in the table
    ApplyFiltersForProducts();
    qDebug() << "Product data refreshed after edit";
}

void dashboard::ApplyFiltersForProducts(const QString &SortColumn,
                                        const QString &SortOrder) {
    QString     Query = BaseQuery;
    QStringList Conditions;

    if (!CurrentCategoryFilter.isEmpty() && CurrentCategoryFilter != "All") {
        Conditions << QString("Category = '%1'").arg(CurrentCategoryFilter);
    }

    if (!CurrentSearchFilter.isEmpty()) {
        Conditions << QString("Name LIKE '%1%'").arg(CurrentSearchFilter);
    }

    if (!Conditions.isEmpty()) {
        Query += " WHERE " + Conditions.join(" AND ");
    }

    // Add ORDER BY if sorting is specified
    if (!SortColumn.isEmpty()) {
        Query += QString(" ORDER BY `%1` %2").arg(SortColumn, SortOrder);
    }

    qDebug() << "Final query:" << Query;
    Model->setQuery(Query);
    UpdateProductRecordCountLabel();
}

void dashboard::ApplyFiltersForUsers(const QString &SortColumn,
                                     const QString &SortOrder) {
    QString     Query = BaseQuery;
    QStringList Conditions;

    if (!CurrentCategoryFilter.isEmpty() && CurrentCategoryFilter != "All") {
        Conditions << QString("Role = '%1'").arg(CurrentCategoryFilter);
    }

    if (!CurrentSearchFilter.isEmpty()) {
        Conditions << QString("username LIKE '%1%'").arg(CurrentSearchFilter);
    }

    if (!Conditions.isEmpty()) {
        Query += " WHERE " + Conditions.join(" AND ");
    }

    // Add ORDER BY if sorting is specified
    if (!SortColumn.isEmpty()) {
        Query += QString(" ORDER BY `%1` %2").arg(SortColumn, SortOrder);
    }

    qDebug() << "Final query:" << Query;
    Model->setQuery(Query);
    UpdateUserRecordCountLabel();
}

void dashboard::ApplyFiltersForProducts() { ApplyFiltersForProducts("", ""); }
void dashboard::ApplyFiltersForUsers() { ApplyFiltersForUsers("", ""); }

void dashboard::on_FilterCategoryComboBox_currentIndexChanged() {
    CurrentCategoryFilter = ui->FilterCategoryComboBox->currentText();
    ApplyFiltersForProducts();
}

void dashboard::on_SearchProductByNameLineEdit_returnPressed() {
    CurrentSearchFilter = ui->SearchProductByNameLineEdit->text();
    ApplyFiltersForProducts();
}

void dashboard::OnProductHeaderSectionClicked(int LogicalIndex) {
    static int  LastSortedColumn = -1;
    static bool Ascending        = true;

    QString ColumnName =
        Model->headerData(LogicalIndex, Qt::Horizontal).toString();
    ColumnName = ColumnName.trimmed().replace(" ", "_");

    if (LastSortedColumn == LogicalIndex) {
        Ascending = !Ascending;
    } else {
        Ascending        = true;
        LastSortedColumn = LogicalIndex;
    }

    QString Order = Ascending ? "ASC" : "DESC";

    // Now apply both filtering and sorting
    ApplyFiltersForProducts(ColumnName, Order);
    UpdateProductRecordCountLabel();
}

void dashboard::OnUserHeaderSectionClicked(int LogicalIndex) {
    static int  LastSortedColumn = -1;
    static bool Ascending        = true;

    QString ColumnName =
        Model->headerData(LogicalIndex, Qt::Horizontal).toString();
    ColumnName = ColumnName.trimmed().replace(" ", "_");

    if (LastSortedColumn == LogicalIndex) {
        Ascending = !Ascending;
    } else {
        Ascending        = true;
        LastSortedColumn = LogicalIndex;
    }

    QString Order = Ascending ? "ASC" : "DESC";

    // Now apply both filtering and sorting
    ApplyFiltersForUsers(ColumnName, Order);
    UpdateProductRecordCountLabel();
}

void dashboard::UpdateProductRecordCountLabel() {
    ui->NumberOfProductRecordsShownLabel->setText(
        QString("Showing %1 records").arg(Model->rowCount()));
}

void dashboard::UpdateUserRecordCountLabel() {
    ui->NumberOfUserRecordsShownLabel->setText(
        QString("Showing %1 records").arg(Model->rowCount()));
}

void dashboard::on_EditProductButton_clicked() {
    QModelIndexList selectedIndexes =
        ui->ProductPageTableView->selectionModel()->selectedRows();

    if (!selectedIndexes.isEmpty()) {
        int selectedRow = selectedIndexes.first().row();

        // Get ProductID from the first column (assuming ProductID is in column
        // 0)
        QModelIndex productIdIndex =
            ui->ProductPageTableView->model()->index(selectedRow, 0);
        int productId =
            ui->ProductPageTableView->model()->data(productIdIndex).toInt();

        // Get Product Name for confirmation
        QModelIndex nameIndex = ui->ProductPageTableView->model()->index(
            selectedRow, 1); // column 1 = Name
        QString productName =
            ui->ProductPageTableView->model()->data(nameIndex).toString();

        qDebug() << "Selected Product ID:" << productId;
        qDebug() << "Product Name:" << productName;

        // Create and show the edit form
        EditProductForm *editForm = new EditProductForm(this);
        editForm->loadProductData(productId);

        // Connect the productUpdated signal to refresh the table
        connect(editForm, &EditProductForm::productUpdated, this,
                &dashboard::refreshProductData);

        editForm->show();

    } else {
        QMessageBox::warning(this, "No Selection",
                             "Please select a product to edit.");
    }
}

void dashboard::on_DeleteProductButton_clicked() {
    QModelIndexList selectedIndexes =
        ui->ProductPageTableView->selectionModel()->selectedRows();

    if (!selectedIndexes.isEmpty()) {
        int selectedRow = selectedIndexes.first().row();

        // Get ProductID
        QModelIndex productIdIndex =
            ui->ProductPageTableView->model()->index(selectedRow, 0);
        int productId =
            ui->ProductPageTableView->model()->data(productIdIndex).toInt();

        // Get detailed product information from database
        QSqlQuery query;
        query.prepare("SELECT ProductID, Name, Category, PricePerKg, "
                      "PricePerUnit, StockQuantity, UnitType, date_added, "
                      "status FROM products WHERE ProductID = ?");
        query.bindValue(0, productId);

        if (query.exec() && query.next()) {
            // Extract all product details
            QString  productName   = query.value("Name").toString();
            QString  category      = query.value("Category").toString();
            QVariant pricePerKg    = query.value("PricePerKg");
            QVariant pricePerUnit  = query.value("PricePerUnit");
            double   stockQuantity = query.value("StockQuantity").toDouble();
            QString  unitType      = query.value("UnitType").toString();
            QString  dateAdded     = query.value("date_added").toString();
            QString  status        = query.value("status").toString();

            // Format pricing information
            QString priceInfo;
            if (!pricePerKg.isNull() && !pricePerUnit.isNull()) {
                priceInfo = QString("Price per KG: $%1\nPrice per Unit: $%2")
                                .arg(pricePerKg.toDouble(), 0, 'f', 2)
                                .arg(pricePerUnit.toDouble(), 0, 'f', 2);
            } else if (!pricePerKg.isNull()) {
                priceInfo = QString("Price per KG: $%1")
                                .arg(pricePerKg.toDouble(), 0, 'f', 2);
            } else if (!pricePerUnit.isNull()) {
                priceInfo = QString("Price per Unit: $%1")
                                .arg(pricePerUnit.toDouble(), 0, 'f', 2);
            } else {
                priceInfo = "No pricing information available";
            }

            // Create detailed confirmation message
            QString detailedMessage =
                QString(
                    "You are about to delete the following product:\n\n"
                    "Product ID: %1\n"
                    "Name: %2\n"
                    "Category: %3\n"
                    "%4\n"
                    "Stock Quantity: %5 %6\n"
                    "Status: %7\n"
                    "Date Added: %8\n\n"
                    "⚠️ WARNING: This action cannot be undone!\n\n"
                    "Are you sure you want to permanently delete this product?")
                    .arg(productId)
                    .arg(productName)
                    .arg(category)
                    .arg(priceInfo)
                    .arg(stockQuantity, 0, 'f', 2)
                    .arg(unitType)
                    .arg(status)
                    .arg(dateAdded);

            // Create custom message box with detailed information
            QMessageBox confirmBox;
            confirmBox.setWindowTitle("Confirm Product Deletion");
            confirmBox.setText("Delete Product Confirmation");
            confirmBox.setDetailedText(detailedMessage);
            confirmBox.setIcon(QMessageBox::Warning);
            confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            confirmBox.setDefaultButton(QMessageBox::No);

            // Set the main text to be more prominent
            confirmBox.setInformativeText(
                QString("Are you sure you want to delete product: \"%1\"?")
                    .arg(productName));

            // Show detailed text by default
            foreach (QAbstractButton *button, confirmBox.buttons()) {
                if (confirmBox.buttonRole(button) == QMessageBox::ActionRole) {
                    button->click();
                    break;
                }
            }

            int result = confirmBox.exec();

            if (result == QMessageBox::Yes) {
                // Proceed with deletion
                QSqlQuery deleteQuery;
                deleteQuery.prepare("DELETE FROM products WHERE ProductID = ?");
                deleteQuery.bindValue(0, productId);

                if (deleteQuery.exec()) {
                    QMessageBox::information(
                        this, "Success",
                        QString("Product \"%1\" has been deleted successfully!")
                            .arg(productName));
                    refreshProductData();
                } else {
                    QMessageBox::critical(
                        this, "Database Error",
                        "Failed to delete product from database:\n" +
                            deleteQuery.lastError().text());
                }
            }
        } else {
            QMessageBox::critical(this, "Error",
                                  "Failed to retrieve product details:\n" +
                                      query.lastError().text());
        }
    } else {
        QMessageBox::warning(
            this, "No Selection",
            "Please select a product from the table to delete.");
    }
}

void dashboard::on_AddProductButton_clicked() {
    // Create a new EditProductForm for adding (without loading existing data)
    EditProductForm *addForm = new EditProductForm(this);
    addForm->setWindowTitle("Add New Product");

    // Connect the productUpdated signal to refresh the table
    connect(addForm, &EditProductForm::productUpdated, this,
            &dashboard::refreshProductData);

    addForm->show();
}

void dashboard::on_FilterRoleComboBox_currentIndexChanged() {
    CurrentCategoryFilter = ui->FilterRoleComboBox->currentText();
    ApplyFiltersForUsers();
}

void dashboard::on_UsersButton_clicked() {
    ui->MainDisplayStackedWidget->setCurrentIndex(3);
    this->BaseQuery = "SELECT * FROM users";
    this->Model->setQuery(BaseQuery);
    ui->UserPageTableView->setModel(Model);
    UpdateUserRecordCountLabel();
}

void dashboard::on_ProductsButton_clicked() {
    ui->MainDisplayStackedWidget->setCurrentIndex(0);
    this->BaseQuery = "SELECT * FROM products";
    this->Model->setQuery(BaseQuery);
    ui->ProductPageTableView->setModel(Model);
}

void dashboard::on_SearchUserByNameLineEdit_returnPressed() {
    CurrentSearchFilter = ui->SearchUserByNameLineEdit->text();
    ApplyFiltersForUsers();
}

void dashboard::on_CategoriesButton_clicked() {
    ui->MainDisplayStackedWidget->setCurrentIndex(6);
}

void dashboard::on_LogoutButton_clicked() {
    if (QMessageBox::question(this, "Confirm Logout",
                              "Are you sure you want to logout?") ==
        QMessageBox::Yes) {
        this->close();
        login *Lgn = new login();
        Lgn->show();
    }
}
