
# TRNG #

The goal of this project is to develop a True Random Number Generator. For the noise source I chose to use a zener diode. I made a first attempt with a low voltage one (3.8V), but I couldn't get satisfactory levels of noise. I moved then to the more tried and tested higer voltage zeners (12V) which, working on the avalanche effect, produce higher levels of noise.

Below is the schematic of the analog circuitry which is then hooked up an Arduino board that takes care to run it and sample the noise. 

![Schematic](documentation/schematic2.png)

If you are interested in the evolution of this project and few things I tried, and failed at, before coming to the current iteration see the [Project Log](LOG.md)

## The charge pump ##

The only available voltage is the 5V provided by the USB supply so I needed to first of all get a higher voltage to be able to run the zener close to its reverse breakdown voltage. I used a charge pump to get the higher voltage. The pump is made up of the schottky diodes D2-D5, C2-C4, C6 and L1. Under software control, PH0-2 alternate between 5v and 0v. If we assume PH0 starts at 0v then C2 will charge at 5V through D2. When then PH0 switches to 5V the junction between C2 and D2 will be lifted to 10V (5V PH0 plus the 5V across C2), at the same time D2 prevents current to flow back to the 5V rail and discharge C2. If PH1 is at this point at 0V current can flow from C2 to C3 instead, through D3. This will charge C3 to 10V. The process repeats with C3 raising to 15V when PH1 goes to 5V and so on. In an ideal circuit you would get 20V at the output, though there are voltage drops in the diodes so I'm getting about 17V. L1 is not critical but it helps getting rid of the digital noise that might still leak through the diodes once the charge pump stops. There is a closed loop control of the output voltage provided by feeding a portion of the voltage through R7/R8 to the board A/D converter, so software can run the charge pump only when the voltage is below a preset level.

In software the charge pump is controlled by the function runChargePump(). This takes care to sequence PH0-2 as needed until the desired voltage level is reached at the reservouir capacitor C6. This function also takes care to control the status lights that show the status of the charge pump. There is an alarm state the system can enter if the desired voltage is not reached within a certain time. Once the voltage is reached, or the alarm is entered, PH0-2 are turned into high impedance inputs. At this stage, unless the alarm mode has been entered, the noise sampling can happen, being the charge pump stopped guarantees the switching noise, which is repetitive, to no affect the read values.

### Charge Pump Status Indicator ###

Two LEDs indicate the status of the charge pump, see table below.

| Yellow | Green | Status                                      |
|--------|-------|---------------------------------------------|
| ON     | OFF   | Charge pump running                         |
| OFF    | ON    | Charge pump not running, voltage level OK   |
| FLASH  | OFF   | Charge pump couldn't reach required voltage |

## The noise source ##

The output of the charge pump is used to reverse bias the 12V zener diode D1 through the 530K resistor R1. The value of the resistor was determined empirically to be the one providing the best noise levels. The value of R1 also depends on the rest of the circuitry that loads the noise source, in general a higher value will mean a higher voltage fluctuation for a given current fluctuation in the zener. At the same time this raises the impedance of the noise source, so will weaken the signal when loaded. 

C1 decuples the DC and lets the noise reach Q1. Q1, with R3 and R2, is configured as an emitter follower and has the purpose to reduce the source impedance. Finally U1, an AD818 OpAmp, provides roughly a 30x amplification. C5 decouples the DC and presents the noise finally to the A/D for sampling.

NOTE: The noise at this point will be centered around 0V, this means that the lower portion will be lost by the A/D. It would be possible to get rid of C5 and play with the AD818 offset pins to get the DC somewhere half way of the A/D fullscale, this would give a 3dB boost to the signal seen in the digital world.

Below is a screenshot of the noise measured at NOUT.

![Scope](documentation/noise.png)

## Random Numbers Generation ##

Once the noise is sampled it gets converted to a train of 0s and 1s by taking the lsb of each analog reading and pushing it into the stream. The signal at this point is random but might be biased. To reduce bias the bitstream is process with John von Neumann whitening algorithm. This consumes 2+ bits to generate one bit, so the speed of data output varies depending on the bias of the original stream. The algorithm fundamentally takes couples of bits and discards them if they are the same. It does output instead a 1 if the bits are "10" and a zero if they are "01". This doesn't enhance the randomness of the data but reduces the bias towards one or zero that the data might have. The idea behind it is relatively simple and is based on the fact that if 1s have a probability P1 and 0s have a probability P0 then 01s have a probablilty P0*P1 and 10s have a probability P1*P0 which is, clearly the same.

## Validation ##

First of all I needed to make sure the noise I was seeing was coming from the zener and not from other sources on the board which, most likely, wouldn't be random due to the regularly repetitive nature of most signals on the board. To do this I have changed the software to not run the charge pump, after the first round. This caused the voltage on the reserviour capacitor C6 to slowly decrease, while all the other signals on the board were still as  in normal operation. I could confirm the noise slowly decreased as C6 voltage dropped proving the source is the zener and not leackage from the digital circuits.

I proceeded then to analyze the data generated for randomness. The software outputs the randomly generated numbers on the serial port in HEX dump format. So data can be first collected in a dump file in this way:

    stty -F /dev/ttyUSB0 115200
    cat /dev/ttyUSB0 | tee dump.txt

Once enough data is collected the dump file can be converted to binary and analyzed with "ent":

    xxd -r -p dump.txt random.bin
    ent random.bin

After some mishap that gave rather peculiar results, see [Project Log](LOG.md), I got the first promising analysys on a stream of roughly 3Mbits. Below the results:

    Entropy = 1.000000 bits per bit.

    Optimum compression would reduce the size
    of this 3244800 bit file by 0 percent.

    Chi square distribution for 3244800 samples is 0.68, and randomly
    would exceed this value 41.00 percent of the times.

    Arithmetic mean value of data bits is 0.5002 (0.5 = random).
    Monte Carlo value for Pi is 3.133372781 (error 0.26 percent).
    Serial correlation coefficient is -0.000792 (totally uncorrelated = 0.0).

The same file analyzed as bytes:

    Entropy = 7.999547 bits per byte.

    Optimum compression would reduce the size
    of this 405600 byte file by 0 percent.

    Chi square distribution for 405600 samples is 254.87, and randomly
    would exceed this value 49.04 percent of the times.

    Arithmetic mean value of data bytes is 127.5233 (127.5 = random).
    Monte Carlo value for Pi is 3.133372781 (error 0.26 percent).
    Serial correlation coefficient is -0.000240 (totally uncorrelated = 0.0).

## Photos ##

Below is the assembled protorype with the noise source and an Arduino Nano.

![Proto](documentation/proto2.png)
