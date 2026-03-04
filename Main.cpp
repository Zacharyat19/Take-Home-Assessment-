#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QString>

class MinimalDashboard : public QMainWindow {
public:
    MinimalDashboard(QWidget *parent = nullptr) : QMainWindow(parent), counter(0) {
        // 1. Set up the central widget and layout
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // 2. Create UI elements
        QLabel *sensorLabel = new QLabel("Sensor Value: 0", this);
        QPushButton *toggleButton = new QPushButton("Start Simulation", this);

        // 3. Add elements to the layout and set the central widget
        layout->addWidget(sensorLabel);
        layout->addWidget(toggleButton);
        setCentralWidget(centralWidget);

        // 4. Set up the timer for data simulation
        QTimer *timer = new QTimer(this);
        timer->setInterval(1000); // 1000 milliseconds = 1 second

        // 5. Connect the timer to update the label
        connect(timer, &QTimer::timeout, this, [this, sensorLabel]() {
            counter++;
            sensorLabel->setText("Sensor Value: " + QString::number(counter));
        });

        // 6. Connect the button to control the timer
        connect(toggleButton, &QPushButton::clicked, this, [timer, toggleButton]() {
            if (timer->isActive()) {
                timer->stop();
                toggleButton->setText("Start Simulation");
            } else {
                timer->start();
                toggleButton->setText("Stop Simulation");
            }
        });
    }

private:
    int counter;
};

int main(int argc, char *argv[]) {
    // QApplication manages the GUI application's control flow and main settings
    QApplication app(argc, argv);
    
    MinimalDashboard window;
    window.setWindowTitle("Take-Home Challenge Foundation");
    window.resize(300, 150);
    window.show();
    
    return app.exec();
}