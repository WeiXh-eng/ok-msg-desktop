/*
 * Copyright (c) 2022 船山信息 chuanshaninfo.com
 * The project is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PubL v2. You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#ifndef FRIEND_CHATROOM_H
#define FRIEND_CHATROOM_H

#include "chatroom.h"

#include <QLabel>
#include <QObject>
#include <QString>
#include <QVector>

class IDialogsManager;
class Friend;
class Group;

struct GroupToDisplay
{
    QString name;
    Group* group;
};

struct CircleToDisplay
{
    QString name;
    int circleId;
};

class FriendChatroom : public Chatroom
{
    Q_OBJECT
public:
    FriendChatroom(const Friend* frnd, IDialogsManager* dialogsManager);
    ~FriendChatroom();

  const  Contact* getContact() override;

public slots:

  const  Friend* getFriend();



    bool canBeInvited() const;

    int getCircleId() const;
    QString getCircleName() const;

    void inviteToNewGroup();
    void inviteFriend(const Group* group);

    bool autoAcceptEnabled() const;
    QString getAutoAcceptDir() const;
    void disableAutoAccept();
    void setAutoAcceptDir(const QString& dir);

    QVector<GroupToDisplay> getGroups() const;
    QVector<CircleToDisplay> getOtherCircles() const;

    void resetEventFlags();

    bool possibleToOpenInNewWindow() const;
    bool canBeRemovedFromWindow() const;
    bool friendCanBeRemoved() const;
    void removeFriendFromDialogs();


private:
    bool active{false};
    const Friend* frnd{nullptr};
    IDialogsManager* dialogsManager{nullptr};

};

#endif // FRIEND_H
