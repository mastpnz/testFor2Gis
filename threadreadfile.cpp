#include "threadreadfile.h"
#include <QThread>
#include <QFile>
#include <QTextStream>

void ThreadReadFile::setFilePath(const QString &filepath)
{
    mFilePath = filepath;
}

void ThreadReadFile::run()
{
    if (mFilePath.length() > 0){
        QFile file(mFilePath);
        if(!file.open(QIODevice::ReadOnly)) {
            return;
        }
        mFileSize = file.size();
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList words = line.split(' ');
            totalWorked+=words.removeAll(QString(""));
            foreach(QString qStr, words)
            {
                emit wordFinded(qStr);
                totalWorked+=sizeof(qStr.toStdString().data());
                qStr.trimmed();
                emit percentDone( totalWorked*100 / mFileSize );
            }
        }
        file.close();
      }
}
