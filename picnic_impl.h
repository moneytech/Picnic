/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */

#ifndef PICNIC_IMPL_H
#define PICNIC_IMPL_H

#include "lowmc.h"
#include "picnic_instances.h"
#include "picnic.h"

int impl_sign(const picnic_instance_t* pp, const uint8_t* plaintext, const uint8_t* private_key,
              const uint8_t* public_key, const uint8_t* msg, size_t msglen, uint8_t* sig,
              size_t* siglen);

int impl_verify(const picnic_instance_t* pp, const uint8_t* plaintext, const uint8_t* public_key,
                const uint8_t* msg, size_t msglen, const uint8_t* sig, size_t siglen);

#if defined(PICNIC_STATIC)
void visualize_signature(FILE* out, const picnic_instance_t* pp, const uint8_t* msg, size_t msglen,
                         const uint8_t* sig, size_t siglen);
void picnic_visualize_keys(FILE* out, const picnic_privatekey_t* private_key,
                           const picnic_publickey_t* public_key);
void picnic_visualize(FILE* out, const picnic_publickey_t* public_key, const uint8_t* msg,
                      size_t msglen, const uint8_t* sig, size_t siglen);
#endif

#endif
