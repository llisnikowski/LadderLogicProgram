#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QQuickItem>
#include "coil.hpp"
#include "contact.hpp"
#include "logInterface.hpp"
#include "networkList.hpp"
#include "codeGenerator.hpp"
#include <QString>
#include "addressField.hpp"

class LogMock : public QObject, public LogInterface
{
public:
    MOCK_METHOD1(addToLogs, void(QString message));
};


class CodeGenetor_Test : public ::testing::Test
{
public:
    CodeGenetor_Test(){
        codeGenerator_.setNetworkList(&networkList_);
        codeGenerator_.setLogObject(&logError_);
        QObject::connect(&codeGenerator_, &CodeGenerator::codeReady,
                         &logCode_, &LogMock::addToLogs);
    }
    ~CodeGenetor_Test(){
        QObject::disconnect(&codeGenerator_, &CodeGenerator::codeReady,
                         &logCode_, &LogMock::addToLogs);
    }

protected:
    CodeGenerator codeGenerator_;
    LogMock logError_;
    LogMock logCode_;
    static NetworkList networkList_;
};


QQuickItem parentItem;
NetworkList CodeGenetor_Test::networkList_{};


TEST_F(CodeGenetor_Test, Init)
{
    networkList_.setParentItem(&parentItem);
    EXPECT_EQ(networkList_.count(), 1);
}

TEST_F(CodeGenetor_Test, Empty)
{
    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, contact)
{
    ContainerLd &container = networkList_.getNetwork(0)->getContainerLd();
    Ld::Contact contact;
    container.add(&contact, 0, 1);

    EXPECT_CALL(logError_, addToLogs(QString{
                              "Niepoprawny adress obiektu"
                          })).Times(1);
    EXPECT_FALSE(codeGenerator_.startGenerating());

    static_cast<Ld::Contact*>(container.getItem(0, 1))->getAddress() = "I01";
    EXPECT_CALL(logError_, addToLogs(QString{
                               "Brak wyjścia"
                           })).Times(1);
    EXPECT_FALSE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, coil)
{
    ContainerLd &container = networkList_.getNetwork(0)->getContainerLd();
    Ld::Coil coil;
    container.remove(0, 1);
    container.add(&coil, 0, 1);

    EXPECT_CALL(logError_, addToLogs(QString{
                               "Niepoprawny adress obiektu"
                           })).Times(1);
    EXPECT_FALSE(codeGenerator_.startGenerating());

    static_cast<Ld::Coil*>(container.getItem(0, 1))->getAddress() = "Q00";
    EXPECT_CALL(logError_, addToLogs(QString{
                                             "Brak wejścia"
                           })).Times(1);
    EXPECT_FALSE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, contactAndCoil)
{
    ContainerLd &container = networkList_.getNetwork(0)->getContainerLd();
    Ld::Contact contact;
    container.add(&contact, 0, 1);

    EXPECT_CALL(logError_, addToLogs(QString{
                               "Niepoprawny adress obiektu"
                           })).Times(1);
    EXPECT_FALSE(codeGenerator_.startGenerating());

    static_cast<Ld::Contact*>(container.getItem(0, 1))->getAddress() = "I00";
    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00=Q00\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}
