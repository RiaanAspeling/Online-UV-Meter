// Get current sensor readings when the page loads  
window.addEventListener('load', getReadings);

// Create UVIndex Gauge
var gaugeuvindex = new LinearGauge({
  renderTo: 'gauge-uvindex',  units: "UV Index",
  width: 120, height: 400,
  minValue: 0, maxValue: 20,
  valueDec: 2, valueInt: 2,
  colorValueBoxRect: "#049faa", colorValueBoxRectEnd: "#049faa", colorValueBoxBackground: "#f1fbfc",
  majorTicks: ["0","2","4","6","8","10","12","14","16","18","20"],
  minorTicks: 2,
  highlights: [ { "from": 0, "to": 3, "color": "rgba(0, 200, 0, .75)" },
                { "from": 3, "to": 6, "color": "rgba(200, 200, 0, .75)" },
                { "from": 6, "to": 8, "color": "rgba(200, 120, 0, .75)" },
                { "from": 8, "to": 11, "color": "rgba(200, 0, 0, .75)" }, 
                { "from": 11, "to": 20, "color": "rgba(120, 0, 200, .75)" },],
  colorPlate: "#fff", colorBarProgress: "#ff0000", colorBarProgressEnd: "#00ff00",
  borderShadowWidth: 0, borders: false,
  needleType: "arrow", needleWidth: 4, needleCircleSize: 2, needleCircleOuter: true, needleCircleInner: false,
  animationDuration: 1500, animationRule: "elastic",
  barWidth: 10,
}).draw();
  
// Create Lux Gauge
var gaugelux = new LinearGauge({
  renderTo: 'gauge-lux',
  units: "Lux",
  width: 120, height: 400,
  minValue: 0, maxValue: 140000,
  valueDec: 2, valueInt: 2,
  colorValueBoxRect: "#049faa", colorValueBoxRectEnd: "#049faa", colorValueBoxBackground: "#f1fbfc",
  majorTicks: ["0","20000","40000","60000","80000","100000", "120000", "140000"],
  minorTicks: 2,
  highlights: [ { "from": 0, "to": 1000, "color": "rgba(50, 50, 50, .75)" },
                { "from": 1000, "to": 10000, "color": "rgba(75, 75, 75, .75)" },
                { "from": 10000, "to": 25000, "color": "rgba(100, 100, 100, .75)" },
                { "from": 25000, "to": 50000, "color": "rgba(200, 200, 200, .75)" }, 
                { "from": 50000, "to": 100000, "color": "rgba(240, 240, 240, .75)" },
                { "from": 100000, "to": 140000, "color": "rgba(255, 255, 255, .75)" },],
  colorPlate: "#fff", colorBarProgress: "#f0f0f0", colorBarProgressEnd: "#101010",
  borderShadowWidth: 0, borders: false,
  needleType: "arrow", needleWidth: 4, needleCircleSize: 2, needleCircleOuter: true, needleCircleInner: false,
  animationDuration: 1500, animationRule: "elastic",
  barWidth: 10,
}).draw();

// Create W/m2 Gauge
var gaugewm2 = new LinearGauge({
  renderTo: 'gauge-wm2',
  units: "W/m2",
  width: 120, height: 400,
  minValue: 0, maxValue: 2000,
  valueDec: 2, valueInt: 2,
  colorValueBoxRect: "#049faa", colorValueBoxRectEnd: "#049faa", colorValueBoxBackground: "#f1fbfc",
  majorTicks: ["0","200","400","600","800","1000","1200","1400","1600","1800","2000"],
  minorTicks: 2,
  highlights: [ { "from": 0, "to": 100, "color": "rgba(50, 50, 50, .75)" },
                { "from": 100, "to": 200, "color": "rgba(75, 75, 75, .75)" },
                { "from": 200, "to": 400, "color": "rgba(100, 100, 100, .75)" },
                { "from": 400, "to": 600, "color": "rgba(200, 200, 200, .75)" }, 
                { "from": 600, "to": 800, "color": "rgba(240, 240, 240, .75)" },
                { "from": 800, "to": 2000, "color": "rgba(255, 255, 255, .75)" },],
  colorPlate: "#fff", colorBarProgress: "#f0f0f0", colorBarProgressEnd: "#101010",
  borderShadowWidth: 0, borders: false,
  needleType: "arrow", needleWidth: 4, needleCircleSize: 2, needleCircleOuter: true, needleCircleInner: false,
  animationDuration: 1500, animationRule: "elastic",
  barWidth: 10,
}).draw();

