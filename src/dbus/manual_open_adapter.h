/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp com.deepin.Manual.Open.xml -a manual_open_adapter -c
 * ManualOpenAdapter
 *
 * qdbusxml2cpp is Copyright (C) 2017 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef MANUAL_OPEN_ADAPTER_H
#define MANUAL_OPEN_ADAPTER_H

#include <QtDBus/QtDBus>
#include <QStringList>

QT_BEGIN_NAMESPACE
class QByteArray;
template<class T>
class QList;
template<class Key, class Value>
class QMap;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface com.deepin.Manual.Open
 */
class ManualOpenAdapter : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.deepin.Manual.Open")
    Q_CLASSINFO("D-Bus Introspection",
                ""
                "  <interface name=\"com.deepin.Manual.Open\">\n"
                "    <method name=\"Open\">\n"
                "      <arg direction=\"in\" type=\"s\"/>\n"
                "    </method>\n"
                "    <method name=\"OpenTitle\">\n"
                "      <arg direction=\"in\" type=\"s\"/>\n"
                "      <arg direction=\"in\" type=\"s\"/>\n"
                "    </method>\n"
                "    <method name=\"ShowManual\">\n"
                "      <arg direction=\"in\" type=\"s\"/>\n"
                "    </method>\n"
                "    <method name=\"Search\">\n"
                "      <arg direction=\"in\" type=\"s\" name=\"keyword\"/>\n"
                "    </method>\n"

                "  </interface>\n"
                "")
public:
    explicit ManualOpenAdapter(QObject *parent = nullptr);
    virtual ~ManualOpenAdapter();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void Open(const QString &in0);
    void OpenTitle(const QString &in0, const QString &in1);
    void Search(const QString &keyword);
    void ShowManual(const QString &in0);
Q_SIGNALS: // SIGNALS
};

#endif
