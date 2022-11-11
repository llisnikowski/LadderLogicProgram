#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

//#include "contact.hpp"
//#include "coil.hpp"
#include "ldPainter.hpp"
#include "symbolsBar.hpp"


Ld::LdPainter mainLdPainter{64, 2};
Ld::SymbolsBar ldSymbolsBar;


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

//    qmlRegisterType<Ld::Contact>("LdContact",1,0,"LdContact");
//    qmlRegisterType<Ld::Coil>("LdCoil",1,0,"LdCoil");
//    qmlRegisterType<Ld::LdPainter>("LdPainter",1,0,"LdPainter");

    ldSymbolsBar.setLdPainter(&mainLdPainter);


    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

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
