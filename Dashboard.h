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
  void ApplyFilters(const QString &sortColumn, const QString &sortOrder);
  void ApplyFilters();
  void UpdateRecordCountLabel();

private slots:
  void onEditButtonClicked();
  void on_FilterCategoryComboBox_currentIndexChanged();
  void on_SearchProductByNameLineEdit_returnPressed();
  void OnHeaderSectionClicked(int LogicalIndex);

  void on_EditProductButton_clicked();

  void on_DeleteProductButton_clicked();

  void on_AddProductButton_clicked();

private:
  Ui::dashboard  *ui;
  QString         BaseQuery;
  QSqlQueryModel *Model;
  QString         CurrentCategoryFilter;
  QString         CurrentSearchFilter;
};
#endif // DASHBOARD_H
