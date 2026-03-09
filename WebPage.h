// WebPages.h
#pragma once
#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi / web server
// const char* ssid = "PetchaiHotspot";
// const char* password = "p@ssw0rd";
const char* ssid = "Home Mesh M5";
const char* password = "wwxt-rhj9-237y";

WebServer server(80);

// HTML page function
String htmlPage() {
  return R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>Splint Monitor</title>
    <meta charset="utf-8">
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <style>
      body { font-family: Arial; text-align:center; margin-top:30px; }
      .value { font-size:1.1em; margin:12px; }
      canvas { max-width: 800px; height: 300px; margin: 20px auto; display: block; }
      .spacer { margin-top: 20px; }
    </style>
  </head>
  <body>
    <h1>Wrist Splint Monitor</h1>

    <div class="value">EMG: <span id="EMG">0 µV</span></div>
    <div class="value">Threshold: <span id="thresh">0 µV</span></div>
    <div class="value">Pressure: <span id="fsr">0 kPa</span></div>
    <div class="spacer"></div>
    <div class="value">Action: <span id="status">idle</span></div>

    <canvas id="emgChart"></canvas>
    <canvas id="pressureChart"></canvas>

    <script>
      const emgCtx = document.getElementById('emgChart').getContext('2d');
      const pressureCtx = document.getElementById('pressureChart').getContext('2d');

      let elapsedTime = 0;
      let startTime = Date.now();

      const emgChart = new Chart(emgCtx, {
        type: 'line',
        data: {
          labels: [],
          datasets: [
            { label: 'EMG (µV)', data: [], borderColor: 'blue', borderWidth: 1, fill: false, pointRadius: 0 },
            { label: 'Threshold (µV)', data: [], borderColor: 'red', borderWidth: 1, fill: false, pointRadius: 0 }
          ]
        },
        options: {
          animation: false,
          scales: {
            x: {
              type: 'linear',
              title: {
                display: true,
                text: 'Time (s)'
              },
              ticks: {
                stepSize: 1
              }
            },
            y: {
              beginAtZero: true,
              title: {
                display: true,
                text: 'Amplitude (µV)'
              }
            }
          },
          plugins: {
            legend: { position: 'top' }
          }
        }
      });

      const pressureChart = new Chart(pressureCtx, {
        type: 'line',
        data: {
          labels: [],
          datasets: [
            { label: 'Pressure (kPa)', data: [], borderColor: 'green', borderWidth: 1, fill: false, pointRadius: 0 }
          ]
        },
        options: {
          animation: false,
          scales: {
            x: {
              type: 'linear',
              title: {
                display: true,
                text: 'Time (s)'
              },
              ticks: {
                stepSize: 1
              }
            },
            y: {
              beginAtZero: true,
              title: {
                display: true,
                text: 'Pressure (kPa)'
              }
            }
          },
          plugins: {
            legend: { position: 'top' }
          }
        }
      });

      async function fetchData() {
        const res = await fetch('/data');
        const json = await res.json();

        document.getElementById('EMG').innerText = json.EMG.toFixed(4) + " µV";
        document.getElementById('thresh').innerText = json.threshold.toFixed(4) + " µV";
        document.getElementById('fsr').innerText = json.fsr.toFixed(4) + " kPa";
        document.getElementById('status').innerText = json.status;

        const elapsedTime = (Date.now() - startTime) / 1000; // seconds
        
        // Update EMG chart
        emgChart.data.labels.push(elapsedTime);
        emgChart.data.datasets[0].data.push(json.EMG);
        emgChart.data.datasets[1].data.push(json.threshold);
        if (emgChart.data.labels.length > 50) {
          emgChart.data.labels.shift();
          emgChart.data.datasets.forEach(d => d.data.shift());
        }
        emgChart.update();

        // Update Pressure chart
        pressureChart.data.labels.push(elapsedTime);
        pressureChart.data.datasets[0].data.push(json.fsr);
        if (pressureChart.data.labels.length > 50) {
          pressureChart.data.labels.shift();
          pressureChart.data.datasets[0].data.shift();
        }
        pressureChart.update();
      }

      setInterval(fetchData, 200);
      fetchData();
    </script>
  </body>
  </html>
  )rawliteral";
}