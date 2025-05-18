#include "Dashboard.h"
#include "ui_Dashboard.h"

#include <QEasingCurve>
#include <QPropertyAnimation>

#include <QPainter>
#include <QStyledItemDelegate>

#include <QPainter>
#include <QStyledItemDelegate>

#include <QPainter>
#include <QPainterPath>
#include <QStyledItemDelegate>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>

class CustomTableDelegate : public QStyledItemDelegate {
  public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override {
        QStyleOptionViewItem opt(option);
        initStyleOption(&opt, index);

        QStyledItemDelegate::paint(painter, opt, index);

        int row      = index.row();
        int col      = index.column();
        int rowCount = index.model()->rowCount();
        int colCount = index.model()->columnCount();

        painter->save();

        // Draw bold line below the header (above first row)
        if (row == 0) {
            QPen headerPen(QColor("#1F1F1F"), 2); // bold/dark line
            painter->setPen(headerPen);
            painter->drawLine(opt.rect.topLeft(), opt.rect.topRight());
        }

        // Draw row separator under each cell (except last row if you want)
        if (row < rowCount - 1) {
            QPen rowPen(QColor("#ccc"), 1); // normal row separator
            painter->setPen(rowPen);
            painter->drawLine(opt.rect.bottomLeft(), opt.rect.bottomRight());
        }

        // Don't draw vertical lines on left/right edges
        if (col > 0 && col < colCount - 1) {
            // Optional: you could draw vertical lines here if you wanted.
            // We're skipping them to remove column separators.
        }

        painter->restore();
    }
};

