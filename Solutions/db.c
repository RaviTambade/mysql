#include <stdio.h>
#include <mysql.h>

int main() {

    printf("Hello.\n");
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // 1. Initialize MySQL connection object
    conn = mysql_init(NULL);

    // 2. Connect to the database
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "ecommerce", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // 3.Run a query
    if (mysql_query(conn, "SELECT * FROM product")) {
        fprintf(stderr, "SELECT query failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // 4.Store the result
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // 5. Fetch and display the rows
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("ID: %s, Name: %s\n", row[0], row[1]);
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);

    printf("Done.\n");
    
    return EXIT_SUCCESS;
}






//gcc db.c -o db.exe -I"C:\Program Files\MySQL\MySQL Server 8.4\include"
// -L"C:\Program Files\MySQL\MySQL Server 8.4\lib" -l libmysql