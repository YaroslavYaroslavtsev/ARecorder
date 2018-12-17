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
    void setName(const QString &name, int col);
    QString name(int col);
    void setKoef(float koef, int col);
    float koef(int col);
    void setOffs(float off, int col);
    float offs(int col);
    void setEnable(bool en, int col);
    bool isEnable(int col);

signals:
    void progressChanged(int);

private:
    float koefs[32];
    float offsets[32];
    QString  names[32];
    bool enables[32];
};

#endif // CSV_H
