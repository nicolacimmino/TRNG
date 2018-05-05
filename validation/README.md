
# Signal Source #

The first test was


# Raw Bit Stream #

Below is an analysys of the raw bitstream, as collected from the ADC by sampling the lsb 8 times to produce 1 byte. The below data was calculated on 5 samples of 32KBytes each.

| #    | Entropy  | Chi^2 Dist. | Chi^2 %    | Mean Value | MC Pi       | Serial Correlation | 1s probability |
|:----:|---------:|------------:|-----------:|-----------:|------------:|-------------------:|---------------:|
| 1    | 7.961542 | 1355.23     | 0.01%      | 137.1090   | 2.930558    | 0.000619           | 0.536870       |
| 2    | 7.961055 | 1622.81     | 0.01%      | 137.2818   | 2.856114    |-0.003822           | 0.537583       |
| 3    | 7.964344 | 1487.93     | 0.01%      | 136.7270   | 2.921753    | 0.002994           | 0.535682       |
| 4    | 7.960437 | 1676.55     | 0.01%      | 137.1584   | 2.925755    | 0.005780           | 0.537758       |
| 5    | 7.961682 | 1618.99     | 0.01%      | 137.3476   | 2.912147    |-0.002330           | 0.537366       |

While the entropy and serial correlation values are good all the other values are not. From the mean value and the 1s probability we can determine this is just due to bias towards 1s. This is also visually confirmed by the probability distribution graph below. The staggered curve raises is due to the higer probability of numbers containing more 1s.

![Probability Distribution](../documentation/prob_distr_rbs05.png)



# Overall Performance #

| TAG    | kbps  | ENT | Notes                                 |
|--------|-------|-----|---------------------------------------|
| nogen  | 0     | N/A | Charge pump not running, no output.   |
| rawbs | 15      |     | Only lsb sampled and appended to stream.  |

| CRC32  | 16    | OK  | As above plus CRC32 extractor.        |

