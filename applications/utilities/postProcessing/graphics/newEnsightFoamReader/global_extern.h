/*--------------------------------------------------------------*/
/* Header file for EnSight External Reader DSO Library Routines */
/*--------------------------------------------------------------*/
/*  *************************************************************
 *   Copyright 1998 Computational Engineering International, Inc.
 *   All Rights Reserved.
 *
 *        Restricted Rights Legend
 *
 *   Use, duplication, or disclosure of this
 *   software and its documentation by the
 *   Government is subject to restrictions as
 *   set forth in subdivision [(b)(3)(ii)] of
 *   the Rights in Technical Data and Computer
 *   Software clause at 52.227-7013.
 *  *************************************************************
 */
#ifndef GLOBAL_EXTERN_H
#define GLOBAL_EXTERN_H

/*--------------------------------
 * Set the reader version define
 * (only one can be set at a time)
 *--------------------------------*/
#define USERD_API_203

/*----------------------------------------
 * Set this appropriately:
 *  DO_ENSIGHT  if using for EnSight itself
 *  DO_READER   if using in a reader
 *----------------------------------------*/
#if 1
#define DO_READER
#else
#define DO_ENSIGHT
#endif

/*---------------------------------------*/
/* True/False and Error conditions, etc. */
/*---------------------------------------*/
#define Z_ERR                  (-1)          /*Error return value.*/
#define Z_OK                    (1)          /*Success return value.*/
#define Z_UNDEF                 (2)          /*Undefined return value.*/

#define Z_NOT_IMPLEMENTED       (3)          /*Routine not implemented*/
                                             /*(currently only checked for */
                                             /* get_var_value_at_specific routine)*/ 
#ifndef TRUE
# define TRUE                   (1)
# define FALSE                  (0)
#endif

#define Z_BUFL                 (80)          /* Typical string length */

#define Z_COMPX                 (0)          /* x component */
#define Z_COMPY                 (1)          /* y component */
#define Z_COMPZ                 (2)          /* z component */

#define Z_STATIC                (0)          /* static geometry          */
#define Z_CHANGE_COORDS         (1)          /* coordinate changing only */
#define Z_CHANGE_CONN           (2)          /* conectivity changing     */

#define Z_GEOM                  (0)          /* Geometry type */
#define Z_VARI                  (1)          /* Variable type */

#define Z_SAVE_ARCHIVE          (0)          /* Save archive    */
#define Z_REST_ARCHIVE          (1)          /* Restore archive */

#define Z_MAX_USERD_NAME        (20)         /* max length of reader name */

#define Z_PER_NODE              (4)          /* At Nodes Variable classif.   */
#define Z_PER_ELEM              (1)          /* At Elements Variable classif.*/

#define Z_MAX_SETS              (300)

#ifndef GLOBALDEFS_H
/*-----------------------------------*/
/* Unstructured coordinate structure */
/*-----------------------------------*/
typedef struct {
  float xyz[3];
}CRD;
#endif

/*----------------*/ 
/* Variable Types */
/*----------------*/ 
enum z_var_type
{
  Z_CONSTANT,
  Z_SCALAR,
  Z_VECTOR,
  Z_TENSOR,
  Z_TENSOR9,
  MAX_Z_VAR_TYPES
};

/*---------------
 * Element Types
 *---------------
 * If you mess with these, you must also
 * change the get_z_maxtype
 *            to_z_elem_type
 *            to_int_elem_type routines
 * in userd_read.c
 *----------------------------------------*/
