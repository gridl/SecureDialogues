#ifndef DIALOGACTIONHANDLERWRAPPER_H
#define DIALOGACTIONHANDLERWRAPPER_H

#include <QObject>
#include <memory>
class Contact;
class DialogActionHandler;

/**
 * @brief Класс-оболочка для взаимодействия с DialogActionHandler
 * Нужен для применения системы сигналов-слотов.
 */
class DialogActionHandlerWrapper : public QObject {
  Q_OBJECT
 public:
  explicit DialogActionHandlerWrapper(
      std::shared_ptr<DialogActionHandler> handler,
      QObject* parent = nullptr);

 signals:

 public slots:
  void createDialogAction(std::shared_ptr<const Contact> contact);
  void acceptDialogAction(std::string dialogId);
  void closeDialogAction(std::string dialogId);
  void cancelDialogAction(std::string dialogId);
  void abortDialogAction(std::string dialogId);
  void removeDialogAction(std::string dialogId);

 private:
  std::shared_ptr<DialogActionHandler> mHandler;
};

#endif  // DIALOGACTIONHANDLERWRAPPER_H
