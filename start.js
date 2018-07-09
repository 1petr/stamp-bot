// var TelegramBot = require('node-telegram-bot-api');
// var request = require('request');
// var fs      = require('fs');
// var mkdirp = require('mkdirp');
// /**/
var config = require("./config/confog.js")
// var btn = require("./button.js")
// var M_photo = require("./models/model.photo.js")
// var M_dir = require("./models/model.dir.js")

// /**/
// var bot = new TelegramBot(config.TOKEN, config.botOptions);
// /*Формирование кнопок*/
// var options = {
//     reply_markup: JSON.stringify({
//       inline_keyboard: [btn.btn]
//     })
// };
// var options_del = {
//     reply_markup: JSON.stringify({
//       inline_keyboard: [btn.btn_del]
//     })
// };

/*
bot.on('message', function(msg) {

    var messageChatId = msg.chat.id;    
    var messageText = msg.text;
    var idUser = msg.from.id;
    var IsPhoto = msg.photo;

    // console.log("Пришло сообщение")
    // console.log("messageChatId = ",messageChatId)
    // console.log("messageText = ",messageText)
    // console.log("idUser = ",idUser)

	M_dir.init(idUser);


   	if (IsPhoto) {
      M_photo.init(config.TOKEN,IsPhoto,idUser,messageChatId);
   	}else{
      Init_Button(messageChatId)
   	}

    
})


function Init_Button(messageChatId){
  fs.readdir("img/"+messageChatId, function(err, content){
      if (err) {
          bot.sendMessage(messageChatId, 'Добавьте вашу печать.');
      } else {
          bot.sendMessage(messageChatId, 'Выберите действие:', options);
      }
  })
}


bot.on('callback_query', function(msg) {    
    var messageChatId = msg.message.chat.id;
    var idUser = msg.from.id;
    var NameButton = msg.data
    var dir = "img/"+idUser+"/signet";
    var dir_ = "img/"+idUser;

    if (NameButton ==='showAll') {      
       if (fs.existsSync(dir)) {
	        fs.readdir(dir, function(error, items) {
	            if(error) {
	                console.log(error);
	            } 
	            else {
	            	if (items.length == 0) {
	              		bot.sendMessage(messageChatId, 'У Вас нет печатей.');
	           		}else{
	              		for (let i =0; i<items.length; i++) {
	                		fs.readFile("img/"+idUser+"/signet/"+items[i], function(err, content) {
	                    	bot.sendPhoto(idUser, content, {caption: items[i]});
	                	})
	              	}
	            }
            
            }
        })
       	}else{
        	bot.sendMessage(messageChatId, 'У Вас нет печатей.');
       	}
        
    }
    else if (NameButton ==='Delet') {
    	fs.readdir(dir, function(error, items) {
	        if(error) {
	            console.log(error);
	        } 
	        else {
	        	if (items.length == 0) {bot.sendMessage(messageChatId, 'У Вас нет печатей.');}
	        	else{bot.sendMessage(messageChatId, 'Выберите удаление:', options_del);}	        	
	        }
	    })       
    }
    else if (NameButton ==='DelAll') {
        fs.readdir(dir, function(error, items) {
            if(error) {
                console.log(error);
            } 
            else {
              for (let i =0; i<items.length; i++) {
                fs.unlink("img/"+idUser+"/signet/"+items[i],function (err) {
                  if (err) console.error(err)
                })
              }
            }
            bot.sendMessage(messageChatId, 'Все печати удалены');
        })      
    }
    else if (NameButton ==='DelOne') {
        fs.readdir(dir, function(error, items) {
            if(error) {
                console.log(error);
            } 
            else {
              var btn_photo = new Array()
              for (let i =0; i<items.length; i++) {
                btn_photo.push({ text: 'Название: '+items[i], callback_data: items[i] })
                
              }
              var options_ph = {
                  reply_markup: JSON.stringify({
                    inline_keyboard: [btn_photo]
                  })
              };
              bot.sendMessage(messageChatId, 'Выберите Название:', options_ph);
            }
        }) 
    }
    else {
      fs.unlink("img/"+idUser+"/signet/"+NameButton,function (err) {
        if (err) console.error(err)
      })
      bot.sendMessage(messageChatId, 'Картинка: '+NameButton+' Удалена');
    }
})

*/

var TelegramBot=require('node-telegram-bot-api');
var bot=new TelegramBot(config.TOKEN, config.botOptions);
// var notes=[];
// bot.onText(/\/напомни (.+) в (.+)/,function(msg,match){
//   // console.log("msg ==>>>>",msg)
//   // console.log("match ==>>>>",match)
//   var userId=msg.from.id;
//   var text=match[1];
//   var time=match[2];
//   notes.push({'uid':userId,'time':time,'text':text});
//   bot.sendMessage(userId,'Отлично! Я обязательно напомню, если не сдохну :)');
//   console.log("notes ==>>>>",notes)
// });


bot.on('message', function(msg) {

    var messageChatId = msg.chat.id;    
    var messageText = msg.text;
    var idUser = msg.from.id;
    var IsPhoto = msg.photo;

    // console.log("Пришло сообщение")
    // console.log("messageChatId = ",messageChatId)
    // console.log("messageText = ",messageText)
    // console.log("idUser = ",idUser)


    

    if (IsPhoto) {
      
    }else{
      
    }

    
})



// setInterval(function(){
//   console.log("setInterval=>>>")
//   for(var i=0;i<notes.length;i++){
//     var curDate=new Date().getHours()+':'+new Date().getMinutes();
//     console.log("times=>>>",curDate)
//     console.log("i=>>>",notes[i])
//     if(notes[i]['time']==curDate){
//       console.log(" if times=>>>",notes[i]['time']==curDate)
//       bot.sendMessage(notes[i]['uid'],'Напоминаю, что вы должны: '+notes[i]['text']+' сейчас.');
//       notes.splice(i,1);
//     }
//   }
// },1000);