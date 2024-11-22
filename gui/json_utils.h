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

QPair<bool, QJsonObject> getJsonObjectFromFileIfUserKeysExist(const QString& path,
                                                              const QJsonArray& service_keys,
                                                              const QJsonObject& user_stamp_keys
                                                             );

QVector<double> getVectorDoubleFromJsonArray(const QJsonArray& json_array);

std::vector<std::vector<double> > getMatrixFromJsonArray(const QJsonArray& json_array);

} // end namespace jsn

#endif // JSON_UTILS_H
