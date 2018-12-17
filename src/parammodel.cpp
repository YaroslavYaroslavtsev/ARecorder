#include "parammodel.h"

ParamModel::ParamModel(QObject *parent)
{
    Q_UNUSED(parent);
    for (int i = 0; i < ADC_CHANNEL_COUNT; i++) {
        enable[i] = true;
        name[i] = QString("Channel %1").arg(i + 1) ;
        koef[i] = 1.0;
        offs[i] = 0.0;
        alpha[i] = 1.0;
    }
}

bool ParamModel::submit()
{
    return true;
}

int ParamModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return ADC_CHANNEL_COUNT;
}

int ParamModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return PARAMS;
}

QVariant ParamModel::data(const QModelIndex &index, int role) const
{
    // incorrect column or row
    if (index.column() > (PARAMS - 1) || index.row() >= ADC_CHANNEL_COUNT)
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QString unswer;
        switch (index.column()) {
            case 0:
                unswer = enable[index.row()] ? trUtf8("Включен") : trUtf8("Отключен");
                break;
            case 1:
                unswer = name[index.row()];
                break;
            case 2:
                unswer = QString::number(koef[index.row()], 'f', 3);
                break;
            case 3:
                unswer = QString::number(offs[index.row()], 'f', 3);
                break;
            case 4:
                unswer = QString::number(alpha[index.row()], 'f', 6);
                break;
            case 5:
                QVariant col = QVariant(color[index.row()]);
                return col;
                break;
        }
        return QVariant(unswer);
    }

    if (role == Qt::CheckStateRole && index.column() == 0)
        return QVariant(enable[index.row()]? Qt::Checked:Qt::Unchecked);
    return QVariant();
}

Qt::ItemFlags ParamModel::flags(const QModelIndex &index) const
{
    if (index.column() == 0)
        return Qt::ItemIsEditable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable;
    return Qt::ItemIsEditable|Qt::ItemIsEnabled;
}

QVariant ParamModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return QVariant(trUtf8("Состояние"));
                break;
            case 1:
                return QVariant(trUtf8("Имя канала"));
                break;
            case 2:
                return QVariant(trUtf8("Коэффициент"));
                break;
            case 3:
                return QVariant(trUtf8("Смещение,V"));
                break;
            case 5:
                return QVariant(trUtf8("Цвет графика"));
                break;
            case 4:
                return QVariant(trUtf8("Коэффициент сглаживния"));
                break;
            default:
                return QVariant();
                break;
            }
        }
    if (orientation == Qt::Vertical) {
        if (section >= ADC_CHANNEL_COUNT)
            return QVariant();
        return QVariant(QString(trUtf8("Канал %1")).arg(section+1));
    }
    return QVariant();
}

bool ParamModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    bool res;
    double val;
    if (index.column() < 0 || index.column() > (PARAMS - 1))
        return false;
    if (index.row() < 0 || index.row() >= ADC_CHANNEL_COUNT)
        return false;
    switch (index.column()) {
        case 0:
            switch(value.type()) {
                case QVariant::Bool :
                case QVariant::Int :
                    enable[index.row()] = value.toBool();
                    break;
                default:
                    enable[index.row()] = (value.toString() == trUtf8("Включен"));
                break;
            }
            break;
        case 1:
            name[index.row()] = value.toString();
            break;
        case 2:
            val = value.toDouble(&res);
            if (res)
                koef[index.row()] = val;
            break;
        case 3:
            val = value.toDouble(&res);
            if (res)
                offs[index.row()] = val;
            break;
        case 5:
            color[index.row()] = value.value<QColor>();
            break;
        case 4:
            val = value.toDouble(&res);
            if (res)
                alpha[index.row()] = val;
            break;
        }
    return true;
}
