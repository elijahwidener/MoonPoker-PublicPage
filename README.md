# MoonPoker: High-Performance Poker Engine and Network Framework

![banner](https://gitmsplib.github.io/MP/banner.png)

## Table of Contents
1. [Project Overview](#project-overview)
2. [Technical Architecture](#technical-architecture)
3. [Current Status](#current-status)
4. [Technologies](#technologies)
5. [Key Features](#key-features)
6. [Contact](#contact)

## Project Overview

MoonPoker is a modern poker platform designed to provide a high-performance, low-latency poker experience. The project features a modular architecture with a C++ game engine core, networked gameplay capabilities, and a cross-platform Flutter client. Our design focuses on performance, scalability, and clean separation of concerns.

![Poker Game Demo](https://github.com/elijahwidener/MoonPoker-PublicPage/blob/main/TUI_working.mp4)

## Technical Architecture

MoonPoker employs a layered architecture:

### Core Game Engine (C++)
- **High-performance** poker logic implementation
- **Deterministic evaluation** of poker hands
- **Constant-time** operations for critical path functions
- **Memory-efficient** state management

### Network Layer (C++ with gRPC)
- **Server implementation** with concurrent game management
- **Real-time communication** for gameplay events
- **Secure authentication** system
- **Game state synchronization** with optimized protocols

### Client Application (Flutter/Dart)
- **Cross-platform** support (Web, iOS, Android)
- **Responsive UI** design for different screen sizes
- **State management** with modern reactive patterns
- **Offline capabilities** for practice play

### Web Services (JavaScript)
- **Lobby system** for game discovery and joining
- **User account management** with authentication
- **Social features** including friends and messaging
- **Tournament management** for competitive play
- **RESTful API** for client-server communication

## Repository Structure

The project is organized into separate repositories for each major component:

- **moonpoker-engine**: C++ game core and poker logic
- **moonpoker-client**: Flutter-based cross-platform client
- **moonpoker-lobby**: JavaScript-based lobby and user management including authentication

This separation allows specialized teams to work on different components using the most appropriate technology for each domain.

## Current Status

### Completed Components:
- ✅ Core poker game engine (Texas Hold'em)
- ✅ Hand evaluation algorithms
- ✅ Game state management
- ✅ Client-server communication protocol
- ✅ Basic server implementation with gRPC
- ✅ Container-based deployment configuration
- ✅ User authentication API
- ✅ Basic lobby system

### In Progress:
- 🔄 Flutter client implementation refinement
- 🔄 Expanded lobby features
- 🔄 Game matching algorithms
- 🔄 User profiles and social features
- 🔄 Production server deployment

## Technologies

### Backend (Game Engine)
- **C++17/20**: Core engine implementation
- **CMake**: Build system management
- **Google Protocol Buffers**: Data serialization
- **gRPC**: Network communication
- **Docker**: Containerization (to be changed to EKS)
- **Envoy**: API gateway for gRPC-Web
- **spdlog**: Logging framework

### Backend (Web Services)
- **Node.js/Express**: RESTful API services
- **PostgreSQL**: User and lobby data storage
- **JWT**: Authentication tokens

### Frontend
- **Flutter/Dart**: Cross-platform client application
- **gRPC-Web**: Client-server communication for game
- **Provider/Riverpod**: State management
- **Flutter Secure Storage**: Local credential storage

### Testing & Quality
- **Google Test**: C++ unit testing
- **Jest**: JavaScript testing
- **Clang Format**: Code style enforcement
- **Doxygen**: Documentation generation

## Key Features

- **Modern C++ Game Core**: Leveraging modern C++ features for performance and safety
- **JavaScript Web Services**: Familiar web stack for user management and lobby features
- **Cross-Platform Client**: Play on web, mobile, or desktop
- **Networked Gameplay**: Multiplayer with low-latency synchronization
- **Modular Architecture**: Clean separation between game rules, networking, and presentation
- **Extensible Design**: Support for additional poker variants planned

## Contact

For inquiries about the current stage of the project, please contact:
- Email: elijahwidener@vt.edu
- GitHub: [elijahwidener](https://github.com/elijahwidener)

---
© 2025 MoonPoker Project
