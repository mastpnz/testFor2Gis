#pragma once

#include <QObject>
#include <QVector>
#include <QMap>

struct TopWordItem {
    QString word;
    float percent;
};

struct WordItem {
    QString word;
    int count;

public:
    bool operator==(const WordItem& a) const {
      return this->word.toLower() == a.word.toLower();
    }
    bool operator!=(const WordItem& a) const {
      return !operator==(a);
    }
};

class TopWordsList : public QObject
{
    Q_OBJECT
public:
    explicit TopWordsList(QObject *parent = nullptr);

    QList<TopWordItem> topItems() const;
    void appendItem(const QString &word);
    void updateTop(const WordItem &item);

    int topMin;

signals:
    void topChanged();

private:
    QMap<QString,int> mItems;
    QList<WordItem> mTopItems;
};

