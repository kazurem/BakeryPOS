#include "Dashboard.h"
#include "ui_Dashboard.h"

#include <QEasingCurve>
#include <QPropertyAnimation>

#include <QPainter>
#include <QStyledItemDelegate>

#include <QPainter>
#include <QStyledItemDelegate>

#include <QPainter>
#include <QStyledItemDelegate>

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
    ui->XPageTableWidget->setColumnCount(6);
    ui->XPageTableWidget->setHorizontalHeaderLabels(
        {"Product", "Quantity", "Unit Price", "Total", "", ""});

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

        QPushButton *btn_Delete = new QPushButton();
        QPushButton *btn_Edit   = new QPushButton();
        btn_Delete->setObjectName("BTN");
        btn_Delete->setStyleSheet("background-color: white; border: none;");
        btn_Delete->setIcon(QIcon(":/icons/delete.png"));

        btn_Edit->setObjectName("BTN_1");
        btn_Edit->setStyleSheet("background-color: white; border: none;");
        btn_Edit->setIcon(QIcon(":/icons/edit.png"));
        ui->XPageTableWidget->setCellWidget(row, 4, btn_Delete);
        ui->XPageTableWidget->setCellWidget(row, 5, btn_Edit);
        ui->XPageTableWidget->setColumnWidth(4, 100);
        ui->XPageTableWidget->setColumnWidth(5, 100);
    }

    QIcon    searchIcon(":/icons/search.png");
    QAction *searchAction = new QAction(searchIcon, "", ui->SearchByXLineEdit);
    ui->SearchByXLineEdit->addAction(searchAction, QLineEdit::LeadingPosition);

    ui->XPageTableWidget->setItemDelegate(
        new CustomTableDelegate(ui->XPageTableWidget));
    ui->XPageTableWidget->setShowGrid(false);
    ui->XPageTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->XPageTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Temporary menu toggle button
    QPushButton *menu_Btn = new QPushButton();
    ui->TopBarHLayout->addWidget(menu_Btn);
    connect(menu_Btn, &QPushButton::clicked, this, ToggleSideMenu);

    // important section
    sideMenuVisible = true;
    //-----------------------------------------------------------------------------
}

dashboard::~dashboard() { delete ui; }

void dashboard::on_AddXButton_clicked() {
    ui->MainDisplayStackedWidget->setCurrentIndex(0);
}

void dashboard::ToggleSideMenu() {
    static const int sideMenuWidth = 239;
    int              startWidth    = ui->SideBarWidget->width();
    int              endWidth      = sideMenuVisible ? 0 : sideMenuWidth;

    QPropertyAnimation *animation =
        new QPropertyAnimation(ui->SideBarWidget, "minimumWidth");
    animation->setDuration(300); // 300 ms
    animation->setStartValue(startWidth);
    animation->setEndValue(endWidth);
    animation->setEasingCurve(QEasingCurve::InOutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation *animationMax =
        new QPropertyAnimation(ui->SideBarWidget, "maximumWidth");
    animationMax->setDuration(300);
    animationMax->setStartValue(startWidth);
    animationMax->setEndValue(endWidth);
    animationMax->setEasingCurve(QEasingCurve::InOutCubic);
    animationMax->start(QAbstractAnimation::DeleteWhenStopped);

    sideMenuVisible = !sideMenuVisible;
}
