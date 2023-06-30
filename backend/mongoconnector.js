//header files
const mongoose = require("mongoose");
const express = require("express");
const app = express();
const bodyParser = require('body-parser');
app.use(bodyParser.json({ limit: '5mb' }));
app.use(bodyParser.urlencoded({ limit: '5mb', extended: true }));
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
  if (req.query.u && req.query.u != "{}") {
    var account = await findAccount(req.query.u);
    if (account) {
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

app.post('/account', (req, res) => {
  var newAccount = new Account({
    _id: new mongoose.Types.ObjectId,
    username: req.body.n,
    password: req.h,
});
  console.log(newAccount);
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
  res.send(jsonToString(user));
});

app.listen(6069, () => {
  console.log("listening on port 6069");
});

function findAccount(uName) { 
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
  console.log(user._id);
  return Task.findOne({_id: id, users: user._id})
  .exec()
  .then((taskResult) => {
    if (taskResult != null) {
      return jsonToString(taskResult);
    } else {
      return taskResult;
    }
  })
  .catch((err) => {
    return ("Error: " + err);
  })
}

function jsonToString(input) {
  var rtrn = "";
  for (key of Object.keys(Object.values(input)[2])) {
    rtrn += (key + ":" + String(input[key]) + "|");
  }
  rtrn = rtrn.slice(0, -1);
  return rtrn;
}