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

#ifndef __mvdDatasetDescriptor_h
#define __mvdDatasetDescriptor_h

//
// Configuration include.
//// Included at first position before any other ones.
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "ConfigureMonteverdi.h"
#endif //tag=QT4-boost-compatibility


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtXml>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "mvdCore.h"
#include "mvdAbstractModel.h"
#include "mvdAlgorithm.h"
#include "mvdSerializableInterface.h"
#endif //tag=QT4-boost-compatibility


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External classes pre-declaration.
namespace
{
}

namespace mvd
{
//
// Internal classes pre-declaration.
class AbstractImageModel;
class ImageProperties;

/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class DatasetDescriptor.
 *
 * \brief WIP.
 */
class Monteverdi_EXPORT DatasetDescriptor :
    public AbstractModel,
    private SerializableInterface
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

//
// Public types.
public:

  /**
   * \class BuildContext
   * \brief WIP.
   */
  class BuildContext
  {
    //
    // Public methods.
  public:
    BuildContext( const QString& filename ) :
      m_Filename( filename )
    {
    }

    //
    // Public attributes
  public:
    QString m_Filename;
  };


//
// Public methods.
public:

  //
  // Static methods.

  /**
   */
  static inline bool IsVersionCompliant( const QString& filename );

  //
  // Instance methods.

  /** \brief Constructor. */
  DatasetDescriptor( QObject* parent =NULL );

  /** \brief Destructor. */
  virtual ~DatasetDescriptor();

  /**
   */
  inline QString GetVersionString() const;

  /**
   */
  inline QDateTime GetDate() const;

  /**
   */
  void InsertImageModel( int id,
			 const QString& imageFilename,
                         const QString& placename,
			 const void* imageSettings,
			 const QString& quicklookFilename,
			 const QString& histogramFilename,
			 const ImageProperties* properties );

  /**
   */
  inline QDomElement FirstImageElement();

  /**
   */
  inline QDomElement FirstDatasetElement();

  /**
   */
  inline QDomElement FirstImageViewContextElement();

  /**
   */
  static
    inline QDomElement NextImageSiblingElement( const QDomElement& sibling );

  /**
   */
  static
    void GetImageModel( const QDomElement& imageSibling,
			int& id,
			QString& filename,
			void* settings,
			QString& quicklookFilename,
			QString& histogramFilename,
			ImageProperties* imageProperties );

  /**
   */
  static
    void GetDatasetInformation( const QDomElement& datasetSibling,
				QString& datasetPath,
				QString& datasetAlias );

  /**
   */
  static
    void GetRenderingImageInformation( const QDomElement& datasetSibling,
                                       PointType& center,
                                       double&  zoom );
  /**
   */
  static
    void GetImagePlacename( const QDomElement& datasetSibling,
                           QString& placename);
  
  /**
   */
  bool SetImageModelSettings( int id, const void* settings );

  /**
   */
  bool SetImageModelProperties( int id, const ImageProperties* properties );

  bool UpdateDatasetAlias( const QString& newAlias);

  bool UpdateViewContext(const PointType& center, double zoom);

  bool UpdateImagePlacename( const QString & nplacename );

  /**
   */
  inline void Write( const QString& filename ) const;

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

//
// Signals.
signals:

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

//
// Protected methods.
protected:

  //
  // AbstractModel overrides.

  /** */
  virtual void virtual_BuildModel( void* context =NULL );

//
// Protected attributes.
protected:

  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

//
// Private methods.
private:

  /**
   * \brief Serialize an STL-compliant container to a QString
   */
  template< typename TInputIterator >
    inline
    static
    QString ContainerToString( const TInputIterator& first,
			       const TInputIterator& last );
			       

  /**
   * \brief Create a QDomElement containing specified text as child
   */
  inline
  QDomElement CreateTextNode( const QString& text,
                              const QString& tagName );

  /**
   * \brief Deserialize a std::vector from a QDomElement
   */
  template< typename T >
    inline
    static
    void ExtractVectorFromElement( std::vector<T>& vector,
				   QDomElement& tagName );

  /**
   * \brief Deserialize a itk::Array from a QDomElement
   */
  template< typename T >
    inline
    static
    void ExtractArrayFromElement( itk::Array<T>& array,
				  QDomElement& tagName );

