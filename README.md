
The goal of this project is to develop a true random number generator. As a sorce of entropy I have used a reversed biased zener diode. When polarized in this way a zener produces white noise in the order of few uV. The noise is amplfied by an OpAmp and input then into the Arduino A0 pin. Below is the schematic of the analog part of this device:

![Schematic](documentation/schematic2.png)

And below is the assembled protorype with the noise source and an Arduino Nano.

![Proto](documentation/proto2.png)

Once the noise is sampled it gets converted to a train of 0s and 1s by taking successive samples and comparing them with an average of the last samples. If the current value is above then a one is inserted in the stream otherwise a zero. This approach allows to compesate for eventual drifts in levels due to temperature or aging. The signal at this point is random but might be biased. To reduce bias I have processed the stream with John von Neumann whitening algoirthm. This consumes 2+ bits to generate one bit, so the speed of data output varies depending on the bias of the original stream. The algorithm fundamentally takes couples of bits and discards them if they are same. It does output instead a 1 if the bits are "10" and a zero if they are "01", this doesn't enhance the randomness of the data but reduces the bias towards one or zero that the data might have.


![Scope](documentation/noise.png)
