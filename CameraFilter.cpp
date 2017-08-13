#include "CameraFilter.h"

#include <QDebug>
#include <QVideoFrame>
#include <QThread>

QImage imageFromVideoFrame(QVideoFrame &frame)
{
    qDebug() << "resolution:(" << frame.width() << ", " << frame.height() << ")";
    QImage image;
    if(frame.map(QAbstractVideoBuffer::ReadOnly)){
        QImage::Format fmt = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
        if(fmt != QImage::Format_Invalid){
            qDebug() << "not invalid format.";
            image = QImage(frame.bits(), frame.width(), frame.height(), /*v.bytesPerLine(),*/fmt);
        }else{
            int nbytes = frame.mappedBytes();
            qDebug() << "invalid format. nbytes=" << nbytes;
            image = QImage::fromData(frame.bits(), nbytes);
        }
        frame.unmap();
    }
    return image.mirrored(true, true);
}

CameraFilter::CameraFilter()
{

}

CameraFilter::~CameraFilter()
{

}

QVideoFilterRunnable *CameraFilter::createFilterRunnable()
{
    return new CameraFilterRunnable(this);
}

CameraFilterRunnable::CameraFilterRunnable(CameraFilter* filter)
{
    m_filter = filter;
}

CameraFilterRunnable::~CameraFilterRunnable()
{

}

QVideoFrame CameraFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{
    Q_UNUSED(surfaceFormat);
    Q_UNUSED(flags);
    QVideoFrame frame(*input);
    qDebug() << "emit QVideoFrame:" << QThread::currentThreadId();

    emit m_filter->cameraResolution(QSize(frame.width(), frame.height()));
    QImage image = imageFromVideoFrame(frame).scaled(QSize(400, 300), Qt::KeepAspectRatio);
    emit m_filter->cameraImage(image);

    return frame;
}
