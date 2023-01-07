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
PropertiesList propertiesList;
CodeGenerator codeGenerator;
SerialPort serialPort;
ConsoleLog consoleLog;
Saver saver;
InterfaceButtons interfaceButtons;

void settingUpObjects();
void configureQmlObjects(QQmlApplicationEngine &engine);

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    settingUpObjects();
    configureQmlObjects(engine);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    return app.exec();
}

void settingUpObjects()
{
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
                     &propertiesList, &PropertiesList::display);
}

void configureQmlObjects(QQmlApplicationEngine &engine)
{
    engine.rootContext()->setContextProperty("networkList", &networkList);
    engine.rootContext()->setContextProperty("ldSymbolsBar", &ldSymbolsBar);
    engine.rootContext()->setContextProperty("selectItem", &selectItem);
    engine.rootContext()->setContextProperty("propertiesList", &propertiesList);
    engine.rootContext()->setContextProperty("consoleLog", &consoleLog);
    engine.rootContext()->setContextProperty("codeGenerator", &codeGenerator);
    engine.rootContext()->setContextProperty("serialPort", &serialPort);
    engine.rootContext()->setContextProperty("interfaceButtons", &interfaceButtons);
}


