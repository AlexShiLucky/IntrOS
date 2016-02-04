/******************************************************************************

    @file    IntrOS: os_flg.h
    @author  Rajmund Szymanski
    @date    04.02.2016
    @brief   This file contains definitions for IntrOS.

 ******************************************************************************

    IntrOS - Copyright (C) 2013 Rajmund Szymanski.

    This file is part of IntrOS distribution.

    IntrOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published
    by the Free Software Foundation; either version 3 of the License,
    or (at your option) any later version.

    IntrOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.

 ******************************************************************************/

#pragma once

#include <oskernel.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : flag                                                                                           *
 *                                                                                                                    *
 **********************************************************************************************************************/

#define flgOne       ( 0U )
#define flgAll       ( 1U )

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : OS_FLG                                                                                         *
 *                                                                                                                    *
 * Description       : define and initilize a flag object                                                             *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   flg             : name of a pointer to flag object                                                               *
 *                                                                                                                    *
 **********************************************************************************************************************/

#define     OS_FLG( flg )                     \
               flg_t flg##__flg = _FLG_INIT(); \
               flg_id flg = & flg##__flg

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : static_FLG                                                                                     *
 *                                                                                                                    *
 * Description       : define and initilize a static flag object                                                      *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   flg             : name of a pointer to flag object                                                               *
 *                                                                                                                    *
 **********************************************************************************************************************/

#define static_FLG( flg )                     \
        static flg_t flg##__flg = _FLG_INIT(); \
        static flg_id flg = & flg##__flg

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : FLG_INIT                                                                                       *
 *                                                                                                                    *
 * Description       : create and initilize a flag object                                                             *
 *                                                                                                                    *
 * Parameters        : none                                                                                           *
 *                                                                                                                    *
 * Return            : flag object                                                                                    *
 *                                                                                                                    *
 * Note              : use only in 'C' code                                                                           *
 *                                                                                                                    *
 **********************************************************************************************************************/

#define                FLG_INIT( ) \
                      _FLG_INIT()

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : FLG_CREATE                                                                                     *
 *                                                                                                                    *
 * Description       : create and initilize a flag object                                                             *
 *                                                                                                                    *
 * Parameters        : none                                                                                           *
 *                                                                                                                    *
 * Return            : pointer to flag object                                                                         *
 *                                                                                                                    *
 * Note              : use only in 'C' code                                                                           *
 *                                                                                                                    *
 **********************************************************************************************************************/

#ifndef __cplusplus
#define                FLG_CREATE( ) \
               &(flg_t)FLG_INIT()
#endif

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : flg_wait                                                                                       *
 *                                                                                                                    *
 * Description       : wait indefinitly on flag object until requested flags have been set                            *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   flg             : pointer to flag object                                                                         *
 *   flags           : all flags to wait                                                                              *
 *   mode            : waiting mode                                                                                   *
 *                     flgOne:    wait for any flags to be set                                                        *
 *                     flgAll:    wait for all flags to be set                                                        *
 *                                                                                                                    *
 * Return            : none                                                                                           *
 *                                                                                                                    *
 **********************************************************************************************************************/

              void     flg_wait( flg_id flg, unsigned flags, unsigned mode );

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : flg_take                                                                                       *
 *                                                                                                                    *
 * Description       : don't wait on flag object until requested flags have been set                                  *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   flg             : pointer to flag object                                                                         *
 *   flags           : all flags to wait                                                                              *
 *   mode            : waiting mode                                                                                   *
 *                     flgOne:    wait for any flags to be set                                                        *
 *                     flgAll:    wait for all flags to be set                                                        *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : requested flags have been set                                                                  *
 *   'another'       : requested flags have not been set                                                              *
 *                                                                                                                    *
 **********************************************************************************************************************/

              unsigned flg_take( flg_id flg, unsigned flags, unsigned mode );

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : flg_give                                                                                       *
 *                                                                                                                    *
 * Description       : set given flags in flag object                                                                 *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   flg             : pointer to flag object                                                                         *
 *   flags           : all flags to set                                                                               *
 *                                                                                                                    *
 * Return            : none                                                                                           *
 *                                                                                                                    *
 **********************************************************************************************************************/

              void     flg_give( flg_id flg, unsigned flags );

#ifdef __cplusplus
}
#endif
