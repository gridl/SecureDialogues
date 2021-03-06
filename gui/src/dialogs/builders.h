#ifndef BUILDERS_H
#define BUILDERS_H

#include <memory>

/**
 * @brief Содержит функции, которые создают диалоги для управления такими
 * примитивами, как контакты, каналы, диалоги.
 */

class BaseSettingsDialog;
class ConnectionInfoContainer;
class ContactContainer;
class DialogCreation;

/**
 * @brief Создает диалог для создания, удаления и редактирования контактов
 * @param contact - контейнер с контактами
 * @param connInfo - контейнер с информацией для подключения к каналам
 * @return  класс диалога, с помощью которого пользователь может управлять
 * своими контактами
 */
std::shared_ptr<BaseSettingsDialog> make_dialog(
    const std::shared_ptr<ContactContainer>& contact,
    const std::shared_ptr<ConnectionInfoContainer>& connInfo);

/**
 * @brief Создает диалог для управления информацией о подключениях для каналов
 * связи
 * @param connInfo контейнер, который содержит информацию о подключениях
 * @return диалог для управления каналами связи.
 */
std::shared_ptr<BaseSettingsDialog> make_dialog(
    const std::shared_ptr<ConnectionInfoContainer>& connInfo);

/**
 * @brief Создает пользовательский диалог для начала общения с удаленным
 * пользователем
 * @param contact контейнер контактов
 * @return объект, через который пользователь может инициировать диалог с
 * удаленным контактом
 */
std::shared_ptr<DialogCreation> make_creation_dialog(
    const std::shared_ptr<ContactContainer>& contact);

#endif  // BUILDERS_H
