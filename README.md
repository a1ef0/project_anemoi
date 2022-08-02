# project_anemoi

Implementation of different cryptographic primitives. Written in c++17, with CLN library.

**NB!** The project is still WIP.

## Description
This is an attempt to re-implement several cryptographic primitives, including the implementation of RSA, DH, ECC and possibly NTRUEncrypt. Please, note, that it is purely ***academic*** project, so it ~~might have~~ has a list of bugs, vulnerabilities and errors, but I tried to keep this list of errors as small as possible.

## Installation
Install the CLN library first.

## How to use it
This is the standalone library with all necessary features, needed to work, include it and give it a try!

## List of implemented features
  - [ ] Basic functions
    - [x] Pow (with given modulus)
    - [x] GCD
    - [ ] Miller-Rabin primality test
    - [x] Random
    - [ ] Get random prime
- [ ] Cryptographical implementations
  - [ ] Textbook RSA
  - [ ] DH (RSA-based)
  - [ ] ECC
  - [ ] ECDSA
  - [ ] DH (ECC-based)
  - [ ] NTRUEncrypt
