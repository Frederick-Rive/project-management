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
  if (req.query.u && req.query.u != "{}") {
    var account = await findAccount(req.query.u, req.query.h);
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

app.post('/account', async (req, res) => {
  let body = JSON.parse(req.body);
  Account.findOne({ username: body.n })
  .exec()
  .then((accountResult) => {
    if (accountResult) {
      console.log("Name Taken");
      res.send("Name Taken");
    } else {
      var newAccount = new Account({
        _id: new mongoose.Types.ObjectId,
        username: body.n,
        password: body.h,
        email: null,
        projects: [mongoose.Types.ObjectId("6490b3a858f110c790acb03e")]
      });
      newAccount.save();
    }
  })  
  .catch((err) => {
    //if connection failed, return error message
    return ("Error: " + err);
  })
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

function findAccount(uName, pHash) { 
  return Account.findOne({ username: uName })
  .exec()
  .then((accountResult) => {
    console.log(pHash)
    if(accountResult.password == pHash){
      return (accountResult);
    } 
    return 0;
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