#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class dashboard;
}
QT_END_NAMESPACE

class dashboard : public QMainWindow
{
    Q_OBJECT

public:
    dashboard(QWidget *parent = nullptr);
    ~dashboard();
    void SetupUI();
    void FillTableWithData(/*Some data structure holding the query result*/);
    void AddDeleteAndEditButtonsToTableRows(QTableWidget *Table);

  private slots:

  private:
    Ui::dashboard *ui;
};
#endif // DASHBOARD_H
