/********************************************
*
* Copyright 2011 by Sean Conner.  All Rights Reserved.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
* Comments, questions and criticisms can be sent to: sean@conman.org
*
*********************************************/

#include <stddef.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

/**********************************************************************/

static int remchar(lua_State *const L)
{
  const char *src;
  size_t      size;
  int         c;
  
  src = luaL_checklstring(L,1,&size);
  if (lua_isnumber(L,2))
    c = lua_tointeger(L,2);
  else if (lua_isstring(L,2))
  {
    const char *cc;
    cc = lua_tostring(L,2);
    c = *cc;
  }
  else
    return luaL_error(L,"you stupid, number or string!");

  char   buffer[size];
  char   *dst;
  
  for (dst = buffer ; size ; src++,size--)
    if (*src != c)
      *dst++ = *src;
  
  lua_pushlstring(L,buffer,(size_t)(dst - buffer));
  return 1;
}

/*********************************************************************/

int luaopen_org_conman_string_remchar(lua_State *const L)
{
  lua_pushcfunction(L,remchar);
  return 1;
}

/*********************************************************************/
