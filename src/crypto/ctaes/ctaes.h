/*
 * This file is part of the Flowee project
 * Copyright (C) 2016 Pieter Wuille                                   *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CTAES_H_
#define _CTAES_H_ 1

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint16_t slice[8];
} AES_state;

typedef struct {
    AES_state rk[11];
} AES128_ctx;

typedef struct {
    AES_state rk[13];
} AES192_ctx;

typedef struct {
    AES_state rk[15];
} AES256_ctx;

void AES128_init(AES128_ctx* ctx, const unsigned char* key16);
void AES128_encrypt(const AES128_ctx* ctx, size_t blocks, unsigned char* cipher16, const unsigned char* plain16);
void AES128_decrypt(const AES128_ctx* ctx, size_t blocks, unsigned char* plain16, const unsigned char* cipher16);

void AES192_init(AES192_ctx* ctx, const unsigned char* key24);
void AES192_encrypt(const AES192_ctx* ctx, size_t blocks, unsigned char* cipher16, const unsigned char* plain16);
void AES192_decrypt(const AES192_ctx* ctx, size_t blocks, unsigned char* plain16, const unsigned char* cipher16);

void AES256_init(AES256_ctx* ctx, const unsigned char* key32);
void AES256_encrypt(const AES256_ctx* ctx, size_t blocks, unsigned char* cipher16, const unsigned char* plain16);
void AES256_decrypt(const AES256_ctx* ctx, size_t blocks, unsigned char* plain16, const unsigned char* cipher16);

#endif
