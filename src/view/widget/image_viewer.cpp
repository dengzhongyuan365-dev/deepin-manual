// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "view/widget/image_viewer.h"
#include "base/ddlog.h"

#include <DLog>
#include <QApplication>
#include <QShortcut>
#include <QImageReader>
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include <QDesktopWidget>
#else
#include <QScreen>
#endif

namespace {

const int kBorderSize = 12;
const int kCloseBtnSize = 48;

} // namespace

ImageViewer::ImageViewer(QWidget *parent)
    : QDialog(parent)
{
    qCDebug(app) << "ImageViewer constructor called";
    this->setObjectName("ImageViewer");
    this->initUI();

    connect(close_button_, &Dtk::Widget::DIconButton::clicked, this, &ImageViewer::close);
    qCDebug(app) << "ImageViewer constructor done";
}

ImageViewer::~ImageViewer()
{
    qCDebug(app) << "ImageViewer destructor called";
}

/**
 * @brief ImageViewer::open
 * @param filepath
 * @note 根据给定的图片文件路径，打开图片并全屏显示
 */
void ImageViewer::open(const QString &filepath)
{
    qCDebug(app) << filepath;

    // Escape uri.
    QString abspath(filepath);
    if (abspath.contains("://")) {
        QUrl url(abspath);
        abspath = url.path();
        qCDebug(app) << "Extracted path from URL:" << abspath;
    }
    QImage image;
    QImageReader reader(abspath);
    reader.setDecideFormatFromContent(true);
    if (reader.canRead()) {
        if (reader.read(&image)) {
            qCDebug(app) << "image open is successful....";
        } else {
            qCDebug(app) << "image open is failed...." << reader.errorString();
        }

    } else {
        qCDebug(app) << "can not read...." << reader.errorString();
    }
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    const QRect screen_rect = qApp->desktop()->screenGeometry(QCursor::pos());
#else
    const QRect screen_rect = QGuiApplication::primaryScreen()->geometry();
#endif
    const int pixmap_max_width = static_cast<int>(screen_rect.width() * 0.8);
    const int pixmap_max_height = static_cast<int>(screen_rect.height() * 0.8);

    if ((image.width() > pixmap_max_width) || (image.height() > pixmap_max_height)) {
        qCDebug(app) << "Scaling image from" << image.size()
                    << "to max" << pixmap_max_width << "x" << pixmap_max_height;
        image = image.scaled(pixmap_max_width, pixmap_max_height, Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
    }
    //小图标不点击放大
    if (image.width() < 50 && image.height() < 50) {
        qCDebug(app) << "Skipping small image:" << image.size();
        return;
    }
    this->move(screen_rect.topLeft());
    this->resize(screen_rect.size());
    this->showFullScreen();

    img_label_->setPixmap(QPixmap::fromImage(image));
    img_label_->setFixedSize(image.width(), image.height());

    QRect img_rect = img_label_->rect();
    img_rect.moveTo(static_cast<int>((screen_rect.width() - image.width()) / 2.0),
                    static_cast<int>((screen_rect.height() - image.height()) / 2.0));
    img_label_->move(img_rect.topLeft());

    //关闭按钮移到图片右上角
    const QPoint top_right_point = img_rect.topRight();
    close_button_->move(top_right_point.x() - kCloseBtnSize / 2,
                        top_right_point.y() - kCloseBtnSize / 2);
    close_button_->show();
    close_button_->raise();
    qCDebug(app) << "ImageViewer opened:" << filepath;
}

/**
 * @brief ImageViewer::initUI
 * 界面初始化
 */
void ImageViewer::initUI()
{
    qCDebug(app) << "Initializing ImageViewer UI";
    img_label_ = new DLabel(this);
    img_label_->setObjectName("ImageLabel");

    close_button_ = new DDialogCloseButton(this);
    close_button_->setFlat(true);
    close_button_->setObjectName("CloseButton");
    close_button_->raise();
    close_button_->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    close_button_->setIconSize(QSize(36, 36));
    close_button_->setFixedSize(45, 45);

    this->setContentsMargins(kBorderSize, kBorderSize, kBorderSize, kBorderSize);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::BypassWindowManagerHint
                         | Qt::Dialog | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setModal(true);

    QShortcut *scHideDialog = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    scHideDialog->setContext(Qt::ApplicationShortcut);
    scHideDialog->setAutoRepeat(false);

    connect(scHideDialog, &QShortcut::activated, this, [this] {
        qCDebug(app) << "pressed esc!";
        this->hide();
    });

    qCDebug(app) << "UI initialization completed";
}

/**
 * @brief ImageViewer::mousePressEvent
 * @param event
 * 重写鼠标点击事件，打开图片后点击窗口任意位置，都隐藏此界面
 */
void ImageViewer::mousePressEvent(QMouseEvent *event)
{
    qCDebug(app) << "Mouse press event";
    QWidget::mousePressEvent(event);
    this->hide();
    qCDebug(app) << "Image viewer hidden by mouse click";
}

/**
 * @brief ImageViewer::paintEvent
 * @param event
 * 画图事件，重绘整个屏幕大小
 */
void ImageViewer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(0, 0, this->width(), this->height(), QColor(0, 0, 0, 77));
}
