#include "topwordslist.h"

TopWordsList::TopWordsList(QObject *parent) : QObject(parent)
{
    topMin = -1;
}

bool topWordItemLessThan(const TopWordItem &v1, const TopWordItem &v2)
{
     return v1.word < v2.word;
}

QList<TopWordItem> TopWordsList::topItems() const
{
    QList<TopWordItem> topList;
    foreach(WordItem w, mTopItems)
    {
        topList.append(TopWordItem({w.word, static_cast<float>(w.count) / static_cast<float>(mTopItems.at(0).count)}));
    }
    qSort(topList.begin(),topList.end(),topWordItemLessThan);
    return topList;
}

void TopWordsList::appendItem(const QString &word)
{
    mItems.insert(word,mItems.value(word,0)+1);
    if(mItems.value(word,0) > topMin)
        updateTop(WordItem({word,mItems.value(word)}));
}

bool wordItemMoreThan(const WordItem &v1, const WordItem &v2)
{
     return v1.count > v2.count;
}

void TopWordsList::updateTop(const WordItem &item)
{
    int pos = mTopItems.indexOf(item);
    if( pos != -1)
        mTopItems.removeAt(pos);
    mTopItems.append(item);
    qSort(mTopItems.begin(),mTopItems.end(),wordItemMoreThan);
    mTopItems = mTopItems.mid(0,15);
    emit topChanged();
}
