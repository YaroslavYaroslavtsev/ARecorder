#include "paramsaver.h"

ParamSaver::ParamSaver(QObject *parent) : QObject(parent)
{
}

void ParamSaver::load(QAbstractTableModel *model,const QString &section)
{
    int rows = model->rowCount();
    int cols = model->columnCount();
    QSettings set;
    if (set.value("parameter") != QVariant(true))
        return;
    if (!section.isEmpty())
        set.beginGroup(section);
    for (int i = 0; i < rows; i++) {
        QString rowname = model->headerData(i,Qt::Vertical).isValid()? model->headerData(i,Qt::Vertical).toString():QString("Item %1").arg(i + 1);
        set.beginGroup(rowname);
        for (int j = 0; j < cols; j++) {
            QString colname = model->headerData(j,Qt::Horizontal).isValid()?model->headerData(j,Qt::Horizontal).toString():QString("Param %1").arg(i + 1);
            QModelIndex idx = model->index(i, j);
            model->setData(idx, set.value(colname));
        }
        set.endGroup();
    }
    if (!section.isEmpty())
        set.endGroup();
}

void ParamSaver::save(const QAbstractTableModel *model,const QString &section)
{
    int i,j;
    int rows = model->rowCount();
    int cols = model->columnCount();
    QSettings set;
    set.setValue("parameter", QVariant(true));
    if (!section.isEmpty())
        set.beginGroup("Каналы");
    for (i = 0; i < rows; i++) {
        QString rowname = model->headerData(i,Qt::Vertical).isValid()? model->headerData(i,Qt::Vertical).toString():QString("Item %1").arg(i+1);
        set.beginGroup(rowname);
        for (j = 0; j < cols; j++) {
            QString colname = model->headerData(j,Qt::Horizontal).isValid()?model->headerData(j,Qt::Horizontal).toString():QString("Param %1").arg(i+1);
            QModelIndex idx = model->index(i,j);
            QVariant prm(model->data(idx));
            set.setValue(colname,prm);
        }
        set.endGroup();
    }
    if (!section.isEmpty())
        set.endGroup();
}

QVariant ParamSaver::load(const QString &section, const QString &parameter,const QVariant &def)
{
    QSettings set;
    set.beginGroup(section);
    QVariant result = set.value(parameter);
    if (result.isValid())
        return result;
    else
        return def;
}

void ParamSaver::save(const QString &section, const QString &parameter,const QVariant &value)
{
    QSettings set;
    set.beginGroup(section);
    set.setValue(parameter,value);
    set.endGroup();
}
