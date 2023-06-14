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
//const Task = require('./models/task.js');
//const Project = require('./models/project.js');

//gets an account based on its ID
app.get('/account', async (req, res) => {
  let accountResult = "FUCK";
  if (req.query.u && req.query.u != "{}") {
    if (req.query.u) {
      var account = await findAccount(req.query.u);
      res.send(account);
    }
    else {
      res.send("FAIL");
    }
  } else {
    var account = await findAccount();
    res.send(account);
  }
});

app.post('/account', (req, res) => {
  console.log(req);
  var newAccount = new Account({
    _id: new mongoose.Types.ObjectId,
    username: req.body.n,
    password: req.h,
    description: req.body.description,
    is_admin: req.body.is_admin
});
  console.log(newAccount);
});

app.listen(6069, () => {
  console.log("listening on port 6069");
});

function findAccount(uName) { 
  return Account.findOne({ username: uName })
  .exec()
  .then((accountResult) => {
    console.log(accountResult);
    return accountResult;
  })
  .catch((err) => {
    return ("Error: " + err);
  })
}

function findAccount() { 
  return Account.findOne()
  .exec()
  .then((accountResult) => {
    console.log(accountResult)
    return accountResult;
  })
  .catch((err) => {
    return ("Error: " + err);
  })
}