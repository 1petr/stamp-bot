var request = require('request');
var fs      = require('fs');
var mkdirp = require('mkdirp');

const { exec } = require('child_process');


module.exports.init = function(TOKEN,IsPhoto,idUser,messageChatId){
	var id_f = SizePhoto(IsPhoto);
	GetPhoto(TOKEN,id_f,idUser);

};

function SizePhoto(IsPhoto){
	var file_id = false;
  	for(id in IsPhoto){
   		if (IsPhoto[id].width > 700 && IsPhoto[id].width < 1000) {
      		file_id = IsPhoto[id].file_id;
    	}
  	}
 	if (!file_id) {
    	file_id = IsPhoto[1].file_id;
  	}
  	return file_id;
}


function GetPhoto(TOKEN,file_id,idUser){
	var str = "https://api.telegram.org/bot"+TOKEN+"/getfile?file_id="+file_id;
	request(str, function (error, response, body) {
		var body_ = JSON.parse(body)
      	var path_ = body_.result.file_path
      	var str_ = "https://api.telegram.org/file/bot"+TOKEN+"/"+path_;
     	var t = path_.split("/")
     	var url_img = "img/"+idUser+"/"+t[1]; //путь до фото
     	var dir = "img/"+idUser; //папка

     	request.get({url: str_, encoding: 'binary'}, function (err, response, body) {
         	fs.writeFile(url_img, body, 'binary', function(err) {
				if(err) console.log(err);
				else{
					openCV(url_img)
				}
			})         
      	});

	})
}
function openCV(url_img){
	exec('LD_LIBRARY_PATH=./lib && export LD_LIBRARY_PATH && ./opencv '+ url_img, (err, stdout, stderr) => {
	    if (err) {
	      console.log("Error while exec", err);
	      console.log("stderr while exec", stderr);
	    } else {
	        console.log("Success!!!");
	        console.log(`stdout: ${stdout}`);
	        console.log(`stderr: ${stderr}`);
	    }
	  });
}
