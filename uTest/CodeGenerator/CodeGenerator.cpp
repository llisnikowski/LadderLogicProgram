#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QQuickItem>
#include "coil.hpp"
#include "contact.hpp"
#include "counter.hpp"
#include "logInterface.hpp"
#include "networkList.hpp"
#include "codeGenerator.hpp"
#include <QString>
#include "addressField.hpp"
#include "timer.hpp"
#include "weektimer.hpp"

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

TEST_F(CodeGenetor_Test, Or)
{
    ContainerLd &container = networkList_.getNetwork(0)->getContainerLd();
    Ld::Contact contact;
    contact.getAddress() = "i01";
    container.add(&contact, 1, 1);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01=Q00\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, And)
{
    ContainerLd &container = networkList_.getNetwork(0)->getContainerLd();
    Ld::Contact contact;
    contact.getAddress() = "i2";
    container.add(&contact, 0, 5);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01&I02=Q00\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, NegativeContact)
{
    ContainerLd &container = networkList_.getNetwork(0)->getContainerLd();
    Ld::Contact contact;
    contact.getAddress() = "I3";
    contact.getPropertyType() = 1;
    container.add(&contact, 0, 7);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01&I02&i03=Q00\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, FullNetwork)
{
    ContainerLd &container = networkList_.getNetwork(0)->getContainerLd();
    Ld::Contact contact;
    contact.getAddress() = "I12";
    contact.getPropertyType() = 1;
    container.add(&contact, 2, 1);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01|i12&I02&i03=Q00\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, CoilSet)
{
    ContainerLd &container = networkList_.getNetwork(1)->getContainerLd();
    Ld::Contact contact;
    contact.getAddress() = "I05";
    container.add(&contact, 0, 1);

    Ld::Coil coil;
    coil.getAddress() = "Q01";
    coil.getPropertyType() = 1;
    container.add(&coil, 0, 3);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01|i12&I02&i03=Q00\r\n"
                              ":N01 I05SQ01\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, CoilReset)
{
    ContainerLd &container = networkList_.getNetwork(2)->getContainerLd();
    Ld::Contact contact;
    contact.getAddress() = "I06";
    contact.getPropertyType() = 1;
    container.add(&contact, 0, 1);

    Ld::Coil coil;
    coil.getAddress() = "Q01";
    coil.getPropertyType() = 2;
    container.add(&coil, 0, 3);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01|i12&I02&i03=Q00\r\n"
                              ":N01 I05SQ01\r\n"
                              ":N02 i06RQ01\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, Timer)
{
    ContainerLd &container = networkList_.getNetwork(3)->getContainerLd();
    Ld::Contact contact;
    contact.getAddress() = "I07";
    contact.getPropertyType() = 1;
    container.add(&contact, 0, 1);

    Ld::Timer timer;
    timer.getAddress() = "T02";
    timer.getPropertyType() = 2;
    timer.getTime() = 1234;
    timer.getTime().setUnits(0);
    container.add(&timer, 0, 3);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01|i12&I02&i03=Q00\r\n"
                              ":N01 I05SQ01\r\n"
                              ":N02 i06RQ01\r\n"
                              ":N03 i07=T02\r\n"
                              ":T02 s1234m2\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, CounterAdd)
{
    ContainerLd &container = networkList_.getNetwork(4)->getContainerLd();
    Ld::Contact contact;
    contact.getAddress() = "I07";
    container.add(&contact, 0, 1);

    Ld::Counter counter;
    counter.getAddress() = "C04";
    counter.getCounter() = 64;
    container.add(&counter, 0, 3);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01|i12&I02&i03=Q00\r\n"
                              ":N01 I05SQ01\r\n"
                              ":N02 i06RQ01\r\n"
                              ":N03 i07=T02\r\n"
                              ":N04 I07=C04\r\n"
                              ":T02 s1234m2\r\n"
                              ":C04 0064\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, CounterReset)
{
    ContainerLd &container = networkList_.getNetwork(5)->getContainerLd();
    Ld::Contact contact;
    contact.getAddress() = "I08";
    container.add(&contact, 0, 1);

    Ld::Counter counter;
    counter.getAddress() = "C04";
    counter.getPropertyType() = 2;
    counter.getCounter() = 11;
    container.add(&counter, 0, 3);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01|i12&I02&i03=Q00\r\n"
                              ":N01 I05SQ01\r\n"
                              ":N02 i06RQ01\r\n"
                              ":N03 i07=T02\r\n"
                              ":N04 I07=C04\r\n"
                              ":N05 I08RC04\r\n"
                              ":T02 s1234m2\r\n"
                              ":C04 0064\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, CounterDir)
{
    ContainerLd &container = networkList_.getNetwork(6)->getContainerLd();
    Ld::Contact contact;
    contact.getAddress() = "I09";
    container.add(&contact, 0, 1);

    Ld::Counter counter;
    counter.getAddress() = "C04";
    counter.getPropertyType() = 1;
    counter.getCounter() = 12;
    container.add(&counter, 0, 3);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01|i12&I02&i03=Q00\r\n"
                              ":N01 I05SQ01\r\n"
                              ":N02 i06RQ01\r\n"
                              ":N03 i07=T02\r\n"
                              ":N04 I07=C04\r\n"
                              ":N05 I08RC04\r\n"
                              ":N06 I09=D04\r\n"
                              ":T02 s1234m2\r\n"
                              ":C04 0064\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}

TEST_F(CodeGenetor_Test, Weektimer)
{
    ContainerLd &container = networkList_.getNetwork(7)->getContainerLd();
    Ld::Weektimer weektimer;
    weektimer.getAddress() = "Z00";
    weektimer.getTimeOn() = "11:43";
    weektimer.getTimeOff() = "13:45";
    weektimer.getDaysOfWeek().setValue(0b0110'1100);
    container.add(&weektimer, 0, 1);

    Ld::Coil coil;
    coil.getAddress() = "Q05";
    container.add(&coil, 0, 3);

    EXPECT_CALL(logCode_, addToLogs(QString{
                              ":START\r\n"
                              ":N00 I00|I01|i12&I02&i03=Q00\r\n"
                              ":N01 I05SQ01\r\n"
                              ":N02 i06RQ01\r\n"
                              ":N03 i07=T02\r\n"
                              ":N04 I07=C04\r\n"
                              ":N05 I08RC04\r\n"
                              ":N06 I09=D04\r\n"
                              ":N07 Z00=Q05\r\n"
                              ":T02 s1234m2\r\n"
                              ":C04 0064\r\n"
                              ":Z00 1143 1345 01101100\r\n"
                              ":END"
                          })).Times(1);
    EXPECT_TRUE(codeGenerator_.startGenerating());
}




