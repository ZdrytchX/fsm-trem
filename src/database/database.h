#ifndef DATABASE_H
#define DATABASE_H

#include "../qcommon/q_shared.h"
#include "../qcommon/qcommon.h"

//cvars
extern cvar_t *db_backend;
extern cvar_t *db_status; 

extern cvar_t *db_address;
extern cvar_t *db_port;
extern cvar_t *db_username;
extern cvar_t *db_password;
extern cvar_t *db_database;

//databse interface object
typedef struct
{
  //inti/destroy function
  //void     (*InitDB)( void );
  //void     (*DestroyDB)( void );

  //Connection related functins
  void     (*DBConnect)( void );
  void     (*DBStatus)( void );
  void     (*DBDisconnect)( void );

  //query related functions
  int      (*RunQuery)( const char *query );
  void     (*FinishQuery)( int queryid );

  //query result row manipulation
  qboolean (*NextRow)( int queryid );
  //int      (*RowID)( int queryid );
  //qboolean (*GotoRowID( int queryid, int rowid );
  int      (*RowCount)( int queryid );

  //query result data manipulation
  void     (*GetFieldByID)( int queryid, int fieldid, char *buffer, int len );
  void     (*GetFieldByName)( int queryid, const char *name, char *buffer, int len );
  int      (*GetFieldByID_int)( int queryid, int fieldid );
  int      (*GetFieldByName_int)( int queryid, const char *name );
  int      (*FieldCount)( int queryid );

  //string cleaning
  void (*CleanString)( const char *in, char *out, int len );
} dbinterface_t;

//database system functions
void DB_Init( void );
void DB_Shutdown( void );

void DB_Connect( void );
void DB_Status( void );
void DB_Disconnect( void );

int DB_RunQuery( const char *query );
void DB_FinishQuery( int queryid );

qboolean DB_NextRow( int queryid );
//int DB_GetRowID( int queryid );
//qboolean DB_GotoRowID( int queryid, int rowid );
int DB_RowCount( int queryid );

void DB_GetFieldByID( int queryid, int fieldid, char *buffer, int len );
void DB_GetFieldByName( int queryid, const char *name, char *buffer, int len );
int DB_GetFieldByID_int( int queryid, int fieldid );
int DB_GetFieldByName_int( int queryid, const char *name );
int DB_FieldCount( int queryid );

void DB_CleanString( const char *in, char *out, int len );

//=============================================
//         MySQL functions
//=============================================
qboolean db_MySQL_Init( dbinterface_t *dbi );

//==============================================
//        MYSQL Connecting related functions
//==============================================

void db_MySQL_Connect( void );
void db_MySQL_DBStatus( void );
void db_MySQL_Disconnect( void );
//==============================================
//        MYSQL Query related functions
//==============================================

int db_MySQL_RunQuery( const char *query );
void db_MySQL_FinishQuery( int queryid );

//==============================================
//        MYSQL ROW related functions
//==============================================

qboolean db_MySQL_NextRow( int queryid );
int db_MySQL_RowCount( int queryid );

//==============================================
//        MYSQL Field related functions
//==============================================

void db_MySQL_GetFieldByID( int queryid, int fieldid, char *buffer, int len );
void db_MySQL_GetFieldByName( int queryid, const char *name, char *buffer, int len );
int db_MySQL_GetFieldByID_int( int queryid, int fieldid );
int db_MySQL_GetFieldByName_int( int queryid, const char *name );
int db_MySQL_FieldCount( int queryid );

void db_MySQL_CleanString( const char *in, char *out, int len );

/*TODO: PgSQL functions
//=============================================
//         PgSql functions
//=============================================

qboolean db_PgSQL_Init( dbinterface_t *dbi );

//==============================================
//        PGSQL Query related functions
//==============================================

int db_PgSQL_RunQuery( const char *query );
void db_PgSQL_FinishQuery( int queryid );
//==============================================
//        PGSQL ROW related functions
//==============================================

qboolean db_PgSQL_NextRow( int queryid );
int db_PgSQL_RowCount( int queryid );

//==============================================
//        PGSQL Field related functions
//==============================================

void db_PgSQL_GetFieldByID( int queryid, int fieldid, char *buffer, int len );
void db_PgSQL_GetFieldByName( int queryid, const char *name, char *buffer, int len );
int db_PgSQL_GetFieldByID_int( int queryid, int fieldid );
int db_PgSQL_GetFieldByName_int( int queryid, const char *name );
int db_PgSQL_FieldCount( int queryid );

//==============================================
//        MYSQL Misc functions
//==============================================

void db_PgSQL_CleanString( const char *in, char *out, int len );
*/

#endif
