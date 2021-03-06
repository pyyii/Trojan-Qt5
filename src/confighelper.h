/*
 * Copyright (C) 2015-2016 Symeon Huang <hzwhuang@gmail.com>
 *
 * shadowsocks-qt5 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * shadowsocks-qt5 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libQtShadowsocks; see the file LICENSE. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef CONFIGHELPER_H
#define CONFIGHELPER_H

#include <QSettings>
#include "connectiontablemodel.h"
#include "connection.h"
#include "tqsubscribe.h"

class ConfigHelper : public QObject
{
    Q_OBJECT

public:
    /*
     * Construct a ConfigHelper object using specified configuration file
     * This constructor will call readGeneralSettings().
     */
    explicit ConfigHelper(const QString &configuration, QObject *parent = nullptr);

    /*
     * Call read() function to read all connection profiles into
     * specified ConnectionTableModel.
     * This function also calls readGeneralSettings().
     */
    void read(ConnectionTableModel *model);

    QList<TQSubscribe> readSubscribes();

    /*
     * readGeneralSettings() only reads General settings and store them into
     * member variables.
     */
    void readGeneralSettings();

    void readAdvanceSettings();

    void save(const ConnectionTableModel &model);

    void saveSubscribes(QList<TQSubscribe> subscribes);

    void importGuiConfigJson(ConnectionTableModel *model, const QString &file);

    void exportGuiConfigJson(const ConnectionTableModel& model, const QString &file);

    void importShadowrocketJson(ConnectionTableModel *model, const QString &file);

    void exportShadowrocketJson(const ConnectionTableModel &model, const QString &file);

    void exportTrojanSubscribe(const ConnectionTableModel &model, const QString &file);

    Connection* configJsonToConnection(const QString &file);

    void connectionToJson(TQProfile &profile);

    void generatePrivoxyConf();

    //start those connections marked as auto-start
    void startAllAutoStart(const ConnectionTableModel& model);

    //create or delete start up item for shadowsocks-qt5
    void setStartAtLogin();

    /* some functions used to communicate with SettingsDialog */
    int  getToolbarStyle() const;
    int  getLogLevel() const;
    QString getSocks5Address() const;
    int getSocks5Port() const;
    QString getHttpAddress() const;
    int getHttpPort() const;
    QString getPACAddress() const;
    int getPACPort() const;
    QString getSystemProxySettings() const;
    bool isTrojanOn() const;
    bool isEnableHttpMode() const;
    bool isHideWindowOnStartup() const;
    bool isStartAtLogin() const;
    bool isOnlyOneInstance() const;
    bool isCheckPortAvailability() const;
    bool isEnableNotification() const;
    bool isHideDockIcon() const;
    bool isAutoUpdateSubscribes() const;
    bool isShowToolbar() const;
    bool isShowFilterBar() const;
    bool isNativeMenuBar() const;
    void setGeneralSettings(int ts, bool hide, bool sal, bool oneInstance, bool cpa, bool en, bool hdi, bool nativeMB);
    void setAdvanceSettings(int ll, bool hm, QString sa, int sp, QString ha, int hp, QString pa, int pp);
    void setSystemProxySettings(QString mode);
    void setTrojanOn(bool on);
    void setAutoUpdateSubscribes(bool update);
    void setMainWindowGeometry(const QByteArray &geometry);
    void setMainWindowState(const QByteArray &state);
    void setTableGeometry(const QByteArray &geometry);
    void setTableState(const QByteArray &state);

    QByteArray getMainWindowGeometry() const;
    QByteArray getMainWindowState() const;
    QByteArray getTableGeometry() const;
    QByteArray getTableState() const;

public slots:
    void setShowToolbar(bool show);
    void setShowFilterBar(bool show);

signals:
    void toolbarStyleChanged(const Qt::ToolButtonStyle);

private:
    int logLevel;
    int toolbarStyle;
    bool enableHttpMode;
    QString socks5LocalAddress;
    int socks5LocalPort;
    QString httpLocalAddress;
    int httpLocalPort;
    QString pacLocalAddress;
    int pacLocalPort;
    QString systemProxyMode;
    bool trojanOn;
    bool autoUpdateSubscribes;
    bool hideWindowOnStartup;
    bool startAtLogin;
    bool onlyOneInstace;
    bool checkPortAvailability;
    bool enableNotification;
    bool hideDockIcon;
    bool showToolbar;
    bool showFilterBar;
    bool nativeMenuBar;
    QSettings *settings;
    QString configFile;

    void checkProfileDataUsageReset(TQProfile &profile);

    static const QString profilePrefix;

    static const QString subscribePrefix;
};

#endif // CONFIGHELPER_H
