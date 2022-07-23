# project_anemoi

Actually, this might be 2 separate projects, first one is the implementation of bigint and the second one is the cryptographic part of this project, but I want to keep it as it is. Written purely in C++17 without any non-std libs. 

**NB!** The project is still WIP.

## Description
This is an attempt to re-implement several cryptographic primitives, including the implementation of BigInteger, RSA, DH, ECC and possibly NTRUEncrypt. Please, note, that it is purely ***academic*** project, so it ~~might have~~ has a list of bugs, vulnerabilities and errors, but I tried to keep this list of errors as small as possible.

## How to use it
This is the standalone library with all necessary features, needed to work, include it and give it a try!

## List of implemented features
- [ ] BigInteger
  - [x] Essential methods
    - [x] Multiplication
    - [x] Division
    - [x] Addition
    - [x] Subtraction
  - [ ] Basic functions
    - [x] Pow (with and w/o given modulus)
    - [x] GCD
    - [ ] Miller-Rabin primality test
    - [ ] Factorial
    - [ ] Random
    - [ ] Get random prime
- [ ] Cryptographical implementations
  - [ ] Textbook RSA
  - [ ] DH (RSA-based)
  - [ ] ECC
  - [ ] ECDSA
  - [ ] DH (ECC-based)
  - [ ] NTRUEncrypt
