/*
 * viking -- GPS Data and Topo Analyzer, Explorer, and Manager
 *
 * Copyright (C) 2003-2005, Evan Battaglia <gtoevan@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib/gi18n.h>

#include "osm.h"
#include "vikmapslayer.h"
#include "vikslippymapsource.h"
#include "vikwebtoolcenter.h"
#include "vikexttools.h"

/* initialisation */
void osm_init () {
  VikMapSource *osmarender_type = VIK_MAP_SOURCE(vik_slippy_map_source_new_with_id(12, "OpenStreetMap (Osmarender)", "tah.openstreetmap.org", "/Tiles/tile/%d/%d/%d.png"));
  VikMapSource *mapnik_type = VIK_MAP_SOURCE(vik_slippy_map_source_new_with_id( 13, "OpenStreetMap (Mapnik)", "tile.openstreetmap.org", "/%d/%d/%d.png"));
  VikMapSource *maplint_type = VIK_MAP_SOURCE(vik_slippy_map_source_new_with_id( 14, "OpenStreetMap (Maplint)", "tah.openstreetmap.org", "/Tiles/maplint.php/%d/%d/%d.png"));
  VikMapSource *cycle_type = VIK_MAP_SOURCE(vik_slippy_map_source_new_with_id( 17, "OpenStreetMap (Cycle)", "thunderflames.org/tiles/cycle/", "%d/%d/%d.png" ));

  maps_layer_register_map_source (osmarender_type);
  maps_layer_register_map_source (mapnik_type);
  maps_layer_register_map_source (maplint_type);
  maps_layer_register_map_source (cycle_type);

  // Webtools
  VikWebtoolCenter *webtool = NULL;
  webtool = vik_webtool_center_new_with_members ( _("OSM (view)"), "http://openstreetmap.org/?lat=%s&lon=%s&zoom=%d&layers=B000FTF" );
  vik_ext_tools_register ( VIK_EXT_TOOL ( webtool ) );
  g_object_unref ( webtool );

  webtool = vik_webtool_center_new_with_members ( _("OSM (edit)"), "http://www.openstreetmap.org/edit?lat=%s&lon=%s&zoom=%d" );
  vik_ext_tools_register ( VIK_EXT_TOOL ( webtool ) );
  g_object_unref ( webtool );

  webtool = vik_webtool_center_new_with_members ( _("OSM (render)"), "http://www.informationfreeway.org/?lat=%s&lon=%s&zoom=%d&layers=B0000F000F" );
  vik_ext_tools_register ( VIK_EXT_TOOL ( webtool ) );
  g_object_unref ( webtool );
}

