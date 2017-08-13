#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "qDebug2Logcat.h"
#include "CameraFilter.h"

int main(int argc, char *argv[])
{
    installLogcatMessageHandler("Camera2");

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<CameraFilter>("CameraFilter", 1, 0, "CameraFilter");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
