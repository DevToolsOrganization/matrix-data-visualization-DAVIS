#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "QVector"
#include "QJsonDocument"

class QString;
class QJsonArray;
class QJsonObject;


namespace jsn {


bool getJsonObjectFromFile(const QString& path,
                           QJsonObject& object);

bool getJsonArrayFromFile(const QString& path,
                          QJsonArray& object);


bool saveJsonObjectToFile(const QString& path,
                          const QJsonObject& json_object,
                          QJsonDocument::JsonFormat format);

bool saveJsonArrayToFile(const QString& path,
                         const QJsonArray& json_object,
                         QJsonDocument::JsonFormat format);

} // end namespace jsn

#endif // JSON_UTILS_H
