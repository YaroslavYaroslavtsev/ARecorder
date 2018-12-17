#ifndef SETUPKOEF_H
#define SETUPKOEF_H

#include <QDialog>
#include <QAbstractTableModel>

namespace Ui {
class SetupKoefDialog;
}

class SetupKoefDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupKoefDialog(QAbstractTableModel *model,QWidget *parent = 0);
    ~SetupKoefDialog();

private slots:
    void on_bt_keyb_clicked();

private:
    Ui::SetupKoefDialog *ui;
};

#endif // SETUPKOEF_H
