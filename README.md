# Small_Vitals_IOT
Small_Vitals_Stub with connectivity code for CC3001 wifi shield. 
All the sensor data is triggered and sampled using just one function each, a https connection between the server and the toolkit is enabled, 
which sends all the data in real-time to the server, open the main file for information on all the sensors and it's driver code and ajson file for the connectivity.
Individual stubs for all the sensors are provided.
The wifi server program is contained in the WifiWebServer_tiva_shield folder and "Wifiutils" files.
For Heart beat analysis, fourier transform is used, please find the library in Fix_FFT for 8-bit version of the FFT. 

The explanation for the same can be seen here:
https://youtu.be/jcv0xv_edSs

The working can be seen here:
https://youtu.be/ryU4mGXHzNU
