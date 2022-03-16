// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#pragma once

#include "src/core/capturerequest.h"
#include <QObject>
#include <QPointer>
#include <QVersionNumber>
#include <functional>

class CaptureWidget;
class ConfigWindow;
class InfoWindow;
class CaptureLauncher;
class UploadHistory;
#if (defined(Q_OS_MAC) || defined(Q_OS_MAC64) || defined(Q_OS_MACOS) ||        \
     defined(Q_OS_MACX))
class QHotkey;
#endif
using lambda = std::function<void(void)>;

class Controller : public QObject
{
    Q_OBJECT

public:
    enum Origin
    {
        CLI,
        DAEMON
    };

    static Controller* instance();

public slots:
    CaptureWidget* gui(
      const CaptureRequest& req = CaptureRequest::GRAPHICAL_MODE);
    void screen(CaptureRequest req, const int screenNumber = -1);
    void full(const CaptureRequest& req);
    void launcher();
    void config();

    void info();
    void history();

    QVersionNumber getVersion();

public:
    static void setOrigin(Origin origin);
    static Origin origin();

signals:
    // TODO remove all parameters from captureTaken and update dependencies
    void captureTaken(QPixmap p, const QRect& selection);
    void captureFailed();

public slots:
    void requestCapture(const CaptureRequest& request);
    void exportCapture(QPixmap p, QRect& selection, const CaptureRequest& req);

private:
    Controller();
    bool resolveAnyConfigErrors();

    // class members
    static Origin m_origin;

    QPointer<CaptureWidget> m_captureWindow;
    QPointer<InfoWindow> m_infoWindow;
    QPointer<CaptureLauncher> m_launcherWindow;
    QPointer<ConfigWindow> m_configWindow;

#if (defined(Q_OS_MAC) || defined(Q_OS_MAC64) || defined(Q_OS_MACOS) ||        \
     defined(Q_OS_MACX))
    QHotkey* m_HotkeyScreenshotCapture;
    QHotkey* m_HotkeyScreenshotHistory;
#endif
};
