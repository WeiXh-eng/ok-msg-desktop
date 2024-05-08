/*
 * Copyright (c) 2022 船山信息 chuanshaninfo.com
 * The project is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PubL v2. You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the
 * Mulan PubL v2 for more details.
 */

//
// Created by gaojie on 24-5-7.
//

#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include "contentlayout.h"
#include "friendlistwidget.h"
#include <QActionGroup>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class ChatWidget;
}

class CircleWidget;
class GroupInviteForm;
class AddFriendForm;


class ChatWidget : public QWidget {
  Q_OBJECT
public:

  enum class FilterCriteria { All = 0, Online, Offline, Friends, Groups };

  ChatWidget(QWidget *parent = nullptr);
  ~ChatWidget();

  [[nodiscard]] ContentLayout *getContentLayout() const {
    return contentLayout;
  }
  void connectCircleWidget();
  void searchCircle(CircleWidget &circleWidget);
  AddFriendForm *openFriendAddForm();
  void reloadTheme();
  void retranslateUi();
protected:
  void showEvent(QShowEvent*) override;
private:
  Ui::ChatWidget *ui;
  ContentLayout *contentLayout;
  FriendListWidget *contactListWidget;
  CircleWidget *circleWidget;

  Core *core;
  CoreFile *coreFile;

  QAction *statusOnline;
  QAction *statusAway;
  QAction *statusBusy;
  QAction *actionLogout;
  QAction *actionQuit;
  QAction *actionShow;
  void setStatusOnline();
  void setStatusAway();
  void setStatusBusy();

  GroupInviteForm *groupInviteForm;
  uint32_t unreadGroupInvites;
  QPushButton *friendRequestsButton;
    QPushButton *groupInvitesButton;

   std::unique_ptr< AddFriendForm > addFriendForm;

      QMenu *filterMenu;

      QActionGroup *filterGroup;
      QAction *filterAllAction;
      QAction *filterOnlineAction;
      QAction *filterOfflineAction;
      QAction *filterFriendsAction;
      QAction *filterGroupsAction;

      QActionGroup *filterDisplayGroup;
      QAction *filterDisplayName;
      QAction *filterDisplayActivity;

  void init();
  void deinit();
  void updateIcons();
  void setupSearch();
  void searchContacts();

  void updateFilterText();
  FilterCriteria getFilterCriteria() const;
  static bool filterGroups(FilterCriteria index);
  static bool filterOnline(FilterCriteria index);
  static bool filterOffline(FilterCriteria index);
  bool groupsVisible() const;

  void connectToCore(Core* core);

  void groupInvitesUpdate();
  void groupInvitesClear();
    void friendRequestsUpdate() ;

public slots:
  void onCoreChanged(Core &core);

  void onStatusSet(Status::Status status);
  void onUsernameSet(const QString& username);
  void onStatusMessageSet(const QString &statusMessage) ;


  void slot_friendAdded(const ToxPk &friendPk, bool isFriend);
  void onFriendUsernameChanged(const ToxPk &friendPk, const QString &username);

  void onFriendStatusChanged(const ToxPk &friendPk, Status::Status status);
  void onFriendStatusMessageChanged(const ToxPk &friendPk,
                                    const QString &message);

  void onFriendMessageReceived(const ToxPk &friendPk,
                               const lib::messenger::IMMessage &message,
                               bool isAction);
  void onFriendAvatarChanged(const ToxPk &friendPk, const QByteArray &avatar);
  void onReceiptReceived(const ToxPk &friendPk, ReceiptNum receipt);
  void onFriendRequestReceived(const ToxPk &friendPk, const QString &message);

  void onFriendTypingChanged(const ToxPk &friendnumber, bool isTyping);



  void onGroupJoined( const GroupId & groupId, const QString& name);
void onGroupInviteReceived(const GroupInvite &inviteInfo);
void onGroupMessageReceived(QString groupnumber,
                            QString nick,
                            const QString &from,
                            const QString &message,
                            const QDateTime& time,
                            bool isAction);



void onGroupInviteAccepted(const GroupInvite &inviteInfo);

void onGroupPeerListChanged(QString groupnumber);

void onGroupPeerSizeChanged(QString groupnumber, const uint size);

void onGroupPeerNameChanged(QString groupnumber, const ToxPk &peerPk,
                            const QString &newName);
void onGroupTitleChanged(QString groupnumber, const QString &author,
                         const QString &title);

void onGroupPeerStatusChanged(QString groupnumber, QString peerPk,
                              bool  online);
void onGroupClicked();



void changeDisplayMode();
void setupStatus();
};

#endif // CHATWIDGET_H
