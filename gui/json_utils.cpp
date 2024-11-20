#include "json_utils.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFile>
#include <QDebug>
#include <QGuiApplication>
#include <QDir>


namespace jsn {

bool getJsonObjectFromFile(const QString& path,
                           QJsonObject& object) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "File can't be opened!" << path;
    return false;
  };
  QByteArray data = file.readAll();
  QJsonParseError errorPtr;
  object = QJsonDocument::fromJson(data, &errorPtr).object();
  if (object.isEmpty()) {
    qDebug() << "JSON IS EMPTY: " << errorPtr.errorString();
    return false;
  }
  file.close();

  return true;
}

bool getJsonArrayFromFile(const QString& path,
                          QJsonArray& object) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "File can't be opened!" << path;
    return false;
  };
  QByteArray data = file.readAll();
  QJsonParseError errorPtr;
  object = QJsonDocument::fromJson(data, &errorPtr).array();
  if (object.isEmpty()) {
    qDebug() << "JSON IS EMPTY: " << errorPtr.errorString();
    return false;
  }
  file.close();
  return true;
}

bool saveJsonObjectToFile(const QString& path,
                          const QJsonObject& json_object,
                          QJsonDocument::JsonFormat format) {
  QFile file(path);
  if (!file.open(QIODevice::WriteOnly))
    return false;
  auto json_doc = QJsonDocument(json_object).toJson(format);
  auto result = file.write(json_doc);
  file.close();
  if (result == -1)
    return false;
  else
    return true;
}

bool saveJsonArrayToFile(const QString& path,
                         const QJsonArray& json_object,
                         QJsonDocument::JsonFormat format) {
  QFile file(path);
  if (!file.open(QIODevice::WriteOnly))
    return false;
  auto json_doc = QJsonDocument(json_object).toJson(format);
  auto result = file.write(json_doc);
  file.close();
  if (result == -1)
    return false;
  else
    return true;
}

QPair<bool, QJsonObject> getJsonObjectFromFileIfUserKeysExist(const QString& path,
                                                              const QJsonArray& service_keys,
                                                              const QJsonObject& user_stamp_keys) {

  QJsonObject result_object_with_data;
  QJsonObject user_json_from_file;
  if (getJsonObjectFromFile(path, user_json_from_file) == false) {
    qDebug()<<"Open User json object with data error...";
    return {false, QJsonObject()};
  };
  QStringList user_file_keys_list = user_json_from_file.keys();
  QStringList user_stamp_keys_list = user_stamp_keys.keys();

  // Check that all user stamp keys are valid
  for (int i = 0; i < user_stamp_keys_list.size(); ++i) {
      QString check_key = user_stamp_keys_list[i];
      if(service_keys.contains(QJsonValue(check_key))==false){
          qDebug()<<"invalid key in the user stamps json"<<check_key;
          return {false,QJsonObject()};
      }
  }

  // Check that we have keys for user json
  for(int i=0;i<service_keys.size();++i){
      auto jarr_custom_keys = user_stamp_keys[service_keys[i].toString()].toArray();
      for(int j=0;j<jarr_custom_keys.size();++j){
          auto custom_key = jarr_custom_keys[j].toString();
          if(user_json_from_file.contains(custom_key)){
             if(user_json_from_file[custom_key].isArray()){
             result_object_with_data.insert(service_keys[i].toString(),
                                            user_json_from_file[custom_key]);
             break;
             }
          }
      };
  }
  if(result_object_with_data.isEmpty()){
      return {false, result_object_with_data};
  }else
      return {true, result_object_with_data};
}

QVector<double> getVectorDoubleFromJsonArray(const QJsonArray& json_array)
{
    QVector<double> vector;
        for (const QJsonValue &value : json_array) {
            if (value.isDouble()) {
                vector.append(value.toDouble());
            }
        }
        return vector;
}

std::vector<std::vector<double> > getMatrixFromJsonArray(const QJsonArray& json_array)
{
    std::vector<std::vector<double>> matrix;

        for (const QJsonValue& rowValue : json_array) {
            if (rowValue.isArray()) {
                QJsonArray rowArray = rowValue.toArray();
                std::vector<double> row;

                for (const QJsonValue& value : qAsConst(rowArray)) {
                    if (value.isDouble()) {
                        row.emplace_back(value.toDouble());
                    }
                }

                matrix.emplace_back(row);
            }
        }

        return matrix;
}



} // end jsn namespace
