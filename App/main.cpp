#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "config.hpp"
#include "factoryLd.hpp"
#include "networkList.hpp"
#include "serialPort.hpp"
#include "symbolsBar.hpp"
#include "propertiesList.hpp"
#include "consoleLog.hpp"
#include "codeGenerator.hpp"

Ld::SymbolsBar ldSymbolsBar;
NetworkList networkList;
SelectItem selectItem;
PropertiesList propertyList;
ConsoleLog consoleLog;
CodeGenerator codeGenerator;
SerialPort serialPort;


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    FactoryLd::setSelectItem(&selectItem);
    codeGenerator.setNetworkList(&networkList);
    codeGenerator.setLogObject(&consoleLog);
    serialPort.setLogObject(&consoleLog);

    QObject::connect(&selectItem, &SelectItem::changedSelectItem,
                     &propertyList, &PropertiesList::display);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("networkList", &networkList);
    engine.rootContext()->setContextProperty("ldSymbolsBar", &ldSymbolsBar);
    engine.rootContext()->setContextProperty("selectItem", &selectItem);
    engine.rootContext()->setContextProperty("propertyList", &propertyList);
    engine.rootContext()->setContextProperty("consoleLog", &consoleLog);
    engine.rootContext()->setContextProperty("codeGenerator", &codeGenerator);
    engine.rootContext()->setContextProperty("serialPort", &serialPort);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
