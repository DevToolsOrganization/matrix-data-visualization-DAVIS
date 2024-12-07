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


bool getJsonValueFromFile(const QString& path,
                          QJsonValue& jsonValue);


bool saveJsonObjectToFile(const QString& path,
                          const QJsonObject& json_object,
                          QJsonDocument::JsonFormat format = QJsonDocument::Indented);

bool saveJsonArrayToFile(const QString& path,
                         const QJsonArray& json_object,
                         QJsonDocument::JsonFormat format = QJsonDocument::Indented);

QPair<bool, QJsonObject> isJsonObjectContainsUserKeys(const QJsonObject& path,
                                                      const QJsonArray& service_keys,
                                                      const QJsonObject& user_stamp_keys
                                                     );

QVector<double> getVectorDoubleFromJsonArray(const QJsonArray& json_array);

std::vector<std::vector<double> > getMatrixFromJsonArray(const QJsonArray& json_array);


QJsonValue getValueByPath(const QJsonValue& obj,
                          const QStringList& path);


QVector<QStringList> getStringListFromJsonArray(const QJsonArray& array);


void extractAllObjects(const QJsonValue& value, QJsonArray& result);


} // end namespace jsn

#endif // JSON_UTILS_H