  /**
   */
  inline QDomElement GetImageElement( int id );

  /**
   */
  void BuildDocument();

  /**
   */
  inline void Read( const QString& filename );

  /**
   */
  inline
    QDomElement OptionalElement( const char* name, QDomElement& parent );

  //
  // SerializableInterface overrides.
  //

  using SerializableInterface::Read;
  using SerializableInterface::Write;

  virtual void virtual_Read( QIODevice* device );

  virtual void virtual_Write( QIODevice& device ) const;


//
// Private attributes.
private:

  /**
   */
  enum Element
  {
    ELEMENT_DOCUMENT_ROOT =0,
    //
    ELEMENT_DATASET_GROUP,
    ELEMENT_DATASET_NAME,
    ELEMENT_DATASET_ALIAS,
    ELEMENT_DATASET_DATE,
    // ELEMENT_DATASET_PATH,
    // ELEMENT_DATASET_DIRECTORY,
    //
    ELEMENT_IMAGES_GROUP,
    ELEMENT_IMAGE_INFORMATION,
    ELEMENT_IMAGE_PLACENAME,
    ELEMENT_IMAGE,
    ELEMENT_QUICKLOOK,
    ELEMENT_HISTOGRAM,
    //
    ELEMENT_SETTINGS_GROUP,
    ELEMENT_RGB_CHANNELS,
    ELEMENT_GRAYSCALE,
    ELEMENT_RGB_DYNAMICS_PARAMETERS,
    ELEMENT_W_DYNAMICS_PARAMETERS,
    ELEMENT_GAMMA,
    //
    ELEMENT_PROPERTIES_GROUP,
    ELEMENT_PROPERTIES_NO_DATA,
    //
    ELEMENT_VIEW_GROUP,
    ELEMENT_VIEW_CENTER,
    ELEMENT_VIEW_ZOOM,
    //
    ELEMENT_COUNT
  };

  /**
   */
  static const char* TAG_NAMES[ ELEMENT_COUNT ];

  /**
   */
  QDomDocument m_DomDocument;

  /**
   */
  QDomElement m_RootElement;

  /**
   */
  QDomElement m_DatasetGroupElement;

  /**
   */
  QDomElement m_ImagesGroupElement;

  /**
   */
  QDomElement m_ImageViewGroupElement;


  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

//
// Slots.
private slots:
};

} // end namespace 'mvd'

/*****************************************************************************/
/* INLINE SECTION                                                            */

//
// Monteverdi deferred includes (sorted by alphabetic order)
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829  //tag=QT4-boost-compatibility
#include "mvdDatasetModel.h"
#endif //tag=QT4-boost-compatibility

