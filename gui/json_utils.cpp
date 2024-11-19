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
                                                              QJsonObject& object,
                                                              const QJsonArray& service_keys,
                                                              const QJsonArray& user_keys) {

  QJsonObject obj;
  if (getJsonObjectFromFile(path, obj) == false) {
    return {false, QJsonObject()};
  };
  QStringList keys = obj.keys();
  qDebug() << "obj keys: " << obj.keys();

  // Check that all user keys are valid
  for (int i = 0; i < service_keys.size(); ++i) {
    for (int j = 0; j < user_keys.size(); ++j) {
      QStringList user_keys_list = user_keys[j].toObject().keys();
      if (user_keys_list[j].contains(service_keys[j].toString()) == false) {
        qDebug() << "invalid user key in json.....";
        return {false, QJsonObject()};
      }
    }
  }

  // Check that we have stamp for user json
  QJsonObject stamp;
  for (int i = 0; i < user_keys.size(); ++i) {
    QStringList user_keys_list = user_keys[i].toObject().keys();
    if (user_keys_list.size() != keys.size())
      continue;
    bool result = true;
    for (int j = 0; j < user_keys_list.size(); ++j) {
      qDebug() << user_keys_list[j] << keys[i];
      if (user_keys_list[j].contains(keys[i]) == false) {
        result = false;
        break;
      }
    }
    if (result) {
      qDebug() << "OK ---- JSON POSITIVE RESULT";
      object = obj;
      return {true, user_keys[i].toObject()};
    }
  }
  return {false, QJsonObject()};
}

} // end jsn namespace
