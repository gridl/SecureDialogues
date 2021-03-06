#include "dialog.h"
#include "contact.h"

#include <algorithm>   //for std::generate_n
#include <functional>  //for std::function
#include <random>
#include <vector>
#include "utils.h"

#include <iostream>
#include "dialogstatemachine.h"
static const DialogStateMachine DIALOG_STATE_MACHINE;

invalid_dialog_action::invalid_dialog_action(const std::string& str) :
    std::runtime_error(str) {}

Dialog::Dialog(std::shared_ptr<const Contact> contact,
               const std::string& dialogId,
               Status status) :
    Dialog(contact, dialogId, 0, status) {}

Dialog::Dialog(std::shared_ptr<const Contact> contact,
               const std::string& dialogId,
               unsigned long sequental,
               Dialog::Status status) :
    mContact(contact),
    mDialogId(dialogId), mStatus(status), mLastSequental(sequental) {}

Dialog::Dialog(std::shared_ptr<const Contact> contact) :
    Dialog(contact, make_uiid(), Status::NEW) {}

std::string Dialog::getDialogId() const {
  return mDialogId;
}

std::string Dialog::getChannelMoniker() const {
  return mContact->channelMoniker();
}

DialogMessage Dialog::makeMessage(const DialogMessage::Action action,
                                  const std::string& content) const
    noexcept(false) {
  if (!DIALOG_STATE_MACHINE.isMessageActionAllowed(mStatus, action)) {
    std::stringstream ss;
    ss << "Message with action " << static_cast<int>(action)
       << " cant be made for dialog state " << static_cast<int>(mStatus);
    throw invalid_dialog_action(ss.str());
  }
  return DialogMessage(action, content, mDialogId, mContact->adress());
}

DialogMessage Dialog::makeAbort() {
  setStatus(Status::ABORTED);
  return make_abort(mDialogId, mContact->adress());
}

Dialog::Status Dialog::getStatus() const noexcept {
  return mStatus;
}

void Dialog::setStatus(Dialog::Status status) noexcept(false) {
  if (!DIALOG_STATE_MACHINE.isStateTransitionAllowed(mStatus, status)) {
    std::stringstream ss;
    ss << "Dialog status transision from state " << static_cast<int>(mStatus)
       << " to " << static_cast<int>(status) << " is not allowed";
  }
  mStatus = status;
}

std::string Dialog::getContactId() const {
  return mContact->id();
}

std::string Dialog::getAdress() const {
  return mContact->adress();
}

std::string Dialog::getName() const {
  return mContact->name();
}

bool Dialog::isSequentalOk(unsigned long sequental) {
  if (sequental > mLastSequental) {
    mLastSequental = sequental;
    return true;
  }
  return false;
}

bool Dialog::isMessageActionAllowed(DialogMessage::Action action) const
    noexcept {
  return DIALOG_STATE_MACHINE.isMessageActionAllowed(mStatus, action);
}
