#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Service.h"
#include "ImageWindow.h"
#include <QQmlContext>

int main(int argc, char *argv[]) {
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    auto *service = new Service;
    qmlRegisterType<ImageWindow>("ImageWindow", 1, 0, "ImageWindow");
    engine.rootContext()->setContextProperty("$Service", service);
    const QUrl url(u"qrc:/Camera/Main.qml"_qs);
    QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreationFailed,
            &app,
            []() { QCoreApplication::exit(-1); },
            Qt::QueuedConnection);

    engine.load(url);
    QGuiApplication::exec();


}
