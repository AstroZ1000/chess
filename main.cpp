#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QMLBridge.h"
#include "GameLogic.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Chess/Main.qml"_qs);

    QMLBridge backEnd;
    std::unique_ptr<GameLogic> gameLogic = std::make_unique<GameLogic>(backEnd);

    // Expose the C++ object to QML
    engine.rootContext()->setContextProperty("QMLBridge", &backEnd);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
