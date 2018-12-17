#ifndef PARAMSAVER_H
#define PARAMSAVER_H

#include <QObject>
#include <QAbstractTableModel>
#include <QSettings>

class ParamSaver : public QObject
{
    Q_OBJECT
public:
    explicit ParamSaver(QObject *parent = 0);
    void load(QAbstractTableModel *model,const QString &section = QString());
    void save(const QAbstractTableModel *model,const QString &section = QString());
    static QVariant load(const QString &section,const QString &parameter,const QVariant &def);
    static void save(const QString &section,const QString &parameter,const QVariant &value);
};

#endif // PARAMSAVER_H
