
# Signal Source #

The first test was


# Raw Bit Stream #

| #    | Entropy  | Chi2 test | Mean Value | MC Pi       | Serial Correlation |
|------|----------|-----------|------------|-------------|--------------------|
| 1    | 7.961542 | 0.01      | 137.1090   | 2.930558335 | 0.000619           |




| TAG    | kbps  | ENT | Notes                                 |
|--------|-------|-----|---------------------------------------|
| nogen  | 0     | N/A | Charge pump not running, no output.   |
| rawbs | 15      |     | Only lsb sampled and appended to stream.  |

| CRC32  | 16    | OK  | As above plus CRC32 extractor.        |

