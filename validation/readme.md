
# Signal Source #

The first test was


| TAG    | kbps  | ENT | Notes                                 |
|--------|-------|-----|---------------------------------------|
| NOGEN  | 0     | N/A | Charge pump not running, no output.   |
| ADONLY |       |     | Only lsb sampled and appended to stream.  |
| VONNEU |       |     | As above plus Von Neumann whitening.      |
| CRC32  | 16    | OK  | As above plus CRC32 extractor.        |