#if (defined USERD_API_100 || defined USERD_API_200) && defined DO_READER
enum z_elem_types {
  Z_POINT,         /* 00:  1 node point element */
  Z_BAR02,         /* 01:  2 node bar           */
  Z_BAR03,         /* 02:  3 node bar           */
  Z_TRI03,         /* 03:  3 node triangle      */
  Z_TRI06,         /* 04:  6 node triangle      */
  Z_QUA04,         /* 05:  4 node quad          */
  Z_QUA08,         /* 06:  8 node quad          */
  Z_TET04,         /* 07:  4 node tetrahedron   */
  Z_TET10,         /* 08: 10 node tetrahedron   */
  Z_PYR05,         /* 09:  5 node pyramid       */
  Z_PYR13,         /* 10: 13 node pyramid       */
  Z_PEN06,         /* 11:  6 node pentahedron   */
  Z_PEN15,         /* 12: 15 node pentahedron   */
  Z_HEX08,         /* 13:  8 node hexahedron    */
  Z_HEX20,         /* 14: 20 node hexahedron    */
  Z_MAXTYPE
};

#elif defined USERD_API_201 && defined DO_READER
enum z_elem_types {
  Z_POINT,         /* 00:  1 node point element              */
  Z_G_POINT,       /* 01:  1 node point element (ghost call) */
  Z_BAR02,         /* 02:  2 node bar                        */
  Z_G_BAR02,       /* 03:  2 node bar           (ghost cell) */
  Z_BAR03,         /* 04:  3 node bar                        */
  Z_G_BAR03,       /* 05:  3 node bar           (ghost cell) */
  Z_TRI03,         /* 06:  3 node triangle                   */
  Z_G_TRI03,       /* 07:  3 node triangle      (ghost cell) */
  Z_TRI06,         /* 08:  6 node triangle                   */
  Z_G_TRI06,       /* 09:  6 node triangle      (ghost cell) */
  Z_QUA04,         /* 10:  4 node quad                       */
  Z_G_QUA04,       /* 11:  4 node quad          (ghost cell) */
  Z_QUA08,         /* 12:  8 node quad                       */
  Z_G_QUA08,       /* 13:  8 node quad          (ghost cell) */
  Z_TET04,         /* 14:  4 node tetrahedron                */
  Z_G_TET04,       /* 15:  4 node tetrahedron   (ghost cell) */
  Z_TET10,         /* 16: 10 node tetrahedron                */
  Z_G_TET10,       /* 17: 10 node tetrahedron   (ghost cell) */
  Z_PYR05,         /* 18:  5 node pyramid                    */
  Z_G_PYR05,       /* 19:  5 node pyramid       (ghost cell) */
  Z_PYR13,         /* 20: 13 node pyramid                    */
  Z_G_PYR13,       /* 21: 13 node pyramid       (ghost cell) */
  Z_PEN06,         /* 22:  6 node pentahedron                */
  Z_G_PEN06,       /* 23:  6 node pentahedron   (ghost cell) */
  Z_PEN15,         /* 24: 15 node pentahedron                */
  Z_G_PEN15,       /* 25: 15 node pentahedron   (ghost cell) */
  Z_HEX08,         /* 26:  8 node hexahedron                 */
  Z_G_HEX08,       /* 27:  8 node hexahedron    (ghost cell) */
  Z_HEX20,         /* 28: 20 node hexahedron                 */
  Z_G_HEX20,       /* 29: 20 node hexahedron    (ghost cell) */
  Z_MAXTYPE
};

