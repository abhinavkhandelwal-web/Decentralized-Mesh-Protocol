#pragma once

#include <cstdint>
#include <cstddef>

class SecurityEngine
{
private:
    uint8_t key[16];
    bool key_set;

    uint8_t round_key[176];

    void key_expansion();

    void encrypt_block(
        const uint8_t input[16],
        uint8_t output[16]
    );

    static void add_round_key(
        uint8_t state[16],
        const uint8_t* round_key
    );

    static void sub_bytes(uint8_t state[16]);
    static void shift_rows(uint8_t state[16]);
    static void mix_columns(uint8_t state[16]);

    static uint8_t gmul(
        uint8_t a,
        uint8_t b
    );

public:
    SecurityEngine();
    ~SecurityEngine();

    bool set_key(
        const uint8_t* user_key,
        size_t key_len
    );

    void clear_key();

    bool encrypt(
        const uint8_t* plaintext,
        size_t len,
        uint8_t* ciphertext,
        const uint8_t nonce[16]
    );

    bool decrypt(
        const uint8_t* ciphertext,
        size_t len,
        uint8_t* plaintext,
        const uint8_t nonce[16]
    );
};
