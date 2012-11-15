/*********************************************************************
*
* Copyright 2010 by Sean Conner.  All Rights Reserved.
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
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <assert.h>

#include <lua.h>
#include <lauxlib.h>

/************************************************************************/

static int math_randomseed(lua_State *const L)
{
  FILE         *fp;
  unsigned int  seed;
  
  assert(L != NULL);  
  
  if (lua_toboolean(L,1))
  {
    fp = fopen("/dev/random","rb");
    if (fp == NULL)
      return luaL_error(L,"The NSA is keeping you from seeding your RNG");
  }
  else
  {
    fp = fopen("/dev/urandom","rb");
    if (fp == NULL)
      return luaL_error(L,"cannot seed RNG");
  }
  
  fread(&seed,sizeof(seed),1,fp);
  fclose(fp);
  srand(seed);
  lua_pushnumber(L,seed);
  return 1;
}

/**************************************************************************/

static int math_idiv(lua_State *const L)
{
  ldiv_t result;
  
  result = ldiv(
  		 luaL_checkinteger(L,1),
  		 luaL_checkinteger(L,2)
  	       );
  lua_pushinteger(L,result.quot);
  lua_pushinteger(L,result.rem);
  return 2;
}

/**************************************************************************/

static int math_div(lua_State *const L)
{
  double numer = luaL_checknumber(L,1);
  double denom = luaL_checknumber(L,2);
  
  if (denom == 0.0)
  {
    if (numer < 0.0)
    {
      lua_pushnumber(L,-HUGE_VAL);
      lua_pushnumber(L,-HUGE_VAL);
    }
    else
    {
      lua_pushnumber(L,HUGE_VAL);
      lua_pushnumber(L,HUGE_VAL);
    }
  }
  else
  {
  
    lua_pushnumber(L,numer / denom);
    lua_pushnumber(L,fmod(numer,denom));
  }
  return 2;  
}

/************************************************************************/

static const struct luaL_Reg reg_math[] =
{
  { "randomseed"	, math_randomseed },
  { "idiv"		, math_idiv	  },
  { "div"		, math_div	  },
  { NULL		, NULL		  }
};

int luaopen_org_conman_math(lua_State *L)
{
  luaL_register(L,"org.conman.math",reg_math);
  
  lua_pushliteral(L,"Copyright 2011 by Sean Conner.  All Rights Reserved.");
  lua_setfield(L,-2,"_COPYRIGHT");

  lua_pushliteral(L,"GNU-GPL 3");
  lua_setfield(L,-2,"_LICENSE");
  
  lua_pushliteral(L,"Some useful math routines no in stock Lua");
  lua_setfield(L,-2,"_DESCRIPTION");
  
  lua_pushliteral(L,"0.0.3");
  lua_setfield(L,-2,"_VERSION");
  
  return 1;
}

/**************************************************************************/

