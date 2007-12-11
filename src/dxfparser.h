#include <dxflib/dl_creationadapter.h>

/**
 *  \class DxfParser
 *  \brief Parsea el fichero dxf de autocad
 *   
 *  \par 
 */
class DxfParser: public DL_CreationAdapter
{
public:
    /** variable temporal para guardar el nombre del bloque */
    string nombre;

    /** constructor */
    DxfParser();

    /** A&ntilde;ade una nueva Capa a la estructura Mapa */
    virtual void addLayer   (const DL_LayerData& data);

    /** A&ntilde;ade una nueva Linea a la estructura Mapa*/
    virtual void addLine    (const DL_LineData& data);

    /** A&ntilde;ade una nueva Polilinea a la estructura Mapa*/
    virtual void addPolyline    (const DL_PolylineData& data);

    /** A&ntilde;ade un nuevo Punto a la estructura Mapa*/
    virtual void addVertex  (const DL_VertexData& data);

    /** A&ntilde;ade un nuevo Bloque a la estructura Mapa*/
    virtual void addBlock(const DL_BlockData& data);
};


