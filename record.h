#ifndef RECORD_H
#define RECORD_H

#include <QString>

class Record
{ 
public:
    explicit Record(const QString& name, const QString& time);

public:
    QString getName() const { return m_name; }
    QString getTime() const { return m_time; }

private:
    QString m_name;
    QString m_time;

signals:
};

#endif // RECORD_H
