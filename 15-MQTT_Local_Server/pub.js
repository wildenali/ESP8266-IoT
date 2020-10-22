// MQTT publisher
var mqtt = require('mqtt')
var client = mqtt.connect('mqtt://localhost:1883')
var topic = 'initopic'
var message = '0'
var nambah = 0;

client.on('connect', ()=>{
    setInterval(()=>{
        nambah++;
        if (nambah >= 10) {
            nambah = 0
        }
        message = nambah.toString();
        client.publish(topic, message)
        console.log('Message sent!', message)
    }, 100)
})