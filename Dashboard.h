#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>

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

  private slots:
    void on_AddXButton_clicked();

  private:
    Ui::dashboard *ui;
};
#endif // DASHBOARD_H
