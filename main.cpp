#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QmlBridge.h"
#include "game_logic.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Chess/Main.qml"_qs);

    QMLBridge bridge(&app);
    std::unique_ptr<GameLogic> gameLogic = std::make_unique<GameLogic>(bridge, app, engine);

    // Expose the C++ object to QML
    engine.rootContext()->setContextProperty("QMLBridge", &bridge);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
