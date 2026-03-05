#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QRandomGenerator>

// Qt Charts specific headers
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>

class ChartDashboard : public QMainWindow {
public:
    ChartDashboard(QWidget *parent = nullptr) : QMainWindow(parent), tickCount(0) {
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // 1. Set up the Data Series
        QLineSeries *series = new QLineSeries();
        series->setName("Temperature (°C)");

        // 2. Set up the Chart logic
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Live Sensor Data");
        chart->setAnimationOptions(QChart::NoAnimation); // Disabling animation improves performance for live data

        // 3. Set up the Axes
        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("Time (Ticks)");
        axisX->setRange(0, 30); // Initial display window of 30 ticks
        axisX->setLabelFormat("%d");

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Value");
        axisY->setRange(0, 100);

        // Attach axes to the chart and the series
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisX);
        series->attachAxis(axisY);

        // 4. Set up the Visual View
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing); // Smooths the jagged edges of the line

        // 5. Basic Control Button
        QPushButton *toggleButton = new QPushButton("Start Simulation", this);

        // Assemble the UI
        layout->addWidget(chartView);
        layout->addWidget(toggleButton);
        setCentralWidget(centralWidget);

        // 6. Data Simulation Engine
        QTimer *timer = new QTimer(this);
        timer->setInterval(1000); // Generates data every 1 second

        connect(timer, &QTimer::timeout, this, [=]() {
            tickCount++;
            
            // Generate a random value between 20 and 80
            qreal value = QRandomGenerator::global()->bounded(20, 81);
            series->append(tickCount, value);

            // Dynamically manage the data size (Keep only the last 30 points)
            if (series->count() > 30) {
                series->removePoints(0, 1); // Remove the oldest data point
                axisX->setRange(tickCount - 30, tickCount); // Scroll the X axis forward
            }
        });

        // 7. Button Logic
        connect(toggleButton, &QPushButton::clicked, this, [=]() {
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
    int tickCount;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChartDashboard window;
    window.resize(600, 400);
    window.show();
    return app.exec();
}