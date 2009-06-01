#include "server.h"
#include <mysql/mysql.h>

MYSQL *connection;
MYSQL_RES *results;
MYSQL_ROW row;

cvar_t *sv_mysql;
cvar_t *sv_mysqlhost;
cvar_t *sv_mysqldatabase;
cvar_t *sv_mysqlusername;
cvar_t *sv_mysqlpassword;

void sv_mysql_init( void ) {
  sv_mysql = Cvar_Get("sv_mysql", "0", CVAR_SERVERINFO );
  sv_mysqlhost = Cvar_Get("sv_mysqlhost", "localhost", CVAR_ARCHIVE | CVAR_SERVERINFO );
  sv_mysqldatabase = Cvar_Get("sv_mysqldatabase", "tremulous", CVAR_ARCHIVE | CVAR_SERVERINFO );
  sv_mysqlusername = Cvar_Get("sv_mysqlusername", "tremulous", CVAR_ARCHIVE | CVAR_SERVERINFO );
  sv_mysqlpassword = Cvar_Get("sv_mysqlpassword", "", CVAR_ARCHIVE | CVAR_SERVERINFO );

  connection = mysql_init( NULL );

  if( !mysql_real_connect( connection, sv_mysqlhost->string, sv_mysqlusername->string, sv_mysqlpassword->string, sv_mysqldatabase->string, 0, NULL, 0) ) {
    Com_Printf( "^3WARNING:^7 MySQL loading failed: %s^7\n", mysql_error( connection ) );
    Cvar_Set( "sv_mysql", "0" );
  }

  Com_Printf( "MySQL loaded version: %s\n", mysql_get_client_info() );
  Cvar_Set( "sv_mysql", "1" );
}

void sv_mysql_shutdown( void ) {
  mysql_close( connection );
  Com_Printf( "MySQL Closed\n" );
  Cvar_Set( "sv_mysql", "0" );
}

qboolean sv_mysql_runquery( char *query ) {
  if( sv_mysql->integer == 1 ) {
    if( mysql_query( connection, query ) ) {
      Com_Printf( "^3WARNING:^7 MySQL Query failed: %s^7\n", mysql_error( connection ) );
      return qfalse;
    }
    results = mysql_store_result( connection );
    return qtrue;
  }
  return qfalse;
}

void sv_mysql_finishquery( void ) {
  if( sv_mysql->integer == 1 ) {
    if( results ) {
      mysql_free_result( results );
    }
  }
}

void sv_mysql_cleanstring( const char *in, char *out, int len ) {
  if( sv_mysql->integer == 1 ) {
    mysql_real_escape_string( connection, out, in, len );
  }
}

qboolean sv_mysql_fetchrow( void ) {
  if( sv_mysql->integer == 1 ) {
    if( results ) {
      row = mysql_fetch_row( results );
      if( !row ) {
        return qfalse;
      }
      return qtrue;
    }
  }
  return qfalse;
}

int sv_mysql_rowcount( void ) {
  if( sv_mysql->integer == 1 ) {
    if( results ) {
      return mysql_num_rows( results );
    }
  }
  return -1;
}

int sv_mysql_affectedrows( void ) {
  if( sv_mysql->integer == 1 ) {
    return mysql_affected_rows( connection );
  }
  return -1;
}

void sv_mysql_fetchfieldbyID( int id, char *buffer, int len ) {
  if( sv_mysql->integer == 1 ) {
    if( row[ id ] ) {
      Q_strncpyz( buffer, row[ id ], len );
    } else {
      //do nothing
    }
  }
}

void sv_mysql_fetchfieldbyName( const char *name, char *buffer, int len ) {
  MYSQL_FIELD *fields;
  int num_fields;
  int i;

  if( sv_mysql->integer == 1 ) {
    if( results ) {
      num_fields = mysql_num_fields( results );
      fields = mysql_fetch_fields( results );

      for( i = 0; i < num_fields; i++ ) {
        if( !strcmp( fields[i].name, name ) ) {
          if( row[ i ] ) {
            Q_strncpyz( buffer, row[ i ], len );
            return;
          }
        }
      }
    }
  }
}

int sv_mysql_fieldcount( void ) {
  int num_fields;

  if( sv_mysql->integer == 1 ) {
    if( results ) {
      num_fields = mysql_num_fields( results );
      return num_fields;
    }
  }
  return 0;
}
