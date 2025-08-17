# Lotus

Lotus is a **lightweight, modern operating system** designed for **privacy, security, and efficiency**. Built from the ground up, Lotus powers your phone, providing a sleek and responsive experience with complete control over your data.

---

## Features

- **Privacy-first design**: Completely open-source, every single part.
- **Processor support**: Fully compatible with Aarch64 processors.
- **Minimal, efficient kernel**: Optimized for low-resource devices.  
- **Custom shell & apps**: Lightweight, intuitive user interface.  
- **Open and extensible**: Supports community-driven development and modular expansions.  

---

## Getting Started

### Requirements

- Supported device: Aarch64 is a must, build accordingly to your device tree.
- Cross-compiler toolchain: `aarch64-none-elf-gcc`  
- QEMU for testing (optional): `qemu-system-aarch64`  

### Build

```bash
git clone https://github.com/VigfallStudios/Lotus.git
cd Lotus
./configure ...
make
```

### Run in QEMU
```bash
qemu-system-aarch64 -machine virt -cpu cortex-a57 -nographic -kernel kernel.elf
```
