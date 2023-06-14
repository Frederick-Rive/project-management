#ifndef TASKMODAL_H
#define TASKMODAL_H

#include <QWidget>
#include "projectobjects.h"

namespace Ui {
class TaskModal;
}

class TaskModal : public QWidget
{
    Q_OBJECT

public:
    explicit TaskModal(QWidget *parent = nullptr);
    ~TaskModal();

    void setTitle(std::string input);
    void setDescription(std::string input);
    void setStartDate(project::Date* input);
    void setEndDate(project::Date* input);
    void addUser(project::UserAccess* input);
    void removeUser(int input);

private:
    Ui::TaskModal *ui;
};

#endif // TASKMODAL_H
