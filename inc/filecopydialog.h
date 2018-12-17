#ifndef FILECOPYDIALOG_H
#define FILECOPYDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDirModel>
#include <QSortFilterProxyModel>
#include <QMessageBox>

namespace Ui {
class FileCopyDialog;
}

class FileCopyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileCopyDialog(QWidget *parent = 0);
    ~FileCopyDialog();

public slots:
    void sl_update(void);
    void sl_copy(void);
    void sl_delete(void);
    void sl_csv(void);
    void sl_alf(void);
    void sl_diskChanged(QModelIndex);
    void sl_content(void);
    void sl_contentFilter(void);

private:
    Ui::FileCopyDialog *ui;
    QFileSystemModel *dir;
    QFileSystemModel *disk;
    QStringList alffiles;
    QStringList csvfiles;
    QStringList alfcfgfiles;
    QMessageBox *msgBox;

    void setHideAddPanel(bool);
    bool isVisibleAddPanel();
};

#endif // FILECOPYDIALOG_H
