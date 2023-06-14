#ifndef KANBANWIDGET_H
#define KANBANWIDGET_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class KanbanWidget;
}

class KanbanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KanbanWidget(std::string name, QWidget *parent = nullptr);
    ~KanbanWidget();
private:
    Ui::KanbanWidget *ui;

    void mousePressEvent(QMouseEvent *event);
};

#endif // KANBANWIDGET_H
