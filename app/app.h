#ifndef APP_H
#define APP_H

#include <QObject>
#include <QTimer>

class MainWindow;
class TopModel;

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = nullptr);
private:
    QTimer *timer;

    MainWindow *view;
    TopModel *viewModel;
    void setConnection();
};

#endif // APP_H
