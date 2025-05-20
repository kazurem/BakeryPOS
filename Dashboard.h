#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QTableWidget>

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
  void SetupUI();
  void ApplyFiltersForProducts(const QString &sortColumn,
                               const QString &sortOrder);
  void ApplyFiltersForUsers(const QString &SortColumn,
                            const QString &SortOrder);
  void ApplyFiltersForProducts();
  void ApplyFiltersForUsers();
  void UpdateProductRecordCountLabel();
  void UpdateUserRecordCountLabel();

private slots:
  void onEditButtonClicked();
  void on_FilterCategoryComboBox_currentIndexChanged();
  void on_SearchProductByNameLineEdit_returnPressed();
  void OnProductHeaderSectionClicked(int LogicalIndex);
  void OnUserHeaderSectionClicked(int LogicalIndex);

  void on_EditProductButton_clicked();

  void on_DeleteProductButton_clicked();

  void on_AddProductButton_clicked();

  void on_FilterRoleComboBox_currentIndexChanged();

  void on_UsersButton_clicked();

  void on_ProductsButton_clicked();

  void on_SearchUserByNameLineEdit_returnPressed();

  void on_CategoriesButton_clicked();

  void on_LogoutButton_clicked();

private:
  Ui::dashboard  *ui;
  QString         BaseQuery;
  QSqlQueryModel *Model;
  QString         CurrentCategoryFilter;
  QString         CurrentSearchFilter;
  QSqlDatabase    db;
};
#endif // DASHBOARD_H
