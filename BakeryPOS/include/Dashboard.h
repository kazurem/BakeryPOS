#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class dashboard;
}
QT_END_NAMESPACE

class dashboard : public QMainWindow {
    Q_OBJECT

  public:
    dashboard(QWidget *parent = nullptr);
    ~dashboard();

  private slots:
    void on_FilterCategoryComboBox_currentIndexChanged();
    void on_SearchProductByNameLineEdit_returnPressed();
    void on_EditProductButton_clicked();
    void on_DeleteProductButton_clicked();
    void on_AddProductButton_clicked();
    void on_FilterRoleComboBox_currentIndexChanged();
    void on_UsersButton_clicked();
    void on_ProductsButton_clicked();
    void on_SearchUserByNameLineEdit_returnPressed();
    void on_CategoriesButton_clicked();
    void on_LogoutButton_clicked();

    void OnProductHeaderSectionClicked(int LogicalIndex);
    void OnUserHeaderSectionClicked(int LogicalIndex);
    void refreshProductData(); // Add this slot

  private:
    Ui::dashboard  *ui;
    QSqlQueryModel *Model;
    QString         BaseQuery;
    QString         CurrentCategoryFilter;
    QString         CurrentSearchFilter;

    void SetupUI();
    void ApplyFiltersForProducts(const QString &SortColumn,
                                 const QString &SortOrder);
    void ApplyFiltersForUsers(const QString &SortColumn,
                              const QString &SortOrder);
    void ApplyFiltersForProducts();
    void ApplyFiltersForUsers();
    void UpdateProductRecordCountLabel();
    void UpdateUserRecordCountLabel();
};

#endif // DASHBOARD_H
