#ifndef CAMERAFILTER_H
#define CAMERAFILTER_H

#include <QAbstractVideoFilter>
#include <QVideoFilterRunnable>

extern QImage imageFromVideoFrame(QVideoFrame &frame);

class CameraFilter : public QAbstractVideoFilter
{
    Q_OBJECT
public:
    explicit CameraFilter();
    ~CameraFilter();
    QVideoFilterRunnable *createFilterRunnable();
private:
signals:
    void finished(QObject *result);
    void cameraResolution(const QSize &resolution);
    void cameraImage(QImage image);
public slots:

};

class CameraFilterRunnable : public QVideoFilterRunnable
{
public:
    CameraFilterRunnable(CameraFilter* filter = NULL);
    ~CameraFilterRunnable();
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);

private:
    CameraFilter *m_filter;
};

#endif // CAMERAFILTER_H
