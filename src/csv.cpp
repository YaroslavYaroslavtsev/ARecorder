#include "csv.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QDir>

CSV::CSV(QObject *parent) : QObject(parent),
    koefs({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    enables({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
{
}

int CSV::convert(const QString &path)
{
    float value;
    double freq;
    double time,timestamp=0;
    int channels;
    int i,n=0,fnum=0;
    long fsize;
    int lastpercent = 0;
    QString txt;
    if(!QDir("Excel").exists()) {
        if(!QDir().mkdir("Excel"))
            return CSV_NODIR;
    }
    if(!QDir("Records").exists()) {
        if(!QDir().mkdir("Records"))
            return CSV_NODIR;
    }

    QFile alf(path);
    QString efile = QFileInfo(path).fileName();
    QFile csv("./Excel/"+ efile.left(efile.length() - 3) + "csv");
    if(!alf.exists())
        return CSV_NOFILE;
    bool op = alf.open(QFile::ReadOnly);
    if(!op)
        return CSV_OPEN;
    op = csv.open(QFile::WriteOnly);
    if(!op)
        return CSV_OPEN;
    QDataStream dt(&alf);
    dt.setFloatingPointPrecision(QDataStream::DoublePrecision);
    dt.setByteOrder(QDataStream::LittleEndian);
    // skip ALF HEADER
    dt.device()->seek(0x44);
    dt >> channels;
    dt >> freq;
    time = 1 / freq;
    fsize = (dt.device()->bytesAvailable() - 0x74) / 4;
    dt.device()->seek(0x74);
    dt.setFloatingPointPrecision(QDataStream::SinglePrecision);
    QTextStream cnv(&csv);
    QLocale locale("ru_RU");
    cnv << trUtf8("Время;");
    for(i = 0; i < channels; i++)
        cnv << names[i] << ";";
    cnv << "\n";
    while(!dt.atEnd())
    {
        // new csv line
        if(n >= channels) {
           timestamp += time;
           n = 0;
           cnv << "\n";
        }
        // timestamp
        if(n==0)
            cnv << locale.toString(timestamp,'f',5) << ";";
        // value
        dt >> value;
        if(value < -10.0)
            break;
        if(enables[n]) {
           value -= offsets[n];
           value *= koefs[n];
           txt = locale.toString(value,'f',3) + ";";
           cnv << txt;
        } else {
           cnv << ";";
        }
        n++;
        fnum++;
        if(fnum * 100 / fsize != lastpercent) {
           lastpercent = fnum * 100 / fsize;
           emit progressChanged(lastpercent);
        }
    }
    alf.close();
    csv.close();
    return CSV_OK;
}

void CSV::setName(const QString &name, int col)
{
    if(col<1 || col >32) return;
    names[col - 1] = name;
}

QString CSV::name(int col)
{
    if(col < 1 || col > 32) return "#Error";
    return names[col - 1];
}

void CSV::setKoef(float koef, int col)
{
    if(col < 1 || col > 32) return;
    koefs[col - 1] = koef;
}

float CSV::koef(int col)
{
    if(col < 1 || col > 32)
        return 1;
    return koefs[col - 1];
}

void CSV::setOffs(float off, int col)
{
    if(col < 1 || col > 32)
        return;
    offsets[col - 1] = off;
}

float CSV::offs(int col)
{
    if(col < 1 || col > 32)
        return 1;
    return offsets[col - 1];
}

void CSV::setEnable(bool en, int col)
{
    if(col < 1 || col > 32)
        return;
    enables[col - 1] = en;
}

bool CSV::isEnable(int col)
{
    if(col < 1 || col > 32)
        return false;
    return enables[col - 1];
}
