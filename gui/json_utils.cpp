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

QPair<bool, QJsonObject> isJsonObjectContainsUserKeys(const QJsonObject& user_json_from_file,
                                                      const QJsonArray& service_keys,
                                                      const QJsonObject& user_stamp_keys) {

  if (user_json_from_file.isEmpty())
    return {false, QJsonObject()};
  QJsonObject result_object_with_data;
  QStringList user_file_keys_list = user_json_from_file.keys();
  QStringList user_stamp_keys_list = user_stamp_keys.keys();

  // Check that all user stamp keys are valid
  for (int i = 0; i < user_stamp_keys_list.size(); ++i) {
    QString check_key = user_stamp_keys_list[i];
    if (service_keys.contains(QJsonValue(check_key)) == false) {
      qDebug() << "invalid key in the user stamps json" << check_key;
      return {false, QJsonObject()};
    }
  }

  // Check that we have keys for user json
  for (int i = 0; i < service_keys.size(); ++i) {
    auto jarr_custom_keys = user_stamp_keys[service_keys[i].toString()].toArray();
    for (int j = 0; j < jarr_custom_keys.size(); ++j) {
      auto custom_key = jarr_custom_keys[j].toString();
      if (user_json_from_file.contains(custom_key)) {
        if (user_json_from_file[custom_key].isArray()) {
          result_object_with_data.insert(service_keys[i].toString(),
                                         user_json_from_file[custom_key]);
          break;
        }
      }
    };
  }
  if (result_object_with_data.isEmpty()) {
    return {false, result_object_with_data};
  } else
    return {true, result_object_with_data};
}

QVector<double> getVectorDoubleFromJsonArray(const QJsonArray& json_array) {
  QVector<double> vector;
  for (const QJsonValue& value : json_array) {
    if (value.isDouble()) {
      vector.append(value.toDouble());
    }
  }
  return vector;
}

std::vector<std::vector<double> > getMatrixFromJsonArray(const QJsonArray& json_array) {
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


bool getJsonValueFromFile(const QString& path,
                          QJsonValue& jsonValue) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "File can't be opened!" << path;
    return false;
  };
  QByteArray data = file.readAll();
  QJsonParseError errorPtr;
  auto jdoc = QJsonDocument::fromJson(data, &errorPtr);
  if (jdoc.isEmpty()) {
    qDebug() << "Json document is empty.";
    return false;
  }
  if (jdoc.isArray()) {
    jsonValue = jdoc.array();
  }
  if (jdoc.isObject()) {
    jsonValue = jdoc.object();
  }

  file.close();
  return true;
}

QJsonValue getValueByPath(const QJsonValue& obj,
                          const QStringList& path) {
  QJsonValue value = obj;
  for (const QString& key : path) {
    if (value.isObject()) {
      value = value.toObject().value(key);
    } else if (value.isArray()) {
      bool ok;
      int index = key.toInt(&ok);
      if (ok && index >= 0 && index < value.toArray().size()) {
        value = value.toArray().at(index);
      } else {
        return QJsonValue();
      }
    } else {
      return QJsonValue();
    }
  }
  return value;
}

QVector<QStringList> getStringListFromJsonArray(const QJsonArray& array) {
  QVector<QStringList> pathes;
  for (int i = 0; i < array.size(); ++i) {
    if (array[i].isArray() == false)
      continue;
    QStringList list;
    for (int j = 0; j < array[i].toArray().size(); ++j) {
      list.append(array[i].toArray()[j].toString());
    }
    pathes.push_back(list);
  }
  return pathes;
}

void extractAllObjects(const QJsonValue& value,
                       QJsonArray& result) {
  if (value.isObject()) {
    QJsonObject obj = value.toObject();
    result.append(obj);
    for (const QString& key : obj.keys()) {
      extractAllObjects(obj[key], result);
    }
  } else if (value.isArray()) {
    QJsonArray array = value.toArray();
    for (const QJsonValue& item : array) {
      extractAllObjects(item, result);
    }
  }
}

bool isObjectMatrixToMatrixType(const QStringList& keys,
                                QJsonObject& object)
{
    QStringList object_keys = object.keys();
    qDebug()<<"Проверочные Ключи: "<<keys;
    qDebug()<<"Ключи объекта"<<object_keys;
    for(int i=0;i<keys.size();++i){
        if(object_keys.contains(keys[i]))continue;
        return false;
    }
    return true;
}



} // end jsn namespace