#else
enum z_elem_types {
  Z_POINT,         /* 00:  1 node point element              */
  Z_G_POINT,       /* 01:  1 node point element (ghost call) */
  Z_BAR02,         /* 02:  2 node bar                        */
  Z_G_BAR02,       /* 03:  2 node bar           (ghost cell) */
  Z_BAR03,         /* 04:  3 node bar                        */
  Z_G_BAR03,       /* 05:  3 node bar           (ghost cell) */
  Z_TRI03,         /* 06:  3 node triangle                   */
  Z_G_TRI03,       /* 07:  3 node triangle      (ghost cell) */
  Z_TRI06,         /* 08:  6 node triangle                   */
  Z_G_TRI06,       /* 09:  6 node triangle      (ghost cell) */
  Z_QUA04,         /* 10:  4 node quad                       */
  Z_G_QUA04,       /* 11:  4 node quad          (ghost cell) */
  Z_QUA08,         /* 12:  8 node quad                       */
  Z_G_QUA08,       /* 13:  8 node quad          (ghost cell) */
  Z_TET04,         /* 14:  4 node tetrahedron                */
  Z_G_TET04,       /* 15:  4 node tetrahedron   (ghost cell) */
  Z_TET10,         /* 16: 10 node tetrahedron                */
  Z_G_TET10,       /* 17: 10 node tetrahedron   (ghost cell) */
  Z_PYR05,         /* 18:  5 node pyramid                    */
  Z_G_PYR05,       /* 19:  5 node pyramid       (ghost cell) */
  Z_PYR13,         /* 20: 13 node pyramid                    */
  Z_G_PYR13,       /* 21: 13 node pyramid       (ghost cell) */
  Z_PEN06,         /* 22:  6 node pentahedron                */
  Z_G_PEN06,       /* 23:  6 node pentahedron   (ghost cell) */
  Z_PEN15,         /* 24: 15 node pentahedron                */
  Z_G_PEN15,       /* 25: 15 node pentahedron   (ghost cell) */
  Z_HEX08,         /* 26:  8 node hexahedron                 */
  Z_G_HEX08,       /* 27:  8 node hexahedron    (ghost cell) */
  Z_HEX20,         /* 28: 20 node hexahedron                 */
  Z_G_HEX20,       /* 29: 20 node hexahedron    (ghost cell) */
  Z_NSIDED,        /* 30:  n node polygon                    */
  Z_G_NSIDED,      /* 31:  n node polygon       (ghost cell) */
  Z_NFACED,        /* 32:  n faced polyhedron                */
  Z_G_NFACED,      /* 33:  n faced polyhedron   (ghost cell) */
  Z_MAXTYPE
};

#endif

enum z_node_ids_opt
{
  Z_NO_NODE_IDS,
  Z_ASSIGN_NODE_IDS,
  Z_GIVEN_NODE_IDS
};

enum z_element_ids_opt
{
  Z_NO_ELEMENT_IDS,
  Z_ASSIGN_ELEMENT_IDS,
  Z_GIVEN_ELEMENT_IDS
};


/*-------------------------------*/
/* Unstructured/Structured types */
/*-------------------------------*/
enum z_structured_defs
{
  Z_UNSTRUCTURED,         /* for unstructured part */
  Z_STRUCTURED,           /* for structured (non-iblanked) part */
  Z_IBLANKED,             /* for structured iblanked part */
  Z_MAXMESHTYPES
};

/*----------------------------*/
/* Structured Iblanking types */
/*----------------------------*/
enum z_iblank_domain
{
  Z_EXT,                  /* Exterior */
  Z_INT,                  /* Interior */
  Z_BND,                  /* Boundary */
  Z_INTBND,               /* Internal boundary/baffle */
  Z_SYM,                  /* Symmetry surface */
  Z_NO_OF_IBLANK_DOMAIN_ITEMS
};


/*-----------------------------------*/
/* Dataset Query file info Structure */
/*-----------------------------------*/
#define Z_MAXFILENP    255  /* Max file name and path.*/
#define Z_MAXTIMLEN     40  /* Max time str length */
#define Z_BUFLEN        82  /* Allocated length of the f_desc strings */
typedef struct {
    char name[Z_MAXFILENP];
    long sizeb;
    char timemod[Z_MAXTIMLEN];
    int num_d_lines;
    char **f_desc;
} Z_QFILES;

/*-------------------------------------------
 * Mixed Material enum
 *
 * (Must be comparable to material_file_index
 *  in mat_defs.h of EnSight server)
 *--------------------------------------------*/
enum  z_material_file_index
{
  Z_MAT_INDEX,
  Z_MIX_INDEX,
  Z_MIX_VALUE,
  Z_NUM_MAT_FILES
};


/*----------------------------------------------------------
 * For readers, we need to include the prototype header file
 *----------------------------------------------------------*/
#if defined DO_READER
#include "global_extern_proto.h"
#endif

// #define ENSIGHTDEBUG 1


     
/*--------------------------------------------------------------------*/
#endif /*GLOBAL_EXTERN_H*/

