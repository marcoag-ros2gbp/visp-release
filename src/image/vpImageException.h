/****************************************************************************
 *
 * $Id: vpImageException.h 4649 2014-02-07 14:57:11Z fspindle $
 *
 * This file is part of the ViSP software.
 * Copyright (C) 2005 - 2014 by INRIA. All rights reserved.
 * 
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * ("GPL") version 2 as published by the Free Software Foundation.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact INRIA about acquiring a ViSP Professional 
 * Edition License.
 *
 * See http://www.irisa.fr/lagadic/visp/visp.html for more information.
 * 
 * This software was developed at:
 * INRIA Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 * http://www.irisa.fr/lagadic
 *
 * If you have questions regarding the use of this file, please contact
 * INRIA at visp@inria.fr
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 * Description:
 * Exceptions that can be emited by the vpImage class and its derivates.
 *
 * Authors:
 * Eric Marchand
 *
 *****************************************************************************/

#ifndef __vpImageException_H
#define __vpImageException_H


/* ------------------------------------------------------------------------- */
/* --- INCLUDE ------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */


/* \file vpImageException.h
   \brief error that can be emited by the vpImage class and its derivates
 */
/* Classes standards. */

#include <visp/vpConfig.h>
#include <visp/vpException.h>

#include <iostream>                /* Classe std::ostream.    */
#include <string>                  /* Classe string.     */

/* ------------------------------------------------------------------------- */
/* --- CLASS --------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

/*!

  \class vpImageException

  \ingroup Exception

  \brief Error that can be emited by the vpImage class and its derivates.
 */
class VISP_EXPORT vpImageException : public vpException
{
  public:
    /*!
    \brief Lists the possible error than can be emmited while calling
    vpImage member
   */
    enum errorImageCodeEnum
    {
      ioError,
      noFileNameError,
      notInitializedError,
      incorrectInitializationError,
      notInTheImage
    } ;

  public:
    vpImageException (const int id, const char* format, ...)
    {
      this->code = id;
      va_list args;
      va_start(args, format);
      setMessage(format, args);
      va_end (args);
    }
    vpImageException (const int id, const std::string & msg)
      : vpException(id, msg){ ; }
    vpImageException (const int id)
      : vpException(id){ ; }
};

#endif