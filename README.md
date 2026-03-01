# Hamming Distance Calculator (Bit-Level Logic)

This project implements an efficient tool to calculate the **Hamming Distance** between two bitstreams. In information theory, the Hamming distance measures the minimum number of substitutions required to change one string into the other, which is a fundamental metric for error detection and data comparison.



## 🛠️ Technical Implementation
* **Bitwise XOR Strategy:** The core logic utilizes the `XOR` (⊕) operation. For any two bits, $a \oplus b$ returns `1` if the bits are different and `0` if they are the same.
* **Population Count:** After the XOR operation, the algorithm counts the number of set bits (1s) in the result to determine the total distance.
* **Optimization:** Designed with low-level bit manipulation to ensure minimal computational overhead, suitable for real-time data processing.

## 📉 Mathematical Definition
For two binary vectors $x$ and $y$ of length $n$, the Hamming distance $d_H$ is defined as:

$$d_H(x, y) = \sum_{i=1}^{n} (x_i \oplus y_i)$$

Where $\oplus$ denotes the Exclusive-OR operation.



## 🚀 Use Cases
* **Error Correction:** Detecting bit-flips in data transmission (Hamming Codes).
* **Genetic Analysis:** Comparing DNA sequences represented as binary strings.
* **Pattern Recognition:** Measuring similarity between feature vectors in machine learning.

## 🃏 Relevance to Pokerbots
In competitive programming and bot development, bit manipulation is often used to represent "Game States" or "Card Sets" (Bitmasks). Calculating distances or differences between these masks using bitwise operators is significantly faster than using standard loops, which is critical when a bot must make decisions within millisecond time constraints.

---
**Author:** Hariharasudhan | Electrical Engineering, IIT Madras | Roll No: ee25b052
