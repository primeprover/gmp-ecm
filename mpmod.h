/* Header for modular multiplication.

  Copyright 2012 Paul Zimmermann.

  This file is part of the ECM Library.

  The ECM Library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or (at your
  option) any later version.

  The ECM Library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with the ECM Library; see the file COPYING.LIB.  If not, write to
  the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
  MA 02110-1301, USA.
*/

#define MPMOD_MULREDC 0 /* assembly combined mulredc */
#define MPMOD_MUL_REDC1 1 /* mpn_mul_n or mpn_sqr followed by mpn_redc_1 */
#define MPMOD_MUL_REDC2 2 /* mpn_mul_n or mpn_sqr followed by mpn_redc_2 */
#define MPMOD_MUL_REDC3 3 /* mpn_mul_n or mpn_sqr followed by ecm_redc3 */
#define MPMOD_MUL_REDC_C 4 /* mpn_mul_n or mpn_sqr followed by plain C redc */