#include "topwordsmodel.h"
#include "topwordslist.h"

TopWordsModel::TopWordsModel(QObject *parent)
    : QAbstractListModel(parent),
      mList(nullptr)
{
    mList = new TopWordsList();
    m_threadReadFile = new ThreadReadFile();
    connect(m_threadReadFile,SIGNAL(wordFinded(QString)),this,SLOT(addWord(QString)),Qt::BlockingQueuedConnection);
    connect(mList,SIGNAL(topChanged()),this,SLOT(updateHisto()));
    connect(m_threadReadFile,SIGNAL(percentDone(int)),this,SLOT(getPercent(int)));
    connect(m_threadReadFile,SIGNAL(finished()),this,SLOT(workDone()));
}

TopWordsModel::~TopWordsModel()
{
    if(mList)
        delete(mList);
}

int TopWordsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
        return 0;

    return mList->topItems().size()>=15 ? 15 : mList->topItems().size();
}

QVariant TopWordsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    TopWordItem tpItem = mList->topItems().at(index.row());

    switch (role) {
    case WordRole:
        return QVariant(tpItem.word);
    case PercentRole:
        return QVariant(tpItem.percent);
    }
    return QVariant();
}

QHash<int, QByteArray> TopWordsModel::roleNames() const
{
    QHash<int,QByteArray> names;
    names[WordRole] = "word";
    names[PercentRole] = "percent";
    return names;
}

TopWordsList *TopWordsModel::twList() const
{
    if(mList)
        return mList;
}

void TopWordsModel::setTwList(TopWordsList *newList)
{
    beginResetModel();
    if(mList)
        mList->disconnect(this);

    mList = newList;

    endResetModel();
}

void TopWordsModel::startWithFilePath(const QString &filepath)
{
    m_threadReadFile->setFilePath(filepath);
    m_threadReadFile->start();
}

void TopWordsModel::addWord(const QString &word)
{
    beginResetModel();
    mList->appendItem(word);
    endResetModel();
}

void TopWordsModel::updateHisto()
{
    beginResetModel();
    endResetModel();
}

void TopWordsModel::getPercent(int perc)
{
    emit this->percentDone(perc);
}

void TopWordsModel::workDone()
{
    emit workFinished();
}
