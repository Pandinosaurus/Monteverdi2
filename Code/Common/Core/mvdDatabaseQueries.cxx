/*=========================================================================

  Program:   Monteverdi
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "mvdDatabaseQueries.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtSql>

//
// System includes (sorted by alphabetic order)
// #include <cstdarg>

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "Core/mvdDatabaseConnection.h"

namespace mvd
{
/*
  TRANSLATOR mvd::DatabaseQueries

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/

/*****************************************************************************/
/* MACROS                                                                    */

/*****************************************************************************/
/* CONSTANTS                                                                 */

namespace
{
} // end of anonymous namespace.


/*****************************************************************************/
/* FUNCTIONS IMPLEMENTATION SECTION                                          */
/*****************************************************************************/
SqlId
GetNodeFields( const QSqlQuery& query,
               QString* label,
               SqlId* parentId,
               SqlId* tagId,
               int* level,
               QString* path )
{
  QUERY_DEBUG_FIELDS( query );


  if( parentId!=NULL )
    {
    assert( query.value( 1 ).type()==QVariant::LongLong );
    *parentId = query.value( 1 ).toLongLong();
    }

  if( tagId!=NULL )
    {
    assert( query.value( 2 ).type()==QVariant::LongLong );
    *tagId = query.value( 2 ).toLongLong();
    }

  if( label!=NULL )
    {
    assert( query.value( 3 ).type()==QVariant::String );
    *label = query.value( 3 ).toString();
    }

  if( level!=NULL )
    {
    assert( query.value( 4 ).type()==QVariant::LongLong );
    *level = static_cast< int >( query.value( 4 ).toLongLong() );
    }

  if( path!=NULL )
    {
    assert( query.value( 5 ).type()==QVariant::String );
    *path = query.value( 5 ).toString();
    }


  assert( query.value( 0 ).type()==QVariant::LongLong );
  return query.value( 0 ).toLongLong();
}

/*****************************************************************************/
SqlId
GetChildNodeFields( const QSqlQuery& query,
                    QString* label,
                    SqlId* parentId,
                    SqlId* tagId,
                    int* level,
                    QString* path )
{
#if 1
  return GetNodeFields( query, label, parentId, tagId, level, path );

#else
  QUERY_DEBUG_FIELDS( query );


  if( parentId!=NULL )
    {
    assert( query.value( 1 ).type()==QVariant::LongLong );
    *parentId = query.value( 1 ).toLongLong();
    }

  if( tagId!=NULL )
    {
    assert( query.value( 2 ).type()==QVariant::LongLong );
    *tagId = query.value( 2 ).toLongLong();
    }

  if( label!=NULL )
    {
    assert( query.value( 3 ).type()==QVariant::String );
    *label = query.value( 3 ).toString();
    }

  if( level!=NULL )
    {
    assert( query.value( 4 ).type()==QVariant::LongLong );
    *level = query.value( 4 ).toInt();
    }

  if( path!=NULL )
    {
    assert( query.value( 5 ).type()==QVariant::String );
    *path = query.value( 5 ).toString();
    }

  assert( query.value( 0 ).type()==QVariant::LongLong );
  return query.value( 0 ).toLongLong();

#endif
}

/*****************************************************************************/
SqlId
GetDatasetFields( const QSqlQuery& query,
                  QString* hash,
                  QString* alias )
{
  QUERY_DEBUG_FIELDS( query );


  if( hash!=NULL )
    {
    assert( query.value( 1 ).type()==QVariant::String );
    *hash = query.value( 1 ).toString();
    }

  if( alias!=NULL )
    {
    assert( query.value( 2 ).type()==QVariant::String );
    *alias = query.value( 2 ).toString();
    }


  assert( query.value( 0 ).type()==QVariant::LongLong );
  return query.value( 0 ).toLongLong();
}

/*****************************************************************************/
/* STATIC IMPLEMENTATION SECTION                                             */

/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */
/*******************************************************************************/
DatabaseQueries
::DatabaseQueries( QObject* parent ) :
  QObject( parent )
{
}

/*******************************************************************************/
DatabaseQueries
::~DatabaseQueries()
{
}

/*******************************************************************************/
/* SLOTS                                                                       */
/*******************************************************************************/

} // end namespace 'mvd'
