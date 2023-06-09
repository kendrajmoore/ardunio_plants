
<a name="readme-top"></a>
<!-- PROJECT SHIELDS -->
[![MIT License][license-shield]][license-url]
<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/kendrajmoore/ardunio_plants/edit/main/README.md">
    <img src="https://i.ibb.co/QP2QXhB/Pngtree-cute-green-small-plant-aloe-4651505.png" alt="Logo" width="200" height="200">
  </a>

  <h3 align="center">IoT Plant Monitoring System</h3>

  <p align="center">
    An IoT Plant Monitoring System that allows you to review your plants health stats from anywhere in the world using an ESP32!
    <br />
    <a href="https://kendrajmoore.github.io/ardunio_plants"><strong>Explore the docs»</strong></a>
    <br />
    <br />
    <a href="https://nodereddash.smartplant.live/ui">View Demo</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>


<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)

Plant monitoring has become an increasingly prominent environmental measurement in climate change, water resource forecasting, land stability, and crop management. Current technologies in soil monitoring are used to help farmers understand their plant health and make decisions about how to care for their crops. These existing technologies, however, rely on proprietary sensors and lack the ability to onboard or customize new types of sensors. The platform will offer (1) seamless sensor integration, (2) storage of time series data, (3) monitoring and visualizations on live data. 


<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With


* [![Node-Red][Node-Red]][Node-url]
* [![Arduino][Arduino]][Arduino-url]
* [![InfluxDB][InfluxDB]][Influx-url]
* [![Digital Ocean][Digital Ocean]][Digital-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started



### Prerequisites

To get started with the project git clone the repo
  ```sh
  git clone https://github.com/kendrajmoore/ardunio_plants.git
  ```

Download Arduino IDE and connect your ESP32 to your computer

Upload the code into the IDE, replace the placeholder text with your SSID, wifi password

Compile and upload the code to your ESP32


### Installation

To complete the hardware component of this project you need
* ESP32 or ESP8622
* Breadboard
* DHT11
* Soil Moisture Sensor
* USB micro-B Cable 6 Feet
* 2 packs of jumper wires
* Male Headers Pack Break Away
* Optional 10k Ohm Resistor

[![Wiring Diagram][wiring]]()


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

You can use this tool to monitor your plants' temperature, humidity, and soil moisture on your computer or phone.
<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [Random Nerd Tutorials](https://randomnerdtutorials.com/)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
<!-- MARKDOWN LINKS & IMAGES -->
[product-screenshot]: https://i.ibb.co/zbSTMhQ/Screenshot-2023-04-28-at-10-25-52-AM.png
[wiring]: https://i.ibb.co/z474hY4/Screenshot-2023-04-26-at-11-39-41-AM.png
[Node-Red]: https://img.shields.io/badge/Node--Red-8F0000?style=for-the-badge&logo=nodered&logoColor=white
[Node-url]: https://nodered.org/
[Arduino]: 	https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white
[Arduino-url]: https://www.arduino.cc/en/software
[InfluxDB]: https://img.shields.io/badge/InfluxDB-22ADF6?style=for-the-badge&logo=InfluxDB&logoColor=white
[Influx-url]: https://vuejs.org/
[Digital Ocean]: https://img.shields.io/badge/Digital_Ocean-0080FF?style=for-the-badge&logo=DigitalOcean&logoColor=white
[Digital-url]: https://www.digitalocean.com/
[license-shield]: https://img.shields.io/badge/License-MIT-blue.svg
[license-url]: https://opensource.org/licenses/MIT