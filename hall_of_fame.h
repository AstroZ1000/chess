#ifndef HALL_OF_FAME_H
#define HALL_OF_FAME_H

#include <QObject>
#include "hall_of_fame.h"
#include "record.h"
#include <vector>

class HallOfFame : public QObject
{
    Q_OBJECT

public:
    explicit HallOfFame(QObject *parent = nullptr);
    ~HallOfFame();

    QString addEntry(QString& player);

signals:

private:
    QString printHallOfFame();
    void writeToFile();
    void readRecords();

private:
    std::vector<Record> m_records;
    QString m_jsonFilename;

};

#endif // HALL_OF_FAME_H
