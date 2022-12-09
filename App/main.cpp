#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "config.hpp"
#include "factoryLd.hpp"
#include "networkList.hpp"
#include "painter.hpp"
#include "symbolsBar.hpp"


Ld::Painter mainPainter{LD_PEN_WIDTH};
Ld::SymbolsBar ldSymbolsBar;
NetworkList networkList;

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    FactoryLd::setPainter(&mainPainter);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("networkList", &networkList);
    engine.rootContext()->setContextProperty("ldSymbolsBar", &ldSymbolsBar);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
