#include "Dashboard.h"
#include "ui_Dashboard.h"

#include "Utils.h"

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

    connect(ui->EditProductButton, &QPushButton::clicked, this,
            &dashboard::onEditButtonClicked);
    connect(ui->ProductPageTableView->horizontalHeader(),
            &QHeaderView::sectionClicked, this,
            &dashboard::OnProductHeaderSectionClicked);
    connect(ui->UserPageTableView->horizontalHeader(),
            &QHeaderView::sectionClicked, this,
            &dashboard::OnUserHeaderSectionClicked);
    ui->MainDisplayStackedWidget->setCurrentIndex(0);
}

void dashboard::onEditButtonClicked() {
    QModelIndexList selectedIndexes =
        ui->ProductPageTableView->selectionModel()->selectedRows();

    if (!selectedIndexes.isEmpty()) {
        int selectedRow = selectedIndexes.first().row();

        QModelIndex index = ui->ProductPageTableView->model()->index(
            selectedRow, 1); // column 1 = Name
        QVariant data = ui->ProductPageTableView->model()->data(index);
        qDebug() << "Selected row:" << selectedRow + 1;
        qDebug() << "Product Name:" << data.toString();

        // You can now use this data to pre-fill your edit form or sidebar
    } else {
        QMessageBox::warning(this, "No Selection",
                             "Please select a product to edit.");
    }
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
    // Create a edit product window
}

void dashboard::on_DeleteProductButton_clicked() {
    // Create a delete confirmation window
}

void dashboard::on_AddProductButton_clicked() {
    // Create a Add product window
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
