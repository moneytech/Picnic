/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "lowmc_pars.h"

#include "macros.h"
#include "mzd_additional.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


#if defined(MUL_M4RI)
bool lowmc_init(lowmc_t* lowmc) {
  if (!lowmc) {
    return false;
  }

  if (lowmc->n - 3 * lowmc->m < 2 || lowmc->n != lowmc->k) {
    return false;
  }

  lowmc->k0_lookup = mzd_precompute_matrix_lookup(lowmc->k0_matrix);
#if defined(REDUCED_LINEAR_LAYER)
  lowmc->precomputed_non_linear_part_lookup =
      mzd_precompute_matrix_lookup(lowmc->precomputed_non_linear_part_matrix);
#endif
  for (unsigned int i = 0; i < lowmc->r; ++i) {
    lowmc->rounds[i].l_lookup = mzd_precompute_matrix_lookup(lowmc->rounds[i].l_matrix);
#if !defined(REDUCED_LINEAR_LAYER)
    lowmc->rounds[i].k_lookup = mzd_precompute_matrix_lookup(lowmc->rounds[i].k_matrix);
#endif
  }

  return true;
}
#endif

void lowmc_clear(lowmc_t* lowmc) {
  for (unsigned int i = 0; i < lowmc->r; ++i) {
#if defined(MUL_M4RI)
#if !defined(REDUCED_LINEAR_LAYER)
    mzd_local_free(lowmc->rounds[i].k_lookup);
#endif
    mzd_local_free(lowmc->rounds[i].l_lookup);
#endif
  }
#if defined(MUL_M4RI)
  mzd_local_free(lowmc->k0_lookup);
#if defined(REDUCED_LINEAR_LAYER)
  mzd_local_free(lowmc->precomputed_non_linear_part_lookup);
#endif
#endif
}
