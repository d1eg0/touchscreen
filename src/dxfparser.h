/**
 *       @file  dxfparser.h
 *
 *     @author  Diego García , kobydiego@gmail.com
 *
 *   @internal
 *     Company  Universitat de les Illes Balears
 *   Copyright  Copyright (c) 2009, Diego García
 *
 *
 *  This file is part of TouchScreenGUI.
 *  TouchScreenGUI is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TouchScreenGUI is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TouchScreenGUI; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  http://www.gnu.org/copyleft/gpl.html
 *
 * =====================================================================================
 */

#include <dxflib/dl_creationadapter.h>

/**
 *  \class DxfParser
 *  \brief Parseador para el fichero DXF.
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


