#pragma once

#include <QThread>

class ThreadReadFile : public QThread
{
    Q_OBJECT
public:
    void setFilePath(const QString &filepath);
    QString mFilePath;
protected:
    void run();
private:
    int mFileSize;
    int totalWorked;

signals:
    void percentDone(const int percent);
    void wordFinded(const QString word);
};

