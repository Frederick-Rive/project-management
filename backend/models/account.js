const mongoose = require('mongoose');

//A schema is similar to a class, and looks like a UML diagram. It is the way that data will be stored in the database
const accountSchema = new mongoose.Schema({
    _id: mongoose.Schema.Types.ObjectId,
    username: String,
    password: String,
    profile_picture: String,
    user_email: String
}, {
    versionKey: false,
    strict: true,
    strictQuery: false
});

module.exports = mongoose.model('Account', accountSchema, 'Account');