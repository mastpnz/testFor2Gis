#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "topwordslist.h"
#include "topwordsmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    TopWordsList topWordList;
    qmlRegisterType<TopWordsModel>("TopWordsModel", 1, 0, "TopWordsModel");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("topWordList"), &topWordList);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
