# Decision Directed PLL (v2) - (GNU Radio OOT Module)

**Author:** Paulo Duta - PU4THZ  
**License:** GPL-3.0

---

## Overview

The **Decision-Directed PLL (v2) (dd_pllv2)** module provides a flexible
carrier-recovery loop that can lock to a variety of digital constellations
(BPSK, QPSK, QAM, etc.). It uses the GNU Radio `digital.constellation`
classes internally, ensuring compatibility with existing modulation schemes.

### Features
- Loop bandwidth and damping configurable at runtime
- Frequency limits and phase wrapping
- Multiple output streams (corrected signal, phase error, frequency)
- Compatible with GNU Radio 3.10+ and Radioconda environments

---

## Functionality

A decision-directed carrier recovery loop that compensates for carrier
phase and frequency offsets in a digitally modulated signal. The PLL
uses symbol decisions (based on the provided constellation) to correct
the carrier rotation, enabling coherent demodulation.

### Parameters

- **bw** : `float`, optional  
    Loop bandwidth in radians per sample. Controls how fast the PLL
    responds to phase/frequency errors. Higher values track faster but
    can be noisier. Typical values: 0.001–0.1.  
    *(Default: 2*pi/100 ≈ 0.0628)*

- **damp** : `float`, optional  
    Loop damping factor. Determines loop stability and transient
    response. A value of 1.0 corresponds to critical damping.  
    *(Default: 1.0)*

- **constellation** : `digital.constellation`, optional  
    Decision-directed constellation object used for symbol slicing.  
    Common examples:  
      - `digital.constellation_bpsk()`  
      - `digital.constellation_qpsk()`  
      - `digital.constellation_qam()`  
    *(Default: BPSK)*

- **min_freq** : `float`, optional  
    Minimum frequency correction limit (radians/sample).  
    Defines the lowest frequency offset the PLL can correct.  
    *(Default: -1.0)*

- **max_freq** : `float`, optional  
    Maximum frequency correction limit (radians/sample).  
    Defines the highest frequency offset the PLL can correct.  
    *(Default: +1.0)*

### Notes
- The PLL’s internal Numerically Controlled Oscillator (NCO)
  is constrained between `min_freq` and `max_freq`.  
- If the true carrier offset exceeds this range, the loop
  may fail to acquire lock.  
- To choose limits appropriately, convert expected offset in Hz to
  radians/sample:  
  `freq_range = 2 * pi * (expected_offset_Hz / sample_rate_Hz)`

---

## Inputs / Outputs

**Inputs**
- `in0` : complex stream

**Outputs**
- `out0` : complex stream (required)
- `errors` : float stream (optional)
- `freqs` : float stream (optional)

---

## Python Usage Example

```python
from gnuradio import dd_pllv2
import gnuradio.digital as digital

constellation = digital.constellation_bpsk().base()
pll = dd_pllv2.dd_pll(
  bw=0.0628,
  damp=1.0,
  constellation=constellation,
  min_freq=-1.0,
  max_freq=1.0
)
Note: A constellation pointer is required. The constructor will
throw an exception if constellation is None.
```

---

## Build Instructions

### Conda-based GNU Radio

Activate your Conda environment containing GNU Radio:

```bash
conda activate <your-env>
```

Install build dependencies:

```bash
conda install gnuradio-build-deps
```

Create a build directory and configure with CMake:

```bash
mkdir build && cd build
cmake -G Ninja \
    -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX \
    -DCMAKE_PREFIX_PATH=$CONDA_PREFIX \
    -DLIB_SUFFIX="" \
    ..
```

Build and install:

```bash
cmake --build .
cmake --build . --target install
```

Test the installation:

```bash
python -c "from gnuradio import dd_pllv2; print('dd_pllv2 loaded successfully')"
```

### Non-Conda / System-wide GNU Radio

Install GNU Radio and dependencies using your system package manager.
Example (Ubuntu):

```bash
sudo apt-get install gnuradio gnuradio-dev cmake g++ libboost-all-dev
```

Create a build directory and configure with CMake:

```bash
mkdir build && cd build
cmake ..
```

Build and install:

```bash
make -j$(nproc)
sudo make install
sudo ldconfig
```

Verify the module:

```bash
python3 -c "from gnuradio import dd_pllv2; print('dd_pllv2 loaded successfully')"
```

---

## References
- GNU Radio Out-Of-Tree Modules: https://wiki.gnuradio.org/index.php/OutOfTreeModules
- Conda GNU Radio Installation: https://wiki.gnuradio.org/index.php/CondaInstall