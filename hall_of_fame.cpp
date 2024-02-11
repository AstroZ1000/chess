#include "hall_of_fame.h"
#include "record.h"
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>>
#include <QFile>

HallOfFame::HallOfFame(QObject *parent)
    : QObject{parent}
    , m_jsonFilename("hall_of_fame.json")
{
    readRecords();
}

HallOfFame::~HallOfFame()
{
    writeToFile();
    m_records.clear();
}

QString HallOfFame::addEntry(QString& player)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    Record record(player, currentDateTime.toString());
    m_records.push_back(record);

    QString text = "Congratulations " + player + "!!!! Want to play again?";
    text += "\n\n\n";
    text += printHallOfFame();

    return text;
}

QString HallOfFame::printHallOfFame()
{
    QString text = "****************************** Hall of Fame ******************************";
    text += "\n";
    text += "\n";
    text += "\n";

    int counter = 1;
    for (const auto& record : m_records)
    {
        text+= QString::number(counter++);
        text+= ". ";
        text+= record.getTime();
        text+= ". . . . . . . . . .";
        text+= record.getName();
        text+= "\n";
    }

    return text;
}

void HallOfFame::readRecords()
{
    QFile file(m_jsonFilename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading!";
    }
    else
    {
        QByteArray jsonData = file.readAll();
        file.close();

        QJsonParseError error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData, &error);

        if (error.error != QJsonParseError::NoError)
        {
            qDebug() << "JSON parsing error:" << error.errorString();
        }

        QJsonArray jsonArray = jsonDocument.array();
        for (const auto& jsonValue : jsonArray) {
            if (jsonValue.isObject()) {
                QJsonObject jsonObject = jsonValue.toObject();

                Record record(jsonObject.value("name").toString(), jsonObject.value("time").toString());
                m_records.push_back(record);
            }
        }
    }
}

void HallOfFame::writeToFile()
{
    QFile file(m_jsonFilename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for writing!";
    }
    else
    {
        QJsonArray jsonArray;

        for (const auto& record : m_records)
        {
            QJsonObject jsonObject;
            jsonObject["name"] = record.getName();
            jsonObject["time"] = record.getTime();

            jsonArray.append(jsonObject);
        }

        QJsonDocument jsonDocument(jsonArray);
        QByteArray jsonData = jsonDocument.toJson();

        qint64 bytesWritten = file.write(jsonData);
        if (bytesWritten == -1)
        {
            qDebug() << "Failed to write JSON data to file";
        }

        file.close();
    }
}
