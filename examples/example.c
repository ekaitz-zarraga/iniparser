#include<iniparse.h>

#define eprintf(format, args...) fprintf (stderr, format , ##args)
#define FREE(a) if(a!=NULL) free(a);
#define MATCH(a,b) !strcmp(a,b)

typedef struct {
    char * name;
    char * username;
    char * password;
    char * server;
} account_t;

typedef struct {
    account_t ** account;
    size_t size;
} account_list;

account_t * create_account( void );
void delete_account( account_t * account);
int account_set_field( char ** field, char * value);
void print_account( account_t * account );

int read_conf ( char * section, char * key, char * value, void * data){
    printf("SECTION:%s\tKEY:%s\tVALUE:%s\t\n", section, key, value);
    account_list * accounts = (account_list *) data;
    int i;

    // Search if the account name exists
    for(i=0; i < accounts->size; i++){
        if( MATCH(accounts->account[i]->name, section ) ){
            break;
        }
    }

    if (i == accounts->size){
        // Account name does not exist -> create it
        accounts->size++;
        accounts->account = realloc( accounts->account, sizeof(account_t *) * accounts->size );
        if(!accounts->account){
            fprintf(stderr, "Error reallocating account list\n");
            return 1;
        }
        accounts->account[i] = create_account();
        if(!accounts->account[i])
            return 1;
        account_set_field( &accounts->account[i]->name, section);
        print_account( accounts->account[i] );
    }

    // Fill key-value pair in the account if they are not filled
    int retval=1;
    if( MATCH(key, "username") ){
        retval = account_set_field( &accounts->account[i]->username, value );
    }else if(MATCH(key, "password")){
        retval = account_set_field( &accounts->account[i]->password, value );
    }else if(MATCH(key, "server")){
        retval = account_set_field( &accounts->account[i]->server, value );
    }
    print_account( accounts->account[i] );
    return retval;
}

int main(int argc, char * argv []){
    account_list accounts;
    accounts.size=0;
    accounts.account=NULL;

    // CALL THE PARSER HERE
    parse_ini( "email.conf", &accounts, read_conf );

    fprintf(stderr, "Parsing finished\n");

    int i;
    for(i=0; i<accounts.size; i++){
        delete_account(accounts.account[i]);
    }
    FREE(accounts.account);
    return 0;
}

account_t * create_account( void ){
    account_t * account;
    account = (account_t *) malloc( sizeof(account_t) );
    if(account==NULL){
        fprintf(stderr, "Error allocating account\n");
        return NULL;
    }
    account->name = NULL;
    account->username = NULL;
    account->password = NULL;
    account->server = NULL;
    return account;
}

void delete_account( account_t * account ){
    FREE(account->name);
    FREE(account->username);
    FREE(account->password);
    FREE(account->server);
    FREE(account);
}

int account_set_field( char ** field, char * value){
    if( *field ){
        // Field is set, exit with error
        fprintf( stderr, "Trying to write a previously written field\n" );
        return 1;
    }

    *field  = (char *) malloc(sizeof(char) * (strlen(value)+1));
    if( !*field ) {
        *field = NULL;
        fprintf( stderr, "Field memory allocation failed\n" );
        return 1;
    }
    strcpy(*field, value);
    return 0;
}

void print_account( account_t * account ){

    printf("Name: %s\n  Username: %s\n  Password: %s\n  Server: %s\n\n",
            account->name,
            account->username,
            account->password,
            account->server);
}
