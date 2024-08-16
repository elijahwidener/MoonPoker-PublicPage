# MoonPoker: Legacy Project Showcase

![banner](https://gitmsplib.github.io/MP/banner.png)

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Legacy Design](#legacy-design)
4. [Technologies Used](#technologies-used)

## Introduction

MoonPoker was an ambitious project aimed at creating an online web app for playing poker in your browser with friends. While the project has since evolved, this repository showcases the legacy codebase as a completed project, demonstrating sophisticated object-oriented design principles and detailed UML modeling.

## Features

- **Multi-Game Support**: Designed to support Stud, Draw, and Community Card Variants of Poker.
- **Game-Modifications**: Planned support for Hi-Lo variants, bounties, and bomb pots.
- **User Profiles**: Infrastructure for creating and customizing player profiles.
- **Responsive Design**: Architected with a focus on both web and mobile optimization.

## Legacy Design

The legacy codebase of MoonPoker exemplifies a robust object-oriented programming (OOP) approach:

### UML Diagrams

The project includes several detailed UML diagrams that illustrate the system's architecture:

1. **Class Diagram**: Showcases the relationships between key classes in the poker game engine.
2. **Sequence Diagram**: Demonstrates the flow of a typical poker hand.
3. **State Diagram**: Illustrates the different states a poker game can be in.

[Include or link to your UML diagrams here]

### Key OOP Concepts Demonstrated

- **Encapsulation**: Clear separation of concerns with well-defined class structures.
- **Inheritance**: Utilization of base classes for common poker elements with specialized subclasses.
- **Polymorphism**: Flexible design allowing for different poker variants and game rules.
- **Abstraction**: High-level interfaces for game mechanics, separating implementation details.

### Code Structure

The legacy codebase was organized into several key modules:

- `GameEngine`: Core logic for managing game state and rules.
- `PlayerManagement`: Handling player data, actions, and state.
- `CardDeck`: Implementation of card deck operations.
- `HandEvaluator`: Logic for evaluating and comparing poker hands.
- `UIController`: Abstractions for user interface interactions.

## Technologies Used

The legacy project was built using:

- **Backend**: C++
- **Build System**: CMake
- **Testing**: Google Test
- **Serialization**: Google Protobuf
- **Documentation**: Doxygen

This project serves as a testament to thoughtful software design and architecture in game development.
