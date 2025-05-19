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
    UpdateRecordCountLabel();

    SetupUI();
}

dashboard::~dashboard() { delete ui; }

void dashboard::SetupUI() {

    // painting the table
    ui->ProductPageTableView->setItemDelegate(
        new CustomTableDelegate(ui->ProductPageTableView));

    // Distribute columns based on content size
    ui->ProductPageTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    // left-align header text, vertically centered
    ui->ProductPageTableView->horizontalHeader()->setDefaultAlignment(
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
            &dashboard::OnHeaderSectionClicked);
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

void dashboard::ApplyFilters(const QString &SortColumn,
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
    UpdateRecordCountLabel();
}

void dashboard::ApplyFilters() { ApplyFilters("", ""); }

void dashboard::on_FilterCategoryComboBox_currentIndexChanged() {
    CurrentCategoryFilter = ui->FilterCategoryComboBox->currentText();
    ApplyFilters();
}

void dashboard::on_SearchProductByNameLineEdit_returnPressed() {
    CurrentSearchFilter = ui->SearchProductByNameLineEdit->text();
    ApplyFilters();
}

void dashboard::OnHeaderSectionClicked(int LogicalIndex) {
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
    ApplyFilters(ColumnName, Order);

    UpdateRecordCountLabel();
}

void dashboard::UpdateRecordCountLabel() {
    ui->NumberOfRecordsShownLabel->setText(
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
