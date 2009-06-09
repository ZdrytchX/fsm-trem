#include "database.h"

//cvars
cvar_t *db_enable;
cvar_t *db_backend;
cvar_t *db_status;

cvar_t *db_address;
cvar_t *db_port;
cvar_t *db_username;
cvar_t *db_password;
cvar_t *db_database;

static dbinterface_t dbi;

qboolean DB_ValidateInterface( dbinterface_t *dbi ) {
  //if( !dbi.InitDB ) return qfalse;
  //if( !dbi.DestroyDB ) return qfalse;

  if( !dbi->DBConnect ) return qfalse;
  if( !dbi->DBStatus ) return qfalse;
  if( !dbi->DBDisconnect ) return qfalse;

  if( !dbi->RunQuery ) return qfalse;
  if( !dbi->FinishQuery ) return qfalse;

  if( !dbi->NextRow ) return qfalse;
  //if( !dbi.RowID ) return qfalse;
  //if( !dbi.GotoRowID ) return qfalse;
  if( !dbi->RowCount ) return qfalse;

  if( !dbi->GetFieldByID ) return qfalse;
  if( !dbi->GetFieldByName ) return qfalse;
  if( !dbi->GetFieldByID_int ) return qfalse;
  if( !dbi->GetFieldByName_int ) return qfalse;
  if( !dbi->FieldCount ) return qfalse;

  if( !dbi->CleanString ) return qfalse;

  return qtrue;
}

void DB_Init( void ) {
  qboolean started = qfalse;

  Com_Printf( "------ Initializing Database ------\n" );
  db_enable = Cvar_Get( "db_enable", "0", CVAR_ARCHIVE );;
  db_backend = Cvar_Get( "db_backend", "MySQL", CVAR_ARCHIVE );
  db_status = Cvar_Get( "db_status", "0", CVAR_ROM );

  db_address = Cvar_Get( "db_address", "127.0.0.1", CVAR_ARCHIVE );
  db_port = Cvar_Get( "db_port", "", CVAR_ARCHIVE );
  db_username = Cvar_Get( "db_username", "tremulous", CVAR_ARCHIVE );
  db_password = Cvar_Get( "db_password", "", CVAR_ARCHIVE );
  db_database = Cvar_Get( "db_database", "tremulous", CVAR_ARCHIVE );
  
  if( db_enable->integer == 0 ) {
    Com_Printf( "Database Disabled.\n" );
  } else {
    if( strstr( db_backend->string, "MySQL" ) ) {
      started = db_MySQL_Init( &dbi );
    } else if( strstr( db_backend->string, "ProstegreSQL" ) ) {
      started = qfalse;
    } else {
      Cvar_Set( "db_enable", "0" );
      Com_Printf( "Database was set enabled but no valid backend specified.\n" );
    }

    if( started ) {
      if( !DB_ValidateInterface( &dbi ) ) {
        Com_Error( ERR_FATAL, "Database interface invalid." );
      }
    } else {
      Com_Printf( "Database Initilisation Failed.\n" );
    }
  }

  if( dbi.DBConnect ) {
    dbi.DBConnect();
    Cvar_Set( "db_status", "1" );
  }


  Com_Printf( "-----------------------------------\n" );
}

void DB_Shutdown( void ) {
  if( dbi.DBDisconnect ) {
    dbi.DBDisconnect();
    Cvar_Set( "db_status", "0" );
  }
}

void DB_Connect( void ) {
  if( dbi.DBConnect ) {
    dbi.DBConnect();
    Cvar_Set( "db_status", "1" );
  }
}

void DB_Status( void ) {
  if( dbi.DBStatus ) {
    dbi.DBStatus();
  }
}

void DB_Disconnect( void ) {
  if( dbi.DBDisconnect ) {
    dbi.DBDisconnect();
    Cvar_Set( "db_status", "0" );
  }
}

int DB_RunQuery( const char *query ) {
  if( dbi.RunQuery ) {
    return dbi.RunQuery( query );
  }
  return -1;
}

void DB_FinishQuery( int queryid ) {
  if( dbi.FinishQuery ) {
    dbi.FinishQuery( queryid );
  }
}

qboolean DB_NextRow( int queryid ) {
  if( dbi.NextRow ) {
    return dbi.NextRow( queryid );
  }
  return qfalse;
}

/*
int DB_GetRowID( int queryid ) {
  if( dbi.RowID ) {
    return dbi.RowID( queryid );
  }
}

qboolean DB_GotoRowID( int queryid, int rowid ) {
  if( dbi.GotoRowID ) {
    return dbi.GotoRowID( queryid, rowid );
  }
}
*/

int DB_RowCount( int queryid ) {
  if( dbi.RowCount ) {
    return dbi.RowCount( queryid );
  }
  return 0;
}

void DB_GetFieldByID( int queryid, int fieldid, char *buffer, int len ) {
  if( dbi.GetFieldByID ) {
    dbi.GetFieldByID( queryid, fieldid, buffer, len );
  }
}

void DB_GetFieldByName( int queryid, const char *name, char *buffer, int len ) {
  if( dbi.GetFieldByName ) {
    dbi.GetFieldByName( queryid, name, buffer, len );
  }
}

int DB_GetFieldByID_int( int queryid, int fieldid ) {
  if( dbi.GetFieldByID_int ) {
    return dbi.GetFieldByID_int( queryid, fieldid );
  }
  return 0;
}

int DB_GetFieldByName_int( int queryid, const char *name ) {
  if( dbi.GetFieldByName_int ) {
    return dbi.GetFieldByName_int( queryid, name );
  }
  return 0;
}

int DB_FieldCount( int queryid ) {
  if( dbi.FieldCount ) {
    return dbi.FieldCount( queryid );
  }
  return 0;
}

void DB_CleanString( const char *in, char *out, int len ) {
  if( dbi.CleanString ) {
    dbi.CleanString( in, out, len );
  }
}
