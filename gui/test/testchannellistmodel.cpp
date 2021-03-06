#include "communication/messagedespatcher.h"
#include "fakechanneladaptersendmessageonly.h"

#include "cryptosystemfake.h"
#include "fakechanneladapter.h"
#include "fakenotifier.h"
#include "models/channelslistmodel.h"

#include <QTest>

#include <memory>
#include "containers/connectioninfocontainer.h"

class TestChannelListModel : public QObject {
  Q_OBJECT
 public:
  explicit TestChannelListModel(QObject* parent = nullptr);

 signals:

 private slots:
  void init();
  void testAddElement();
  void testAddElement_data();

 private:
  std::unique_ptr<ConnectionInfoContainer> mContainer;
  std::shared_ptr<ChannelsListModel> mModel;
};

TestChannelListModel::TestChannelListModel(QObject* parent) : QObject(parent) {}

void TestChannelListModel::init() {
  auto messageDispatcher = std::make_shared<MessageDespatcher>(
      std::make_shared<CryptoSystemFake>(), std::make_shared<FakeNotifier>());

  mContainer.reset(new ConnectionInfoContainer());
  mContainer->add(ConnectionHolder(UdpConnection{}, "conn 1"));
  mContainer->add(ConnectionHolder(UdpConnection{}, "conn 2"));
  mContainer->add(ConnectionHolder(UdpConnection{}, "conn 3"));
  mContainer->add(ConnectionHolder(UdpConnection{}, "conn 4"));

  mModel = std::make_shared<ChannelsListModel>(mContainer->getAllElements());
  mContainer->registerWatcher(mModel);
}

void TestChannelListModel::testAddElement() {
  QFETCH(QString, added_name);
  QFETCH(int, added_pos);

  mContainer->add(ConnectionHolder(UdpConnection{}, added_name.toStdString()));
  auto data = mModel->data(mModel->index(added_pos, 0)).toString();

  QCOMPARE(data, added_name);
}

void TestChannelListModel::testAddElement_data() {
  QTest::addColumn<QString>("added_name");
  QTest::addColumn<int>("added_pos");

  QTest::newRow("0") << QString("added 1") << 4;
  QTest::newRow("1") << QString("added 2") << 4;
  QTest::newRow("2") << QString("added 3") << 4;
  QTest::newRow("3") << QString("added 4") << 4;
}

QTEST_MAIN(TestChannelListModel)
#include "testchannellistmodel.moc"
