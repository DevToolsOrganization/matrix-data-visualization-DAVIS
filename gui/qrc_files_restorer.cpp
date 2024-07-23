#include "qrc_files_restorer.h"
#include <QFile>
#include <QDir>
#include <QString>

QrcFilesRestorer::QrcFilesRestorer(const QString& path2Qrc) {
  QDir dir(path2Qrc);
  QStringList files = dir.entryList();
}

void QrcFilesRestorer::restoreFilesFromQrc(const QString& path2Qrc) {
  QDir dir(path2Qrc);
  QStringList files = dir.entryList();
  for (int i = 0; i < files.count(); ++i) {
    QString filenameNew = QDir::currentPath() + "/" + files.at(i);
    QFile file(filenameNew);
    if (!file.exists()) {
      QFile::copy(path2Qrc + "/" + files.at(i), filenameNew);
      file.setPermissions(QFileDevice::WriteUser | QFileDevice::ReadUser);
    }
  }
}


