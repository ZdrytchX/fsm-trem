#include "database.h"
#include <mysql/mysql.h>

#define MAX_QUERYS_RESULTS 10

MYSQL *connection;

typedef struct {
  MYSQL_RES *results;
  MYSQL_ROW row;
} db_MySQL_querylist_t;

db_MySQL_querylist_t querylist[ MAX_QUERYS_RESULTS ];

int db_MySQL_GetFreeQueryID( void ) {
  int i;
  
  for( i = 0; i < MAX_QUERYS_RESULTS; i++ ) {
    if( !querylist[ i ].results ) {
      return i;
    }
  }
  return -1;
}

qboolean db_MySQL_Init( dbinterface_t *dbi ) {

  dbi->DBConnect = db_MySQL_Connect;
  dbi->DBStatus= db_MySQL_DBStatus;
  dbi->DBDisconnect = db_MySQL_Disconnect;

  dbi->RunQuery = db_MySQL_RunQuery;
  dbi->FinishQuery = db_MySQL_FinishQuery;

  dbi->NextRow = db_MySQL_NextRow;
  //dbi->RowID = db_MySQL_RowID;
  //dbi->GotoRowID = db_MySQL_GotoRowID;
  dbi->RowCount = db_MySQL_RowCount;

  dbi->GetFieldByID = db_MySQL_GetFieldByID;
  dbi->GetFieldByName = db_MySQL_GetFieldByName;
  dbi->GetFieldByID_int = db_MySQL_GetFieldByID_int;
  dbi->GetFieldByName_int = db_MySQL_GetFieldByName_int;
  dbi->FieldCount = db_MySQL_FieldCount;

  dbi->CleanString = db_MySQL_CleanString;

  //dbi->InitDB = db_MySQL_Init;
  //dbi->DestroyDB = ;

  return qtrue;
}

//==============================================
//        MYSQL Connecting related functions
//==============================================

void db_MySQL_Connect( void ) {

  //init mysql
  connection = mysql_init( NULL );

  //set mysql options
  //mysql_options( connection, MYSQL_OPT_RECONNECT, 1); //enable connection reconnect

  //attempt to connect to mysql
  if( !mysql_real_connect( connection, db_address->string, db_username->string, db_password->string, db_database->string, 0, NULL, 0) ) {
    Com_Printf( "WARNING: MySQL loading failed: %s.\n", mysql_error( connection ) );
    return;
  }

  Com_Printf( "MySQL loaded.\n" );
}

void db_MySQL_DBStatus( void ) {
  
}

void db_MySQL_Disconnect( void ) {
  mysql_close( connection );
  Com_Printf( "MySQL Unloaded.\n" );
}

//==============================================
//        MYSQL Query related functions
//==============================================

int db_MySQL_RunQuery( const char *query ) {
  int queryid;
  if( connection ) {
    if( mysql_query( connection, query ) ) {
      Com_Printf( "WARNING: MySQL Query failed: %s\n", mysql_error( connection ) );
      return -1;
    }
  
    queryid = db_MySQL_GetFreeQueryID();
    if( queryid >= 0 ) {
      querylist[ queryid ].results = mysql_store_result( connection );
      Com_DPrintf( "DEV: MySQL using query ID %i.\n", queryid );
      return queryid;
    }
  }
  return -1;
}

void db_MySQL_FinishQuery( int queryid ) {
  if( querylist[ queryid ].results ) {
    mysql_free_result( querylist[ queryid ].results );
    querylist[ queryid ].results = NULL;
    Com_DPrintf( "DEV: MySQL Freeing query ID %i.\n", queryid );
  }
}

//==============================================
//        MYSQL ROW related functions
//==============================================

qboolean db_MySQL_NextRow( int queryid ) {
  if( querylist[ queryid ].results ) {
    //get next row
    querylist[ queryid ].row = mysql_fetch_row( querylist[ queryid ].results );
    //if its not valid return false
    if( !querylist[ queryid ].row ) {
      return qfalse;
    }
    return qtrue;
  }
  return qfalse;
}

int db_MySQL_RowCount( int queryid ) {
  if( querylist[ queryid ].results )
    return mysql_num_rows( querylist[ queryid ].results );
  return 0;
}

//==============================================
//        MYSQL Field related functions
//==============================================

void db_MySQL_GetFieldByID( int queryid, int fieldid, char *buffer, int len ) {
  if( querylist[ queryid ].row[ fieldid ] )
    Q_strncpyz( buffer, querylist[ queryid ].row[ fieldid ], len );
  else
    Com_Printf( "WARNING: MySQL field %i doesnt exist.\n", fieldid );
}

void db_MySQL_GetFieldByName( int queryid, const char *name, char *buffer, int len ) {
  MYSQL_FIELD *fields;
  int num_fields;
  int i;

  if( querylist[ queryid ].results ) {
    num_fields = mysql_num_fields( querylist[ queryid ].results );
    fields = mysql_fetch_fields( querylist[ queryid ].results );

    //loop through till we find the field
    for( i = 0; i < num_fields; i++ ) {
      if( !strcmp( fields[ i ].name, name ) ) {
        //found check for valid data
        if( querylist[ queryid ].row[ i ] ) {
          Q_strncpyz( buffer, querylist[ queryid ].row[ i ], len );
          return;
        }
      }
    }
    Com_Printf( "WARNING: MySQL field %s doesnt exist.\n", name );
  }
}

int db_MySQL_GetFieldByID_int( int queryid, int fieldid ) {
  if( querylist[ queryid ].row[ fieldid ] )
    return atoi( querylist[ queryid ].row[ fieldid ] );
  else {
    Com_Printf( "WARNING: MySQL field %i doesnt exist.\n", fieldid );
    return 0;
  }
  return 0;
}

int db_MySQL_GetFieldByName_int( int queryid, const char *name ) {
  MYSQL_FIELD *fields;
  int num_fields;
  int i;

  if( querylist[ queryid ].results ) {
    num_fields = mysql_num_fields( querylist[ queryid ].results );
    fields = mysql_fetch_fields( querylist[ queryid ].results );

    //loop through till we find the field
    for( i = 0; i < num_fields; i++ ) {
      if( !strcmp( fields[ i ].name, name ) ) {
        //found check for valid data
        if( querylist[ queryid ].row[ i ] ) {
          return atoi( querylist[ queryid ].row[ i ] );
        }
      }
    }
    Com_Printf( "WARNING: MySQL field %s doesnt exist.\n", name );
  }
  return 0;
}

int db_MySQL_FieldCount( int queryid ) {
  if( querylist[ queryid ].results )
    return mysql_num_fields( querylist[ queryid ].results );
  return 0;
}

//==============================================
//        MYSQL Misc functions
//==============================================

void db_MySQL_CleanString( const char *in, char *out, int len ) {
  if( connection && len > 0 && in[0] ) {
    mysql_real_escape_string( connection, out, in, len );
  }
}