namespace mvd
{

/*****************************************************************************/
inline
bool
DatasetDescriptor
::IsVersionCompliant( const QString& filename )
{
  // qDebug()
  //   << "DatasetDescriptor::IsVersionCompliant(" << filename << ")";

  DatasetDescriptor descriptor;

  descriptor.Read( filename );

  qDebug() <<
    filename << " version " << descriptor.GetVersionString();

  return
    !descriptor.GetVersionString().isEmpty() &&
    IsVersionGreaterEqual(
      descriptor.GetVersionString(),
      Monteverdi_DATA_VERSION_STRING
    );
}

/*****************************************************************************/
inline
QString
DatasetDescriptor
::GetVersionString() const
{
  assert( !m_RootElement.isNull() );

  return m_RootElement.attribute( "version" );
}

/*****************************************************************************/
QDateTime
DatasetDescriptor
::GetDate() const
{
  assert( !m_DatasetGroupElement.isNull() );

  QDomElement dateElt(
    m_DatasetGroupElement.firstChildElement( TAG_NAMES[ ELEMENT_DATASET_DATE  ] )
  );
  assert( !dateElt.isNull() );

  return QDateTime::fromString( dateElt.text(), "yyyy-MM-ddThh:mm:ss.zzz" );
}

/*****************************************************************************/
inline
void
DatasetDescriptor
::Read( const QString& filename )
{
  Read( filename, SerializableInterface::MODE_TEXT );
}

/*****************************************************************************/
inline
void
DatasetDescriptor
::Write( const QString& filename ) const
{
  Write( filename, SerializableInterface::MODE_TEXT );
}

/*****************************************************************************/
inline
QDomElement
DatasetDescriptor
::FirstImageElement()
{
  return m_ImagesGroupElement.firstChildElement(
      TAG_NAMES[ ELEMENT_IMAGE_INFORMATION ]
  );
}

/*****************************************************************************/
inline
QDomElement
DatasetDescriptor
::FirstDatasetElement()
{
  return m_DatasetGroupElement;
}

/*****************************************************************************/
inline
QDomElement
DatasetDescriptor
::FirstImageViewContextElement()
{
  return m_ImageViewGroupElement;
}

/*****************************************************************************/
inline
QDomElement
DatasetDescriptor
::GetImageElement( int id )
{
  QDomElement imageElt;

  for( imageElt = FirstImageElement();
       !imageElt.isNull() && imageElt.attribute( "id" ).toInt()!=id;
       imageElt = DatasetDescriptor::NextImageSiblingElement( imageElt ) );

  return imageElt;
}

/*****************************************************************************/
inline
QDomElement
DatasetDescriptor
::NextImageSiblingElement( const QDomElement& sibling )
{
  return sibling.nextSiblingElement( TAG_NAMES[ ELEMENT_IMAGE_INFORMATION ] );
}

/*****************************************************************************/
template< typename TInputIterator >
inline
QString
DatasetDescriptor
::ContainerToString( const TInputIterator& first,
                     const TInputIterator& last )
{
  QStringList stringList;

  for( TInputIterator it( first ); it != last; ++it )
    {
    stringList.append( ToQString( *it ) );
    }

  return stringList.join( " " );
}

/*****************************************************************************/
inline
QDomElement
DatasetDescriptor
::CreateTextNode( const QString& text,
                  const QString& tagName )
{
  assert( !tagName.isEmpty() );
  QDomElement vectorElement( m_DomDocument.createElement( tagName ) );
  assert( !vectorElement.isNull() );

  QDomText textNode( m_DomDocument.createTextNode( text ) );
  assert( !textNode.isNull() );
  
  vectorElement.appendChild( textNode );

  return vectorElement;
}

/*****************************************************************************/
template< typename T >
inline
void
DatasetDescriptor
::ExtractVectorFromElement( std::vector<T>& vector,
                            QDomElement& element )
{
  QDomNode node = element.firstChild();
  // TODO: Manage XML structure errors.
  assert( !node.isNull() );
  assert( node.isText() );

  QDomText textNode = node.toText();
  assert( !textNode.isNull() );

  QString data = textNode.data();
  QStringList stringList = data.split(" ");

  size_t size = static_cast<size_t>(stringList.size());
  vector.resize(size);
  for (size_t i = 0; i < size; ++i)
    {
      QVariant v = stringList[i];
      vector[i] = v.value<T>();
    }
}

/*****************************************************************************/
template< typename T >
inline
void
DatasetDescriptor
::ExtractArrayFromElement( itk::Array<T>& array,
                           QDomElement& element )
{
  QDomNode node = element.firstChild();
  // TODO: Manage XML structure errors.
  assert( !node.isNull() );
  assert( node.isText() );

  QDomText textNode = node.toText();
  assert( !textNode.isNull() );
  
  QString data = textNode.data();
  QStringList stringList = data.split(" ");
  
  unsigned int size = static_cast<unsigned int>(stringList.size());
  array.SetSize(size);
  for (unsigned int i = 0; i < size; ++i)
  {
    QVariant v = stringList[i];
    array[i] = v.value<T>();
  }
}

/*****************************************************************************/
inline
QDomElement
DatasetDescriptor
::OptionalElement( const char* name, QDomElement& parent )
{
  QDomElement elt( parent.firstChildElement( name ) );

  if( elt.isNull() )
    {
    elt = m_DomDocument.createElement( name );

    // TODO: Manage XML error here.
    assert( !elt.isNull() );
    }

  parent.appendChild( elt );

  return elt;
}

} // end namespace 'mvd'

#endif // __mvdDatasetDescriptor_h
