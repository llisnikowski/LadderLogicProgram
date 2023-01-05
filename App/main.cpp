#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "interfaceButtons.hpp"
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
CodeGenerator codeGenerator;
SerialPort serialPort;
ConsoleLog consoleLog;
Saver saver;
InterfaceButtons interfaceButtons;


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    FactoryLd::setSelectItem(&selectItem);
    codeGenerator.setNetworkList(&networkList);
    codeGenerator.setLogObject(&consoleLog);
    serialPort.setLogObject(&consoleLog);
    saver.setNetworkList(&networkList);

    interfaceButtons.setLogObject(&consoleLog);
    interfaceButtons.setSerialPort(&serialPort);
    interfaceButtons.setSaver(&saver);
    interfaceButtons.setCodeGenerator(&codeGenerator);
    interfaceButtons.setNetworkList(&networkList);

    QObject::connect(&selectItem, &SelectItem::changedSelectItem,
                     &propertyList, &PropertiesList::display);


    engine.rootContext()->setContextProperty("networkList", &networkList);
    engine.rootContext()->setContextProperty("ldSymbolsBar", &ldSymbolsBar);
    engine.rootContext()->setContextProperty("selectItem", &selectItem);
    engine.rootContext()->setContextProperty("propertyList", &propertyList);
    engine.rootContext()->setContextProperty("consoleLog", &consoleLog);
    engine.rootContext()->setContextProperty("codeGenerator", &codeGenerator);
    engine.rootContext()->setContextProperty("serialPort", &serialPort);
    engine.rootContext()->setContextProperty("interfaceButtons", &interfaceButtons);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
