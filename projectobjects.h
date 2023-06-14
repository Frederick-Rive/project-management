#ifndef PROJECTOBJECTS_H
#define PROJECTOBJECTS_H
#include <iostream>
#include <vector>
#include <string>

namespace project {

    class Account;
    class UserAccess;
    class Log;
    class Task;
    class Project;

    class Date {
    private:
        int date, month, year;

    public:
        Date(int d, int m, int y);
        Date();
        int getYear();
        int getMonth();
        std::string getMonthString();
        std::string getShortMonthString();
        int getDate();
        std::string getDateString();
        bool setDate(int input);
        bool setMonth(int input);
        bool setYear(int input);
        int getWeekDay();
        int getWeek();
    };

    class Account {
    private:
        std::string id, username, password, profilePic, userEmail;
        std::vector<Project> projects;

    public:
        Account(std::string uName, std::string pHash, std::string email);
        std::string getID();
        std::string getUsername();
        bool checkUsername(std::string check);
        void setUsername(std::string uName);
        bool checkPassword(std::string check);
        bool resetPassword(std::string check, std::string input);
        std::string getProfilePic();
        std::string getUserEmail();
        int getProjectCount();
        Project getProject(int index);
    };

    class UserAccess : public Account {
    private:
        std::string accessID, level;
        std::vector<Log> logs;
        bool passwordResetRequested;

    public:
        UserAccess(std::string uName, std::string pHash, std::string email, std::string accessLevel);
        UserAccess(Account *account, std::string accessLevel);
        std::string getAccessID();
        std::string getAccessLevel();
        bool setLevel(std::string input);
        int getLogCount();
        Log getLog(int index);
    };

    class Log {
    private:
        std::string id, task, activity;
        Date date;

    public:
        Log(std::string t, std::string a);
        std::string getTask();
        std::string getActivity();
        Date getDate();
    };

    class Task {
    private:
        std::string id, name, description, state;
        Date startDate, endDate;
        std::vector<std::string> users;

    public:
        Task(std::string n, std::string d, Date* start, Date* end);
        std::string getName();
        bool setName(std::string input);
        std::string getDescription();
        bool setDescription(std::string input);
        Date getStartDate();
        Date getEndDate();
        bool setStartDate(Date input);
        bool setEndDate(Date input);
        int getUserCount();
        bool addUser(std::string input);
        bool removeUser(int input);
        std::string getState();
        bool setState(std::string input);
    };

    class Project {
    private:
        std::string id, name;
        std::vector<UserAccess> users;
        std::vector<Task> tasks;
        Date startDate, endDate;

    public:
        Project(std::string n, Date* s, Date* e);
        std::string getID();
        std::string getName();
        bool setName(std::string input);
        int getUserCount();
        UserAccess getUser(int input);
        int getTaskCount();
        Task getTask(int input);
        Date getStartDate();
        Date getEndDate();
        bool setStartDate(Date* input);
        bool setEndDate(Date* input);
        bool addUser(UserAccess input);
        bool removeUser(int input);
        bool addTask(Task input);
        bool removeTask(int input);
    };

    //std::string

}
#endif // PROJECTOBJECTS_H
