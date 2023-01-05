#include "address.hpp"
#include "coil.hpp"
#include "contact.hpp"
#include "containerLd.hpp"
#include "networkList.hpp"
#include "saver.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Saver_Test : public ::testing::Test
{
public:
    Saver_Test(){
        saver_.setFile("SaverTestFile");
        saver_.setNetworkList(&networkList_);
    }

protected:
    Saver saver_;
    static QQuickItem parentItem_;
    static NetworkList networkList_;
};

QQuickItem Saver_Test::parentItem_{};
NetworkList Saver_Test::networkList_{};


TEST_F(Saver_Test, Init)
{
    networkList_.setParentItem(&parentItem_);
    EXPECT_EQ(networkList_.count(), 1);
}

TEST_F(Saver_Test, emptyNetwork)
{
    saver_.save();
    networkList_.clearList();
    saver_.load();
    EXPECT_EQ(networkList_.count(), 1);
    EXPECT_EQ(networkList_.getNetwork(0)->getContainerLd().getSchemat(), "-;");
}

TEST_F(Saver_Test, saveContact)
{
    {
        auto &containerLd = networkList_.getNetwork(0)->getContainerLd();
        Ld::Contact contact;
        containerLd.add(&contact, 0, 1);
        EXPECT_EQ(containerLd.getSchemat(), "-I-;-;");
    }
    EXPECT_EQ(networkList_.count(), 2);
    saver_.save();
    networkList_.clearList();
    saver_.load();

    EXPECT_EQ(networkList_.count(), 2);
    auto &containerLd = networkList_.getNetwork(0)->getContainerLd();
    EXPECT_EQ(containerLd.getSchemat(), "-I-;-;");
}

TEST_F(Saver_Test, saveCoilWithAddress)
{
    {
        auto &containerLd = networkList_.getNetwork(0)->getContainerLd();
        Ld::Coil coil;
        coil.getAddress() = "Q00";
        containerLd.add(&coil, 0, 3);
        EXPECT_EQ(containerLd.getSchemat(), "-I-O-;-;");
    }
    EXPECT_EQ(networkList_.count(), 2);
    saver_.save();
    networkList_.clearList();
    saver_.load();

    EXPECT_EQ(networkList_.count(), 2);
    auto &containerLd = networkList_.getNetwork(0)->getContainerLd();
    EXPECT_EQ(containerLd.getSchemat(), "-I-O-;-;");
    auto coil =static_cast<Ld::Address*>(containerLd.getDragItem(0,3));
    EXPECT_EQ(coil->getAddress().getTextValue(), "Q00");
}

TEST_F(Saver_Test, saveNode)
{
    {
        auto &containerLd = networkList_.getNetwork(0)->getContainerLd();
        Ld::Contact contact;
        contact.getAddress() = "qwerty";
        containerLd.add(&contact, 1, 1);
        EXPECT_EQ(containerLd.getSchemat(), "-I-+-O-;-I-+;-;");
    }
    saver_.save();
    networkList_.clearList();
    saver_.load();

    EXPECT_EQ(networkList_.count(), 2);
    auto &containerLd = networkList_.getNetwork(0)->getContainerLd();
    EXPECT_EQ(containerLd.getSchemat(), "-I-+-O-;-I-+;-;");
    EXPECT_EQ(static_cast<Ld::Address*>(containerLd.getDragItem(0,5))->
              getAddress().getTextValue(), "Q00");
    EXPECT_EQ(static_cast<Ld::Address*>(containerLd.getDragItem(1,1))->
              getAddress().getTextValue(), "qwerty");
}

TEST_F(Saver_Test, multinetwork)
{
    {
        auto &containerLd = networkList_.getNetwork(1)->getContainerLd();
        Ld::Contact contact;
        contact.getAddress() = "contact";
        containerLd.add(&contact, 0, 1);
        EXPECT_EQ(containerLd.getSchemat(), "-I-;-;");
    }
    saver_.save();
    networkList_.clearList();
    saver_.load();

    EXPECT_EQ(networkList_.count(), 3);
    {
        auto &containerLd = networkList_.getNetwork(0)->getContainerLd();
        EXPECT_EQ(containerLd.getSchemat(), "-I-+-O-;-I-+;-;");
        EXPECT_EQ(static_cast<Ld::Address*>(containerLd.getDragItem(0,5))->
                  getAddress().getTextValue(), "Q00");
        EXPECT_EQ(static_cast<Ld::Address*>(containerLd.getDragItem(1,1))->
                  getAddress().getTextValue(), "qwerty");
    }
    {
        auto &containerLd = networkList_.getNetwork(1)->getContainerLd();
        EXPECT_EQ(containerLd.getSchemat(), "-I-;-;");
        EXPECT_EQ(static_cast<Ld::Address*>(containerLd.getDragItem(0,1))->
                  getAddress().getTextValue(), "contact");
    }
}




