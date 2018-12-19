#include "setupkoefdialog.h"
#include "ui_setupkoefdialog.h"
#include <QMessageBox>
#include <QProcess>

SetupKoefDialog::SetupKoefDialog(QAbstractTableModel *model,QWidget *parent) :
    QDialog(parent), ui(new Ui::SetupKoefDialog)
{
     ui->setupUi(this);
     ui->tableView->setModel(model);
     ui->tableView->horizontalHeader()->setStretchLastSection(true);
     ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
     connect(ui->bt_ok, SIGNAL(clicked()), model,SLOT(submit()));
}

SetupKoefDialog::~SetupKoefDialog()
{
    delete ui;
}

void SetupKoefDialog::on_bt_keyb_clicked()
{
    QProcess::startDetached("osk.exe");
}
