var request = require('request');
var fs      = require('fs');
var mkdirp = require('mkdirp');



module.exports.init = function(idUser){
	var dir = "img/"+idUser;
  var dir_ = dir+"/signet"
  if (!fs.existsSync(dir)) {
    CreateDir_user(dir)
    if (!fs.existsSync(dir_)) {
      CreateDir_user(dir_)
    }
  }
  else{
    if (!fs.existsSync(dir_)) {
      CreateDir_user(dir_)
    }
  }

};

function CreateDir_user(dir){
  mkdirp(dir, function (err) {
    if (err) console.error(err)
    else{}
  })
}
function CreateDir_signet(dir_){  
  mkdirp(dir_, function (err) {
    if (err) console.error(err)
    else{}
  })
}


