#include "projectobjects.h"
#include <ctime>
#include <chrono>

using namespace project;

Date::Date(int d, int m, int y) {
    this->date = d;
    this->month = m;
    this->year = y;
}
Date::Date() {
    std::time_t current = std::time(0);
    std::tm* local = std::localtime(&current);

    this->date = local->tm_mday;
    this->month = local->tm_mon + 1;
    this->year = local->tm_year + 1900;
}
int Date::getYear() { return this->year; }
int Date::getMonth() { return this->month; }
std::string Date::getMonthString() {
    std::string months[12] = {"January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    return months[this->month - 1];
}
std::string Date::getShortMonthString() {
    std::string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    return months[this->month - 1];
}
int Date::getDate() { return this->date; }
std::string Date::getDateString() {
    std::string rtrn;
    rtrn += std::to_string(this->date) + "/" + std::to_string(this->month) + "/" + std::to_string(this->year);
    return rtrn;
}
bool Date::setDate(int input) { this->date = input; return true; }
bool Date::setMonth(int input) { this->month = input; return true; }
bool Date::setYear(int input) { this->year = input; return true; }
int Date::getWeekDay() { return 0; }
int Date::getWeek() { return 0; }

Account::Account(std::string uName, std::string pHash, std::string email) {
    this->username = uName;
    this->password = pHash;
    this->userEmail = email;

}
std::string Account::getID() { return this->id; }
std::string Account::getUsername() { return this->username; }
bool Account::checkUsername(std::string check) { return check == this->username; }
void Account::setUsername(std::string uName) { this->username = uName; }
bool Account::checkPassword(std::string check) { return check == this->password; }
bool Account::resetPassword(std::string check, std::string input) { if (check == this->password) { this->password = input; return true; } return false; }
std::string Account::getProfilePic() { return this->profilePic; }
std::string Account::getUserEmail() { return this->userEmail; }
int Account::getProjectCount() { return this->projects.size(); }
Project Account::getProject(int index) { return this->projects[index]; }

UserAccess::UserAccess(std::string uName, std::string pHash, std::string email, std::string accessLevel) : Account(uName, pHash, email) {
    this->level = accessLevel;
}
UserAccess::UserAccess(Account *account, std::string accessLevel) : Account(*account) {
    this->level = accessLevel;
}
std::string UserAccess::getAccessID() { return this->accessID; }
std::string UserAccess::getAccessLevel() { return this->level; }
bool UserAccess::setLevel(std::string input) { this->level = input; return true; }
int UserAccess::getLogCount() { return this->logs.size(); }
Log UserAccess::getLog(int index) { return this->logs[index];}

Log::Log(std::string t, std::string a) {
    this->task = t;
    this->activity = a;


}
std::string Log::getTask() { return this->task; }
std::string Log::getActivity() { return this->activity; }
Date Log::getDate() { return this->date; }


Task::Task(std::string i, std::string n, std::string d, Date *start, Date *end) {
    this->id = i;
    this->name = n;
    this->description = d;
    this->startDate = *start;
    this->endDate = *end;
}
std::string Task::getName() { return this->name; }
bool Task::setName(std::string input) { this->name = input; return true; }
std::string Task::getDescription() { return this->description; }
bool Task::setDescription(std::string input) { this->description = input; return true; }
Date Task::getStartDate() { return this->startDate; }
Date Task::getEndDate() { return this->endDate; }
bool Task::setStartDate(Date input) { this->startDate = input; return true; }
bool Task::setEndDate(Date input) { this->endDate = input; return true; }
int Task::getUserCount() { return this->users.size(); }
bool Task::addUser(std::string input) { this->users.push_back(input); return true; }
bool Task::removeUser(int input) {
    return true;
}
std::string Task::getState() { return this->state; }
bool Task::setState(std::string input) { this->state = input; return true; }

Project::Project(std::string n, Date* s, Date* e) {
    this->id = "Temp";
    this->name = n;
    this->startDate = *s;
    this->endDate = *e;
}
std::string Project::getID() { return this->id; }
std::string Project::getName() { return this->name; }
bool Project::setName(std::string input) { this->name = input; return true; }
int Project::getUserCount() { return this->users.size(); }
UserAccess Project::getUser(int input) { return this->users[input]; }
int Project::getTaskCount() { return this->tasks.size(); }
Task Project::getTask(int input) { return this->tasks[input]; }
Date Project::getStartDate() { return this->startDate; }
Date Project::getEndDate() { return this->endDate; }
bool Project::setStartDate(Date* input) { this->startDate = *input; return true; }
bool Project::setEndDate(Date* input) { this->endDate = *input; return true; }
bool Project::addUser(UserAccess input) { users.push_back(input); return true; }
bool Project::removeUser(int input) {
    std::vector<UserAccess> rtrn;
    for (int i = 0; i < (int)users.size(); i++) {
        if (i != input) {
            rtrn.push_back(users[i]);
        }
    }
    users = rtrn;
    return true;
}
bool Project::addTask(Task input) { tasks.push_back(input); return true; }
bool Project::removeTask(int input) {
    std::vector<Task> rtrn;
    for (int i = 0; i < (int)tasks.size(); i++) {
        if (i != input) {
            rtrn.push_back(tasks[i]);
        }
    }
    tasks = rtrn;
    return true;
}