// Create °C Gauge
var gaugec = new LinearGauge({
  renderTo: 'gauge-c',
  units: "Celcius",
  width: 120, height: 400,
  minValue: -10, maxValue: 60,
  valueDec: 2, valueInt: 2,
  colorValueBoxRect: "#049faa", colorValueBoxRectEnd: "#049faa", colorValueBoxBackground: "#f1fbfc",
  majorTicks: ["-10","0","10","20","30","40","50","60"],
  minorTicks: 2,
  highlights: [ { "from": -10, "to": -5, "color": "rgba(0, 0, 150, .75)" },
                { "from": -5, "to": 0, "color": "rgba(0, 75, 150, .75)" },
                { "from": 0, "to": 10, "color": "rgba(0, 150, 150, .75)" },
                { "from": 10, "to": 15, "color": "rgba(0, 200, 200, .75)" }, 
                { "from": 15, "to": 20, "color": "rgba(0, 150, 0, .75)" },
                { "from": 20, "to": 30, "color": "rgba(150, 200, 0, .75)" },
                { "from": 30, "to": 35, "color": "rgba(200, 200, 0, .75)" },
                { "from": 35, "to": 60, "color": "rgba(200, 0, 0, .75)" },],
  colorPlate: "#fff", colorBarProgress: "#CC0000", colorBarProgressEnd: "#0000aa",
  borderShadowWidth: 0, borders: false,
  needleType: "arrow", needleWidth: 4, needleCircleSize: 2, needleCircleOuter: true, needleCircleInner: false,
  animationDuration: 1500, animationRule: "elastic",
  barWidth: 10,
}).draw();

// Create Dew°C Gauge
var gaugedewc = new LinearGauge({
  renderTo: 'gauge-dewc',
  units: "Celcius",
  width: 120, height: 400,
  minValue: -10, maxValue: 60,
  valueDec: 2, valueInt: 2,
  colorValueBoxRect: "#049faa", colorValueBoxRectEnd: "#049faa", colorValueBoxBackground: "#f1fbfc",
  majorTicks: ["-10","0","10","20","30","40","50","60"],
  minorTicks: 2,
  highlights: [ { "from": -10, "to": -5, "color": "rgba(0, 0, 150, .75)" },
                { "from": -5, "to": 0, "color": "rgba(0, 75, 150, .75)" },
                { "from": 0, "to": 10, "color": "rgba(0, 150, 150, .75)" },
                { "from": 10, "to": 15, "color": "rgba(0, 200, 200, .75)" }, 
                { "from": 15, "to": 20, "color": "rgba(0, 150, 0, .75)" },
                { "from": 20, "to": 30, "color": "rgba(150, 200, 0, .75)" },
                { "from": 30, "to": 35, "color": "rgba(200, 200, 0, .75)" },
                { "from": 35, "to": 60, "color": "rgba(200, 0, 0, .75)" },],
  colorPlate: "#fff", colorBarProgress: "#CC0000", colorBarProgressEnd: "#0000aa",
  borderShadowWidth: 0, borders: false,
  needleType: "arrow", needleWidth: 4, needleCircleSize: 2, needleCircleOuter: true, needleCircleInner: false,
  animationDuration: 1500, animationRule: "elastic",
  barWidth: 10,
}).draw();

// Create humidity Gauge
var gaugehumidity = new LinearGauge({
  renderTo: 'gauge-humidity',
  units: "%",
  width: 120, height: 400,
  minValue: 0, maxValue: 100,
  valueDec: 2, valueInt: 2,
  colorValueBoxRect: "#049faa", colorValueBoxRectEnd: "#049faa", colorValueBoxBackground: "#f1fbfc",
  majorTicks: ["0","10","20","30","40","50","60","70","80","90","100"],
  minorTicks: 2,
  highlights: [ { "from": 75, "to": 100, "color": "rgba(100, 100, 200, .75)" },],
  colorPlate: "#fff", colorBarProgress: "#f0f0f0", colorBarProgressEnd: "#101010",
  borderShadowWidth: 0, borders: false,
  needleType: "arrow", needleWidth: 4, needleCircleSize: 2, needleCircleOuter: true, needleCircleInner: false,
  animationDuration: 1500, animationRule: "elastic",
  barWidth: 10,
}).draw();

// gaugeuvindex.value = 10; //myObj.uvindex;
// gaugelux.value = 10000; //myObj.lux;
// gaugewm2.value = 1000; //myObj.wm2;
// gaugec.value = 25; //myObj.tempC;
// gaugedewc.value = 12.5; //myObj.dewTempC;
// gaugehumidity.value = 50; //myObj.humidity;

// Function to get current readings on the webpage when it loads for the first time
function getReadings(){
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var myObj = JSON.parse(this.responseText);
      console.log(myObj);
      gaugeuvindex.value = myObj.uvindex;
      gaugelux.value = myObj.lux;
      gaugewm2.value = myObj.wm2;
      gaugec.value = myObj.tempC;
      gaugedewc.value = myObj.dewTempC;
      gaugehumidity.value = myObj.humidity;
    }
  }; 
  xhr.open("GET", "/readings", true);
  xhr.send();
}

if (!!window.EventSource) {
  var source = new EventSource('/events');
  
  source.addEventListener('open', function(e) {
    console.log("Events Connected");
  }, false);

  source.addEventListener('error', function(e) {
    if (e.target.readyState != EventSource.OPEN) {
      console.log("Events Disconnected");
    }
  }, false);
  
  source.addEventListener('message', function(e) {
    console.log("message", e.data);
  }, false);
  
  source.addEventListener('new_readings', function(e) {
    console.log("new_readings", e.data);
    var myObj = JSON.parse(e.data);
    console.log(myObj);
    gaugeuvindex.value = myObj.uvindex;
    gaugelux.value = myObj.lux;
    gaugewm2.value = myObj.wm2;
    gaugec.value = myObj.tempC;
    gaugedewc.value = myObj.dewTempC;
    gaugehumidity.value = myObj.humidity;
  }, false);
}