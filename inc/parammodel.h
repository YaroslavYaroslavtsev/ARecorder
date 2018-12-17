#ifndef PARAMMODEL_H
#define PARAMMODEL_H

#include <QAbstractTableModel>
#include <QColor>
#include "adc.h"

#define PARAM_ENABLE    0
#define PARAM_NAME      1
#define PARAM_KOEF      2
#define PARAM_OFFSET    3
#define PARAM_ALPHA     4
#define PARAMS          5

class ParamModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ParamModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

public slots:
    bool submit();

private:
    bool enable[ADC_CHANNEL_COUNT];
    QString name[ADC_CHANNEL_COUNT];
    double koef[ADC_CHANNEL_COUNT];
    double offs[ADC_CHANNEL_COUNT];
    QColor color[ADC_CHANNEL_COUNT];
    double alpha[ADC_CHANNEL_COUNT];
};

#endif // PARAMMODEL_H
