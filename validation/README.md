
# Signal Source #

The first test was


# Raw Bit Stream #

| #    | Entropy  | Chi2 test | Mean Value | MC Pi       | Serial Correlation |
|------|----------|-----------|------------|-------------|--------------------|
| 1    | 7.961542 | 0.01      | 137.1090   | 2.930558    | 0.000619           |
| 2    | 7.961055 | 0.01      | 137.2818   | 2.856114    |-0.003822           |
| 3    | 7.964344 | 0.01      | 136.7270   | 2.921753    | 0.002994           |
| 4    | 7.960437 | 0.01      | 137.1584   | 2.925755    | 0.005780           |
| 5    | 7.961682 | 0.01      | 137.3476   | 2.912147    |-0.002330           |



| TAG    | kbps  | ENT | Notes                                 |
|--------|-------|-----|---------------------------------------|
| nogen  | 0     | N/A | Charge pump not running, no output.   |
| rawbs | 15      |     | Only lsb sampled and appended to stream.  |

| CRC32  | 16    | OK  | As above plus CRC32 extractor.        |

