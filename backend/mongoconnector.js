//header files
const mongoose = require("mongoose");
const express = require("express");
const app = express();
const bodyParser = require('body-parser');
app.use(bodyParser.json({ limit: '20mb' }));
app.use(bodyParser.text({ limit: '20mb' }));
app.use(bodyParser.urlencoded({ limit: '20mb', extended: true }));
const cors = require('cors');
app.use(cors());
const multer = require('multer');
const storage = multer.diskStorage({
    destination: (req, file, cb) => {
        cb(null, uploads)
    },
    filename: (req, file, cb) => {
        cb(null, file.fieldname + '-' + Date.now)
    }
});
const upload = multer({ storage: storage });
const bcrypt = require('bcrypt');
const salt = 10;

//connect to the database
mongoose.connect('mongodb+srv://Freddie-RIve:LGmw1XzE4hhnzgg7@project-management.h6h4c36.mongodb.net/?retryWrites=true&w=majority')
    .then(() => 
      console.log("Connection Succeeded"))
    .catch((err) => {
      console.log("Connection Error: " + err)
    });

const Account = require('./models/account.js');
//const UserAccess = require('./models/useraccess.js');
//const Log = require('./models/log.js');
const Task = require('./models/task.js');   
const Project = require('./models/project.js');

var user = new Account();

//gets an account based on its ID
app.get('/account', async (req, res) => {
  console.log(req.query);
  if (req.query.u && req.query.u != "{}") {
    var account = await findAccount(req.query.u, req.query.h);
    console.log(account);
    if (account) {
      console.log('logged in');
      user = account;
      res.send("1");
    } else {
      res.send("0");
    }
  }
  else {
    res.send("0");
  }
});

app.get('/task', async (req, res) => {
  if (req.query.id && req.query.id != "{}") {
    var task = await findTask(req.query.id);
    if (task) {
        res.send(task);
    } else {
      res.send("0");
    }
  }
  else {
    var task = await findTask();
    console.log(task);
    res.send("0");
  }
});

app.get('/usertasks', async (req, res) => {
  var tasks = await findUserTasks();
  let rtrn = "";
  for (task of tasks) {
    rtrn += task.id + "|";
  }
  rtrn = rtrn.slice(0, -1);
  res.send(rtrn);
});

app.post('/task', async (req, res) => {
  let body = JSON.parse(req.body);
  var newTask = new Task({
    _id: new mongoose.Types.ObjectId,
    name: body.n,
    description: body.d,
    state: body.s,
    startDate: body.sd,
    endDate: body.ed,
    users: body.u
  })
  newTask.save();
  res.send('1');
})

app.post('/account', async (req, res) => {
  let body = JSON.parse(req.body);
  console.log(body);
  var accTest = await checkAccount(req.query.u);
  if (accTest) {
    console.log("Name Taken");
    res.send('0');
  } else {
      var newAccount = new Account({
        _id: new mongoose.Types.ObjectId,
        username: body.n,
        password: body.h,
        email: null,
      });
      console.log(newAccount);
      newAccount.save();
      res.send('1');
    }
});

app.get('/project', async (req, res) => {
  if (req.query.id && req.query.id != "{}") {
    var project = await findProject(req.query.id);
    if (project) {
      res.send(project);
    } else {
      res.send("0");
    }
  }
  else {
    var task = await findTask();
    console.log(task);
    res.send("0");
  }
});

//gets an account based on its ID
app.get('/user', async (req, res) => {
  console.log(typeof user);
  if (user && user != '0') {
    res.send(jsonToString(user));
  } else {
    res.send(user);
  }
});

app.listen(6069, () => {
  console.log("listening on port 6069");
});

function findAccount(uName, pHash) {
  return Account.findOne({ username: uName, password: pHash })
  .exec()
  .then((accountResult) => {
    console.log(accountResult);
    console.log("aaa");
    return (accountResult);
  })
  .catch((err) => {
    return ("Error: " + err);
  })
}

function checkAccount(uName) {
  return Account.findOne({ username: uName })
  .exec()
  .then((accountResult) => {
    return (accountResult);
  })
  .catch((err) => {
    return ("Error: " + err);
  })
}

function findAccountNoUname() { 
  return Account.findOne()
  .exec()
  .then((accountResult) => {
    return jsonToString(accountResult);
  })
  .catch((err) => {
    return ("Error: " + err);
  })
}

function findTask(id) { 
  //queries databse for task
  return Task.findOne(qObj(id))
  .exec()
  .then((taskResult) => {
    //if a task is returned, send  task to application
    if (taskResult != null) {
      return jsonToString(taskResult);
    } else {
      //otherwise, send a 0 to show that nothing was returned
      return "0";
    }
  })
  .catch((err) => {
    //if connection failed, return error message
    return ("Error: " + err);
  })
}

function findUserTasks() {
  return Task.find({"users": user._id})
  .exec()
  .then((taskResult) => {
    return taskResult;
  })
  .catch((err) => {
    return ("Error: " + err);
  })
}

function qObj (id) {
  let rtrn = {};
  rtrn["_id"] = id;
  rtrn["users"] = user._id;
  return rtrn;
}

function jsonToString(input) {
  var rtrn = "";
  for (key of Object.keys(Object.values(input)[2])) {
    rtrn += (key + ":" + String(input[key]) + "|");
  }
  rtrn = rtrn.slice(0, -1);
  return rtrn;
}