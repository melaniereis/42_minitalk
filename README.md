# 📡 Minitalk

<div align="center">

![Funny Communication GIF]([https://media.tenor.com/yF3Zothe3f8AAAAM/food-fight-food-war.gif](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExNGl3bWx4cTZoMHY4d2MzbmtzZTEyMGszeHFwOWNxcWg5YnNydTdtbyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/3o7bucZfOGGG4gWlPy/giphy.gif))

Welcome to **Minitalk** - An implementation of the Minitalk project from 42 School, enhanced with Unicode support and multi-client functionality.

![Project Status](https://img.shields.io/badge/Project-Minitalk-blue?style=for-the-badge&logo=42)
![Programming Language](https://img.shields.io/badge/Language-C-orange?style=for-the-badge&logo=c)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

## 📚 Table of Contents

<details>
<summary>View Contents</summary>

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Bonus Features](#bonus-features)
- [Contributing](#contributing)
- [License](#license)

</details>

---

## 🔍 Overview

**Minitalk** is a project that demonstrates inter-process communication using signals (`SIGUSR1` and `SIGUSR2`). This implementation extends the basic requirements by supporting Unicode, transmitting message length, and handling multiple clients.

---

## ✨ Features

- **Unicode Support**: Utilizes bitwise operations for transmitting data, supporting Unicode characters.
- **Message Length Pre-transmission**: Client sends message length for server memory allocation.
- **Bitwise Signal Sending**: Each byte is transmitted bit by bit via signals.
- **Multi-Client Support**: Server can receive messages from multiple clients in sequence.
- **Confirmation Signal**: Server signals back to confirm message receipt.

---

## 🚀 Installation

### 📦 Prerequisites

- **C Compiler** (e.g., GCC)
- **Make** tool

### 🔧 Setup

```bash
git clone https://github.com/melaniereis/42_minitalk.git
cd minitalk
make
```
## 🖥️ Usage

**Start the Server:**
```bash
./server
```
**Use the Client to Send Messages:**
```bash
./client [server_pid] "Your message here"
```
Replace [server_pid] with the process ID of the running server
## 🧠 Implementation Details

**Client Side:**
- Begins by sending the length of the message.
- Converts each character to bytes, sending each bit via signals (`SIGUSR1` for 0, `SIGUSR2` for 1).

**Server Side:**
- Allocates memory based on the length received.
- Reassembles characters from bits, storing them until the message is complete.
- Uses `sigaction` for signal handling.

**Bitwise Operations:**
- Essential for handling Unicode characters by breaking them into bits.

**Multi-Client Support:**
- Server resets state after each message, ready for new connections.

## 🎁 Bonus Features

- **Unicode Compatibility**: Bitwise operations allow for Unicode transmission.
- **Feedback Mechanism**: Server confirms message receipt to the client.
- **Use of `sigaction`**: Provides a more robust signal handling mechanism.

## 🧬 Justifications for Design Choices

### Use of `sigaction`:
- **Reliability**: `sigaction` allows for more reliable signal handling compared to the older `signal` function. It provides options to control how signals are delivered, ensuring that signals are not lost or ignored during processing.
- **Signal Masking**: With `sigaction`, you can specify a signal mask, which prevents certain signals from interrupting the handler while it's running, thus avoiding race conditions or signal storms, which is critical in an environment where multiple signals are expected.
- **Behavioral Control**: It supports setting flags to modify signal behavior, such as `SA_RESTART`, which can restart system calls if they are interrupted by a signal, improving the robustness of the application.

### Global Variables:
- **State Management**: A single global variable is used on the server to manage the current state of message reception. This includes tracking the bit position, storing the message, and signaling if a message is currently being processed or completed.
- **Simplification**: This method simplifies the code architecture, especially important for maintaining state across signal interruptions or when dealing with multiple clients.

## 🤝 Contributing

Contributions are welcome! Feel free to fork this repository, make changes, and submit pull requests.

## 📜 License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

<div align="center">

**Let's Communicate! 🎉**

[⬆ Back to Top](#-minitalk)

</div>
