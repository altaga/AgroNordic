# AgroNordic
Sustainable platform of sensing and irrigation automation based around the Thingy53 with predictive analysis.

<img src="https://i.ibb.co/GJ5JwQR/agronordic-negro-sin-fondo.png">

Sustainable platform of sensing and irrigation automation based around the SenseCAP K1100 with predictive analysis via the Helium Network.

# Watch our demo video:

[![Demo](https://i.ibb.co/j3DCtPZ/image.png)](pending....)

# Test the product:

## URL: https://main.d30it56wy5f0pr.amplifyapp.com/

# Materials:

## Hardware:

- Thingy53 - [Product Link](https://www.nordicsemi.com/Products/Development-hardware/Nordic-Thingy-53l)
- SEGGER J-Link debugger (nRF5340-DK) - [Product Link](https://www.nordicsemi.com/Products/Development-hardware/nRF5340-DK)
- XIAO nRF52840 - [Product Link](https://www.seeedstudio.com/Seeed-XIAO-BLE-nRF52840-p-5201.html)
- RPi 4 - [Product Link](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)
- Capacitive Soil Moisture Sensor - [Product Link](https://www.amazon.com/Gikfun-Capacitive-Corrosion-Resistant-Detection/dp/B07H3P1NRM)
- TIP120 - [Product Link](https://www.arrow.com/es-mx/products/tip120/stmicroelectronics?utm_campaign=arrow_snapeda_q32020&utm_term=tip120&utm_medium=aggregator&utm_content=inpart_link_download&region=europe&utm_source=snapeda)
- 1N4007 - [Product Link](https://www.newark.com/w/search?st=18C8923&COM=ref_hackster&CMP=Hackster-NA-project-1c5452-Sep-22)
- Resistor 2.21k ohm - [Product Link](https://www.newark.com/vishay/cmf502k2100fheb/metal-film-resistor-2-21kohm-250mw/dp/26R4020?COM=ref_hackster&CMP=Hackster-NA-project-1c5452-Sep-22)
- Solenoid Valve - [Product Link](https://www.newark.com/gems-sensors/mb202-vb30-l203/solenoid-valve/dp/45M6131?COM=ref_hackster&CMP=Hackster-NA-project-1c5452-Sep-22)

## Software:

- Arduino IDE - [Program Link](https://www.arduino.cc/en/software)
- nRF Connect - [Program Link](https://www.nordicsemi.com/Products/Development-tools/nrf-connect-for-desktop)
- NodeJS - [Program Link](https://nodejs.org/en/)

## Cloud Services:

- IoT Core - [Service Link](https://aws.amazon.com/iot-core/)
- Amplify - [Service Link](https://aws.amazon.com/amplify/)

# Story: 

This will be the third iteration of two past projects;

The first one was Agrofox: https://www.hackster.io/107329/aggrofox-large-scale-and-urban-agriculture-iot-solution-8155fe

The second one is AgroHelium: https://www.hackster.io/Edoliver/agrohelium-urban-agriculture-aiot-solution-d8fbf4

We are also borrowing a lot from this one from Seeed:

https://youtu.be/NQt-XLcSIwA?list=PLpH_4mf13-A0MzOdPNITVfoVBMvf7Rg9g

Our intention this time is to get as close as possible to a functional prototype (the step before Mass-manufacturing), of course, with several upgrades along the way!

# Introduction:

In recent years Urban agriculture has made its mark in popular culture as an alternative to industrial farming. It offers several benefits and also helps to solve some of the most nefarious problems that we will have going forward regarding food supply, the growing population and the new trends favoring organic, naturally grown food. Despite all that it has been faced with a plethora of problems including its access to water, pollution concerns, and high maintenance costs. In addition to those most farming methods are very empirical in nature and it has been just a few years since the Internet of Things and other Industry 4.0 technologies have reached Agriculture. And among most of those, its degree of adoption is quite lackluster. Urban agriculture needs a cheap and readily available solution, for it to be sustainable.

Business Insider Singapore.

<img src="https://hackster.imgix.net/uploads/attachments/1500556/image_oICGQlCDSx.png?auto=compress%2Cformat&w=740&h=555&fit=max">

KImbal Musk (Elon's brother) is hyped about this.

<img src="https://hackster.imgix.net/uploads/attachments/1500557/image_v5DrlEKpJ6.png?auto=compress%2Cformat&w=740&h=555&fit=max">

# Problem:

IF we want to have the most impact with a project regarding sustainability, namely Water sustainability we have to focus on the industry that requires more of it, which is Agriculture.

<img src="https://hackster.imgix.net/uploads/attachments/1500558/image_qB4BGn0rdQ.png?auto=compress%2Cformat&w=740&h=555&fit=max">

And regarding that the main problem in agriculture is actually Water. Most countries have their periods of drought, but as years become even hotter because of climate change, drought greatly affects several regions. California is an example of this:

<img src="https://hackster.imgix.net/uploads/attachments/1500559/image_RQUnWDCS3m.png?auto=compress%2Cformat&w=740&h=555&fit=max">

So we get into a $42 Billion USD problem adding all the parameters. Industry 4.0 tools and automation are greatly needed to attack this.

**Here comes a new challenger!**

After COVID-19 hit most industries were shown a loss in revenue of almost 30%. The pandemic is impacting global food systems, disrupting regional agricultural value chains, and posing risks to household food security.

International Labour Organization.

<img src="https://hackster.imgix.net/uploads/attachments/1500560/image_hC6JGmMwOc.png?auto=compress%2Cformat&w=740&h=555&fit=max">

Now we have to take much more seriously the fact that Urban Agriculture can provide us a "cushion" during all this problematic time.

**Now, my personal problem**

This is a photo of one of the Tomato fruits I have in my backyard which I cannot continuously check. Sometimes I am away or very busy, and I tend to neglect its care. Another thing is regarding collecting fruit at the proper moments because they may become uneatable at some point. The problem regarding water can be taken care of if I automate irrigation and some more things.

<img src="https://hackster.imgix.net/uploads/attachments/1500561/image_0fIBbF3HgW.png?auto=compress%2Cformat&w=740&h=555&fit=max" height="400px">

# Solution:

Our solution to the problem will be to create a sustainable platform of sensing and irrigation automation with predictive analysis via the Thingy53 instead of relying entirely on cloud and we will be connecting everything with AWS IoT Core and BLE Gateway. With one objective in mind: SAVE WATER.

1. Using temperature with humidity, soil moisture and soil temperature sensors, we will obtain sensor data. BLE technology has been chosen because the characteristics of low power are excellent for remote areas and cities alike.

Then using the Openweathermap API and ReactJS we will create a Dashboard and notification capabilities.

1. We will connect to our RPi Gateway via the BLE and send sensor data to AWS IoT.

2. Once we have the data at AWS, we will then send it to a web application. We made it possible to develop almost any application with the obtained data. Examples of these applications:

Generate databases of our crops and their conditions.
Do data analysis to obtain predictive models in the long term.
Water automation systems with the data obtained (as we will do in this project).

Crop yield analysis.

3. We then will make a Dashboard with the data obtained for the complete and simple visualization of the data. For the application, we will perform data crossing with the OpenWeatherMap API, to perform the control of an electrovalve connected to another microcontroller. The data crossing obtained is used to check if that day is going to rain, and thus not use irrigation water in crops. Also if the system detects that water is needed, in the field by the humidity sensors, the irrigation system is turned on. In turn once a day an email will be sent to the farmer with the general information of his field or he can check anytime on his dashboard. Also everytime the irrigation system is online, a notification will be sent.

# Connection Diagram:

## Hardware Diagram:

## Temperature, Humidity and Moisture Device:

<img src="https://i.ibb.co/JFcVwKX/temp-bb.png">

### Electro Valve:

<img src="https://i.ibb.co/bHM8cV0/vLCE-bb.png">

# Temperature, Humidity and Moisture Device:

Main sensor circuit.

Bill of Materials:

- Thingy53.
- XIAO nRF52840.
- Capacitive Soil Moisture Sensor

<img src="https://i.ibb.co/JFcVwKX/temp-bb.png">

Real implementation:

<img src="https://i.ibb.co/37304R1/20221003-001525.jpg">

El codigo de esta implementacion usando nRF Connect es:

https://github.com/altaga/AgroNordic/tree/main/Sensor_Station

Toda la configuracion de BLE que tiene el device es la siguiente.

- Device Name: SENSORST
- Service Temperature UUID: 0000fe40cc7a482a984a7f2ed5b3e58f
  - Characteristic UUID: 0x0000fe438e2245419d4c21edae82ed19
- Service Humidity UUID: 0000fe41cc7a482a984a7f2ed5b3e58f
  - Characteristic UUID: 0x0000fe448e2245419d4c21edae82ed19
- Service Moisture UUID: 0000fe42cc7a482a984a7f2ed5b3e58f
  - Characteristic UUID: 0x0000fe458e2245419d4c21edae82ed19

La parte del codigo que manda los datos como notificaciones BLE para cada uno de los sensores es.

    err = bt_gatt_notify(NULL, &stsensor_svc.attrs[2], &temp, sizeof(temp));
    if (err)
    {
      LOG_ERR("Notify error: %d", err);
    }
    else
    {
      LOG_INF("Send notify ok");
      temp = (temp == 0) ? 0x100 : 0;
    }

Code: URL: https://github.com/altaga/AgroNordic/blob/main/Sensor_Station/src/main.c

# Valve Module:

Once the main circuit is completed, make the automated irrigation valve.

Bill of Materials:

- Thingy53.
- TIP120
- 12v Source.
- Solenoid Valve Nc 1/2.
- Diode 1N4007.
- 1 Resistances of 2.2kohm.
- Cable, Solder, Jump wire or similar.

<img src="https://i.ibb.co/bHM8cV0/vLCE-bb.png">

Real implementation:

<img src="https://i.ibb.co/M8Q4dpC/20221003-001929.jpg">

El codigo de esta implementacion usando nRF Connect es:

https://github.com/altaga/AgroNordic/tree/main/Valve_Code

Toda la configuracion de BLE que tiene el device es la siguiente.

- Device Name: ElectroValve
- Service UUID: 0000fe38cc7a482a984a7f2ed5b3e58f
  - Characteristic UUID: 0000fe398e2245419d4c21edae82ed19

La parte del codigo que controlaba el estado de la electrovlula era el siguiente.

    void led_update(void)
    {
      if (!led_ok) {
        return;
      }

      led_state = !led_state;
      LOG_INF("Turn %s LED", led_state ? "on" : "off");
      gpio_pin_set(led.port, led.pin, led_state);
    }

Code: URL: https://github.com/altaga/AgroNordic/blob/main/Valve_Code/src/led_svc.c

# RPi Gateway:

Por ultimo como cereza en el pastel, vamos a ocupar una RPi como gateway BLE para mandar los datos ditrectamente a AWS IoT.

Real implementation:

<img src="https://i.ibb.co/KFTyRGP/20221002-235618.jpg">

El codigo de esta implementacion usando nRF Connect es:

https://github.com/altaga/AgroNordic/blob/main/Gateway/index.py

En esta implementacion se realizo un MQTT Client en la RPi, el cual segun los resultados que este leyendo de nuestros devices y mandando estos a AWA IoT core ademas de poder controlar la valula al escribir un valor en el topic "/changevalve".

# RPi - AWS IoT Integration:

El poder obtener los datos de los sensores no tiene sentido alguno si no se tiene un servicio en la nube que obtenga los datos y los utilice con algun fin, en este caso AWS.

<img src="https://i.ibb.co/MCDgc21/Image.png">

Para poder mandar los datos desde nuestra gateway a AWS IoT, ocupamos su servicio de MQTTS, para eso tendremos que crear una Thing en la plataforma.

<img src="https://i.ibb.co/DWSzzd0/image.png">

Puedes ponerle el nombre que quieras a la Thing.

<img src="https://i.ibb.co/prQGyBB/image.png">

La parte importante de este proceso sera obtener los certificados de la thing, pero si quieres experimentar mas con el SDK de IoT de AWS, puedes seleccionar el OS que prefieras.

<img src="https://i.ibb.co/tZ6bqR7/image.png">

Una vez creado el SDK lo descargaremos a nuestra maquina.

<img src="https://i.ibb.co/mHwNDG9/image.png">

El paso mas importante aca es obtener estos certificados, ya que ellos no permitiran conectarnos correctamente a AWS IoT.

<img src="https://i.ibb.co/xmsff01/image.png">

Ya con estos certificados podras utilizar el MQTTS de la RPi gateway correctamente.

# Dashboard:

For our dashboard we made a simple web page with ReactJS, we decided that the green color was the most representative of a sustainability challenge.

For the graphics page, we made a crop selector, where we can see the real-time data of each crop, the data in the graphics is sent directly from AWS IoT Integration.

<img src="https://i.ibb.co/Gt9mnXX/image.png">

We also added a page, where we will see the location of our devices, in order to better track the weather.

<img src="https://i.ibb.co/b3v3WNq/image.png">

## AWS Amplify:

We are going to use the Amplify service to make the deployment of our application, but this requires having a repository where we have our code to be able to carry out the CI / CD process, we can use any of the following Git repository hosting services.

<img src="https://i.ibb.co/vkQdd2D/image.png">

However, to maintain a better organization of the apps deployed on AWS, we will use Github with Private Repository.

<img src="https://i.ibb.co/s5nsks7/Screenshot-2022-09-26-215831.png">

We select the repository that we create with our code.

<img src="https://i.ibb.co/tBDmxt4/image.png">

Since it is a deployment with ReactJS the Build settings are configured automatically.

<img src="https://i.ibb.co/mzrfv1D/image.png">

Once we finish creating the WebApp, all the steps of the Ci / CD cycle should appear and if everything went well they should look like this.

<img src="https://i.ibb.co/QKC7QWb/image.png">

The result will be a link similar to this one.

WebApp: https://main.d30it56wy5f0pr.amplifyapp.com/

# Irrigation system via Openweathermap Forecast and Thingy53.

We have to explain first the why's before the know how's.

The use of tracking the forecast of the weather is the main purpose of the project itself, that is to optimize water usage.

What use there is of having a sensor that tracks that the soil is dry and activate an irrigation system with that info, but it is going to rain that same day?

We can save a lot of water simply by using the weather forecast systems available to notify our platform that it is going to rain and stop from using water that day.

And of course we want to automate everything.

Without further ado:

- Get to: https://openweathermap.org/ and Sign up.

- After that then simply go to Sign In and click on API Keys, then copy the API KEY.
  
<img src="https://hackster.imgix.net/uploads/attachments/1500565/image_q9pmS0RNXX.png?auto=compress%2Cformat&w=740&h=555&fit=max">

En este caso el dashboard esta consumiendo la API de OpenWeatherMap y como este esta conectado a su vez con AWS IoT core, este es capaz de recibir los datos deel thingy53 y controlar con un clic la activacion o desactivacion de la valvula, segun el clima y los datos obtenidos de el sensor.

<img src="https://i.ibb.co/YhFj9gK/vlcsnap-2022-10-06-20h41m11s881.png">

# Going Green: Solar Power:

This device has to have a solar panel to reduce the cost of infrastructure.

We recommend that you use at least a 2.5W Solar panel (I tried on a 2W panel and failed, it got very low power and lifetime) in tandem with a LiPo Battery like in the following circuit:

<img src="https://i.ibb.co/c6X2gZN/temp2-bb.png">

The power segment of the circuit is intended to power the circuit via a Solar Power during the day and then charge the LiPo battery so it can continue working at night.

For this purpose you can see the Regulator in the image that is a connection module that regulates the LiPo battery charge and the Solar Panel feeding energy to the system.

<img src="https://hackster.imgix.net/uploads/attachments/1500571/image_h5j8edt4nF.png?auto=compress%2Cformat&w=740&h=555&fit=max">

The Sigfox version of the project, the same can be done with the Thingy53.

As previously stated I tried with my small 2W panel, but we are in the rainy season where I live so we need a bigger panel. I urge someone who already has the bigger panel to try it. For the Demo I will be using a Battery. BE very wary when trying this setup, I would go to battery just to be sure and by the way it will be an external one, because for it to work with the AA it may, you have to destroy a resistance.

Here are some reccomended links to these components:

Sunny Buddy: https://www.sparkfun.com/products/12885

Lipo Rider pro: https://www.seeedstudio.com/LiPo-Rider-Pro-p-992.html

Solar panel: https://www.seeedstudio.com/2-5W-Solar-Panel-116X160.html

Now its time to upload the code into your dev board! (If you have already input your credentials properly beforehand, if not go to the next step). Get everything into their cases (3D CAD models provided).

**At this point we have the two "Things" of our AIoT solution that sense and actuate**

# Get Cases:

CAMBIAR

I took the time to make some NEW cases for the project and the result is quite good as you can see:

<img src="https://hackster.imgix.net/uploads/attachments/1502873/image_lpdyj7sbdr.png?auto=compress%2Cformat&w=740&h=555&fit=max">
<img src="https://hackster.imgix.net/uploads/attachments/1502882/image_g3E4IhPRJ1.png?auto=compress%2Cformat&w=740&h=555&fit=max">

Video:

[![Demo](https://i.ibb.co/j3DCtPZ/image.png)](https://www.youtube.com/watch?v=o-x40sDlnao)

# Final Product:

Here is the final version of the complementary sensor:

Thingy53 Valve:

<img src="https://i.ibb.co/dJkbWNK/Image.png">

On Site:

<img src="https://i.ibb.co/bBMmnWL/Image.png">

Thingy53 Sensors:

<img src="https://i.ibb.co/pnqC2YX/20221002-234904.jpg">

On Site:

<img src="https://i.ibb.co/CWWF7Zh/20221003-134835.jpg">

RPi Gateway:

<img src="https://i.ibb.co/CHGRrdX/20221002-235534.jpg">

On Site:

<img src="https://i.ibb.co/mSvNmkH/20221003-134815-1.png">

Full Solution:

<img src="https://i.ibb.co/tzZVmhW/Image.png">

# EPIC DEMO:

[![Demo](https://i.ibb.co/j3DCtPZ/image.png)](pending...)

# Benefits and Sustainability:

As long as we can push initiatives like this forward we can get:

1. Reduction in Carbon emmisions The average meal has traveled 4, 200 miles just to get to your table. Urban agriculture helps consumers reduce their “foodprint” by providing them the opportunity to purchase food that was grown within their community.

2. Creating Jobs These farms create opportunities to involve the community. Urban farms create jobs (and volunteer) opportunities in big cities, where poverty and hunger are often persistent issues.

3.- Stimulates your local economy which also builds the community around. An increase in small businesses stimulates local economy and supports the community by creating jobs right where people live.

4. Healthcare.- Bringing nutritious food to local communities has many direct health benefits, including reducing the risk of harmful conditions like heart disease, obesity, diabetes, and more.

5. Food quality.-These farms preserve biodiversity by cultivating heirloom varieties or those with lower shelf-stability. The proximity and connectedness to market allows for fresh, nutritious produce to become available to communities that have never had access to this in the past.

6. Green spaces: This contributes to the health of city ecosystems in a variety of ways. Greenery adds aesthetic appeal, reduces runoff from precipitation, provides restful spaces for the community, and counters the heat island effect by fixing carbon.

<img src="https://hackster.imgix.net/uploads/attachments/1500573/image_rQrzzfocGW.png?auto=compress%2Cformat&w=740&h=555&fit=max">

# Commentary and Future Rollout:

Sustainable disruption is needed because current methods are insufficient for the rising demand, infrastructure is costly and most fields are in remote areas. Also despite what it promises urban agriculture needs a cheap and readily available solution, for it to be sustainable. And COVID-19 just came to aggravate this situation even more.

The current project offers an initial solution to these problems by starting with one of my own, but it is not difficult to see how one of these can expand. This offers a cheap and affordable solution that can serve the local, home or urban farmer as it can automate several of their processes and most important of all provide valuable information about their crops that they can use to make good decisions.

Thinking about the future of the project, of course I still like Helium after all these years. And despite some of the controversies that have been coming up since last year, as a builder first I can see the potential of the biggest LoRa Network in the world and now with their 5G and Cellular side pivot. Regarding the [SenseCAP K1100 - The Sensor Protytype Kit with LoRa® and AI](https://www.seeedstudio.com/seeed-studio-lorawan-dev-kit-p-5370.html), I think it offers a great solution for builders, makers and even home growers and tinkerers alike. With it we were able to pass less time on the bench soldering and getting everything together and more time designing the product and on its presentation and concept. Not to mention that the Wio Terminal is excellent to give your product a much more refined touch and further possibilities of commercialization.

# References:

- https://developer.helium.com/
- https://www.freightfarms.com/blog/urban-farming-benefits
- https://www.theecologycenter.org/10-ways-urban-farms-benefit-the-community/
- https://www.vox.com/2016/5/15/11660304/urban-farming-benefitshttps://www.hackster.io/107329/aggrofox-large-scale-and-urban-agriculture-iot-solution-8155fe
- https://www.hackster.io/contests/iotinthewil