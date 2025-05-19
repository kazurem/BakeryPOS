#include "login.h"
#include "ui_login.h"
#include "dashboard.h"
#include <QMessageBox>

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_checkBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal); // Show password
    } else {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password); // Hide password
    }
}

void login::on_btnLogin_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username == "khalid" && password == "1234") {
        dashboard *dash = new dashboard(this);  // Lowercase 'dashboard'
        dash->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}



