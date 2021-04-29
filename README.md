
# WiFi Function and Arbitrary Waveforms Generator

---

![Project.Cover](funcGen.jpg)

---

### Download
| Latest release | Latest development build |
|----------------|--------------------------|
| [![Noto](https://img.shields.io/badge/master-v1.0-green.svg)](https://github.com/NotoFederico/FuncGen/tree/main) | [![Noto](https://img.shields.io/badge/develop-v2.0+-blue.svg)](https://github.com/NotoFederico/FuncGen/tree/dev) |

---

# Contents
- 1 - [Introduction](#1-introduction)
- 2 - [Paper Link](#3-paper-link)
- 3 - [Contributing](#4-contributing)
- 4 - [Licence](#5-licence)

---

# 1. Introduction

The present project aims to develop a function generator, which is exactly what its name implies: a test equipment that generates electrical signals in the form of waves that are used as stimuli for electronic measurements.

Most circuits require some type of input signal whose amplitude varies with time. The signal can be an alternating current signal (with peaks that oscillate above and below a reference) or it can vary over a range of direct current offset voltages, either positive or negative. It can be a sine wave or other analog function, a digital pulse, a binary pattern, or a purely arbitrary waveform.

The generator of signals, or functions, is the source of stimulus. Pair with a data acquisition instrument for a complete measurement solution. The two tools are connected to the input and output terminals of the device under test (DUT).

The signal generator can provide "ideal" waveforms, or it can add known and repeatable amounts and types of distortion (or errors) to the signal it delivers. This feature is one of the greatest virtues of the signal generator, as it is often impossible to create predictable distortion, exactly when and where it is needed, using only the circuit itself. The response of the device under test (DUT) in the presence of these distorted signals reveals its ability to handle voltages that fall outside the envelope of normal performance.

There are hundreds of different applications for this class of equipment, but placed in a context of electronic measurements, three categories can be divided: Verification: the designers of wireless equipment that develop new transmitting and receiving hardware must simulate baseband I&Q signals, with and without deficiencies, to verify compliance with proprietary wireless standards using arbitrary low-distortion functions.

Characterization: Newly developed digital-to-analog converters (DACs) and analog-to-digital converters (ADCs) must be thoroughly tested for their limits for linearity and distortion. Analog and digital signals are applied in phase to bring the speeds of these devices up to 1Gbps. Stress or margin test: engineers working with serial data flow architectures (commonly used in digital communication buses) need to stress their devices with deficiencies, particularly fluctuations and synchronization violations

In the project in question, known signals can be generated: such as sine, semi-diverse, square, rectangular, triangular, sawtooth and white noise and arbitrary signals, which are those signals of complex origin that do not follow a regular mathematical expression and that can be generated by the user using specialized software and subsequently sent over WiFi, thanks to a dedicated website. These signals can be chosen through a menu and their parameters, such as duty, offset and amplitude, are modifiable and will be monitored in real time on a display.

---

# 2. Paper Link

[Paper (Spanish)](https://github.com/NotoFederico/FuncGen/blob/main/FuncGen_STM32DISCO/Informe.pdf)


---

# 3. Contributing

FuncGen uses the [gitflow workflow](https://www.atlassian.com/git/tutorials/comparing-workflows#gitflow-workflow). If you are implementing a new feature or logic from the original game, please branch off and perform pull requests to ```develop```. If you are fixing a bug for the next release, please branch off and perform pull requests to the correct release branch. ```master``` only contains tagged releases, you should never branch off this.

---

# 4. Licence

FuncGen is licensed under the GNU General Public License version 3.

