/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEEPIN_MANUAL_VIEW_MANUAL_PROXY_H
#define DEEPIN_MANUAL_VIEW_MANUAL_PROXY_H

#include <QDBusConnection>
#include <QDesktopServices>

namespace dman {

class ManualProxy : public QObject
{
    Q_OBJECT
public:
    explicit ManualProxy(QObject *parent = nullptr);
    ~ManualProxy() override;
signals:
    void WidgetLower();
    void channelInit();

public slots:
    QString getSystemManualDir();
    QStringList getSystemManualList();

    void openExternalLink(const QString &url);
    void setApplicationState(const QString &appName);
    QStringList getUsedAppList();
    bool hasSelperSupport();

    void finishChannel();

private:
    void saveAppList(const QStringList &list);

private:
    QStringList app_list_;
};

} // namespace dman

#endif // DEEPIN_MANUAL_VIEW_MANUAL_PROXY_H
