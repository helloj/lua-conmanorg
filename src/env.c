/********************************************
*
* Copyright 2009 by Sean Conner.  All Rights Reserved.
*
* This library is free software; you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 3 of the License, or (at your
* option) any later version.
*
* This library is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
* License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library; if not, see <http://www.gnu.org/licenses/>.
*
* Comments, questions and criticisms can be sent to: sean@conman.org
*
*********************************************/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <lua.h>
#include <lauxlib.h>

extern char **environ;

static const struct luaL_reg env[] =
{
  { NULL , NULL }
};

int luaopen_org_conman_env(lua_State *L)
{
  luaL_register(L,"org.conman.env",env);
  
  for (int i = 0 ; environ[i] != NULL ; i++)
  {
    char   *value;
    char   *eos;
    
    value = memchr(environ[i],'=',(size_t)-1);
    assert(value != NULL);
    eos   = memchr(value + 1,'\0',(size_t)-1);
    assert(eos   != NULL);
    
    lua_pushlstring(L,environ[i],(size_t)(value - environ[i]));
    lua_pushlstring(L,value + 1,(size_t)(eos - (value + 1)));
    lua_settable(L,-3);
  }
    
  return 1;
}

