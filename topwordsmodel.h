#pragma once

#include <QAbstractListModel>
#include "threadreadfile.h"

class TopWordsList;

class TopWordsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TopWordsList *twList READ twList WRITE setTwList)
public:
    explicit TopWordsModel(QObject *parent = nullptr);
    ~TopWordsModel();
    enum {
        WordRole = Qt::UserRole +1,
        PercentRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    TopWordsList *twList() const;
    void setTwList(TopWordsList *newList);
    ThreadReadFile *m_threadReadFile;

    Q_INVOKABLE void startWithFilePath(const QString &filepath);
signals:
    void percentDone(int percent);
    void workFinished();

private:
    TopWordsList *mList;

public slots:
    void addWord(const QString &word);
    void getPercent(int perc);
    void workDone();
    void updateHisto();
};