// to use it: ui->tableWidget->setItem(row, column, new
// LeftAlignedItem(value.toString()))
class LeftAlignedItem : public QTableWidgetItem {
  public:
    LeftAlignedItem(const QString &text) : QTableWidgetItem(text) {
        setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
};

// Temporary Section --------------------------------------------
struct Item {
    QString name;
    int     quantity;
    double  unitPrice;
    QString x1;
};

QList<Item> items = {
    {"Baguette",        2, 1.50,  "kg" },
    {"Chocolate Cake",  1, 12.00, "kg" },
    {"Choissant",       6, 0.90,  "pcs"},
    {"Muffin",          4, 1.25,  "kg" },
    {"Sourdough Bread", 1, 3.75,  "pcs"},
    {"Apple Pie",       1, 5.50,  "kg" },
    {"Cinnamon Roll",   3, 2.00,  "pcs"},
    {"Donut",           5, 1.10,  "kg" },
    {"Donut",           5, 1.10,  "pcs"},
    {"Donut",           5, 1.10,  "kg" },
    {"Donut",           5, 1.10,  "kg" },
    {"Donut",           5, 1.10,  "kg" },
    {"Donut",           5, 1.10,  "kg" },
    {"Donut",           5, 1.10,  "kg" },
    {"Donut",           5, 1.10,  "kg" },
    {"Donut",           5, 1.10,  "kg" },
};
//--------------------------------------------------------------

dashboard::dashboard(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::dashboard) {
    ui->setupUi(this);

    // Temporary Section
    // ------------------------------------------------------------
    ui->ProductPageTableWidget->setRowCount(0); // clear any existing rows
    ui->ProductPageTableWidget->setColumnCount(5);
    ui->ProductPageTableWidget->setHorizontalHeaderLabels(
        {"Product", "Stock Quantity", "Unit Price", "Unit", ""});

    for (const auto &item : items) {
        int row = ui->ProductPageTableWidget->rowCount();
        ui->ProductPageTableWidget->insertRow(row);

        LeftAlignedItem *nameItem = new LeftAlignedItem(item.name);
        LeftAlignedItem *qtyItem =
            new LeftAlignedItem(QString::number(item.quantity));
        LeftAlignedItem *priceItem =
            new LeftAlignedItem(QString::number(item.unitPrice, 'f', 2));
        // LeftAlignedItem *totalItem =
        //     new LeftAlignedItem(QString::number(total, 'f', 2));
        LeftAlignedItem *X1 = new LeftAlignedItem(item.x1);

        // Alignment & Read-Only
        for (LeftAlignedItem *it : {nameItem, qtyItem, priceItem, X1}) {
            it->setFlags(it->flags() & ~Qt::ItemIsEditable);
        }

        ui->ProductPageTableWidget->setItem(row, 0, nameItem);
        ui->ProductPageTableWidget->setItem(row, 1, qtyItem);
        ui->ProductPageTableWidget->setItem(row, 2, priceItem);
        ui->ProductPageTableWidget->setItem(row, 3, X1);
    }

    SetupUI();
}

dashboard::~dashboard() { delete ui; }

void dashboard::AddDeleteAndEditButtonsToTableRows(QTableWidget *Table) {
    int RowCount    = Table->rowCount();
    int ColumnCount = Table->columnCount();

    for (int Row = 0; Row < RowCount; Row++) {
        // Create buttons
        QPushButton *Btn_Delete = new QPushButton();
        QPushButton *Btn_Edit   = new QPushButton();

        // Set icons only (no text)
        Btn_Delete->setIcon(QIcon(":/icons/delete.png"));
        Btn_Edit->setIcon(QIcon(":/icons/edit.png"));

        // Remove borders, background for flat icon look
        Btn_Delete->setStyleSheet(
            "QPushButton {background-color: transparent; border: none;} "
            "QPushButton:hover {border: 1.5px solid #e30a17; border-radius: "
            "4px;}");
        Btn_Edit->setStyleSheet(
            "QPushButton {background-color: transparent; border: none;} "
            "QPushButton:hover {border: 1.5px solid #0096C7; border-radius: "
            "4px;}");

        Btn_Delete->setCursor(Qt::PointingHandCursor);
        Btn_Edit->setCursor(Qt::PointingHandCursor);

        // Create a widget to hold both buttons
        QWidget     *ActionCellWidget = new QWidget();
        QHBoxLayout *Layout           = new QHBoxLayout(ActionCellWidget);
        Layout->setContentsMargins(0, 0, 0, 0); // No padding inside the cell
        Layout->setSpacing(10);                 // Space between icons
        Layout->addWidget(Btn_Edit);
        Layout->addWidget(Btn_Delete);
        Layout->setAlignment(Qt::AlignCenter);

        // Set the widget to the last column
        Table->setCellWidget(Row, ColumnCount - 1, ActionCellWidget);

        // Optionally fix the width of the action column
        Table->setColumnWidth(ColumnCount - 1, 120);
    }
}

void dashboard::SetupUI() {

    // painting the table
    ui->ProductPageTableWidget->setItemDelegate(
        new CustomTableDelegate(ui->ProductPageTableWidget));
    ui->ProductPageTableWidget->setShowGrid(false);
    ui->ProductPageTableWidget->setSelectionMode(
        QAbstractItemView::SingleSelection);
    ui->ProductPageTableWidget->setSelectionBehavior(
        QAbstractItemView::SelectRows);

    // Distribute columns based on content size
    // ui->XPageTableWidget->horizontalHeader()->setSectionResizeMode(
    //     QHeaderView::Stretch);

    // left-align header text, vertically centered
    ui->ProductPageTableWidget->horizontalHeader()->setDefaultAlignment(
        Qt::AlignLeft | Qt::AlignVCenter);

    // showing how many records are being shown out of total records
    ui->NumberOfRecordsShownLabel->setText("Showing 1-10 of 100");
    ui->NumberOfRecordsShownLabel->setStyleSheet("color: #1F1F1F;");

    ui->ProductPageTableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    ui->ProductPageTableWidget->horizontalHeader()->setSectionResizeMode(
        4, QHeaderView::Fixed);
    // ui->ProductPageTableWidget->horizontalHeader()->setSectionResizeMode(
    //     0, QHeaderView::Stretch);
    // ui->ProductPageTableWidget->horizontalHeader()->setSectionResizeMode(
    //     1, QHeaderView::ResizeToContents);

    // Setting table height according to row height
    int RowHeight =
        ui->ProductPageTableWidget->verticalHeader()->defaultSectionSize();
    int TotalHeight = ui->ProductPageTableWidget->rowCount() * RowHeight +
                      ui->ProductPageTableWidget->horizontalHeader()->height();
    ui->ProductPageTableWidget->setMaximumHeight(TotalHeight);

    // Adding svg to Side bar label
    // QSvgRenderer SvgRenderer(QString(":/images/logo-color.svg"));
    // QPixmap      Pixmap(64, 64);
    // Pixmap.fill(Qt::transparent);
    // QPainter Painter(&Pixmap);
    // SvgRenderer.render(&Painter);
    // ui->SideBarLogoLabel->setPixmap(Pixmap);

    ui->MainDisplayStackedWidget->setCurrentIndex(0);

    AddDeleteAndEditButtonsToTableRows(ui->ProductPageTableWidget);
}

void dashboard::FillTableWithData(
    /*Some Data Structure holding the query result*/) {
    /*Perform appropriate operation to fill table with data*/

    // loop over the data structure
    // insert row
    // Make a new item for each column value for a specific row
    // set ~Qt::IsItemEditable flag
    // Set the item to the table cell
}

