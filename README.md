# Hackaton 24-06-2024

This project is part of the intra-university `hackathon` of `Ecole 42 Antananarivo`.

The theme of the hackathon is `Independence Day`.

It started on `2024-06-24 at 8 A.M`. and ended on `2024-06-25 at 12 P.M`.

## Team

The team is composed of `four members`. We are students at `42 Antananarivo` following the `Common Core Cursus`. Here are our **logins** in the **42 Global Network**:

@**anjrakot** [github profile](https://github.com/Fafafa12)

@**hramaros** [github profile](https://github.com/shexweeknd)

@**nrabarij** [github profile](https://github.com/nrabarij)

@**nrabehar** [github profile](https://github.com/nrabehar)

[images-of-profiles](https://images/blob)

## Project Overview

Because the theme of the hackathon was `Independence day`, all the projects requested had to be related to `Malagasy traditions and customs`.

For our part, we decided to code a popular Malagasy game called `Fanorona`.

The game consists of ***two players***, opposing each other.

The program is basically written in `C` and uses the `MinilibX` library as a graphical API. It also utilizes a `Node.js` script for network communication.

### Strategy

The game is played on a board of `3x3`, `5x5` or `9x5`. Represented as `[column]x[lines]`.

It has two sides, composed of stones (or any items which can represent the pawns). The white and black pawns take alternate turns, starting with white in order to capture the opposing pieces.

There are two kinds of moves:

- A **non-capturing move**, which is called a `paika`.
- And a **capturing move**.

### End conditions

If one player captures all opponent's stones, the game `ends` and the player `wins`.

Or, if neither player can achieve this, the game ends with a `Draw`.

## Challenges

We faced the challenge of creating a simple game, yet enjoyable.

The real deal is to be able to play the game from `two different computers`, by transmitting player's data through a `server` which will display the board on each client's side.

### Usage

TODO