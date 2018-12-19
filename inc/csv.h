#ifndef CSV_H
#define CSV_H

#include <QObject>

#define CSV_OK 0
#define CSV_NOFILE -1
#define CSV_OPEN -2
#define CSV_NODIR -3

class CSV : public QObject
{
    Q_OBJECT
public:
    explicit CSV(QObject *parent = 0);
    int convert(const QString&);
    void setName(const QString&, int);
    QString name(int);
    void setKoef(float, int);
    float koef(int);
    void setOffs(float, int);
    float offs(int);
    void setEnable(bool, int);
    bool isEnable(int);

signals:
    void progressChanged(int);

private:
    float koefs[32];
    float offsets[32];
    QString  names[32];
    bool enables[32];
};

#endif // CSV_H
