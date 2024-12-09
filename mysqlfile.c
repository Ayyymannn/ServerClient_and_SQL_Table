#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
int add_book(MYSQL *conn, char *title, char *author, int year) {
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO books (title, author, year) VALUES ('%s', '%s', %d);", title, author, year);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
    }else{
        printf("Book Added\n");
    }
}

int display_books(MYSQL *conn){
    const char *query = "SELECT * FROM books;";
    MYSQL_RES *res; // Result set for queries
    MYSQL_ROW row; // Row in the result set

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
    }

    // Store the result set
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Failed to retrieve result set: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Display the result set
    printf("Query Results:\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (int i = 0; i < mysql_num_fields(res); i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
        }

    mysql_free_result(res);
}

int matching_books(MYSQL *conn, char* title){
    char query[512];
    MYSQL_RES *res; // Result set for queries
    MYSQL_ROW row; // Row in the result set

    snprintf(query, sizeof(query), "SELECT * FROM books WHERE title LIKE '%s';", title);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
    }

    // Store the result set
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Failed to retrieve result set: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Display the result set
    printf("Query Results:\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (int i = 0; i < mysql_num_fields(res); i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
        }

    mysql_free_result(res);
}

int main(){
    MYSQL *conn; // MySQL connection handle
    MYSQL_RES *res; // Result set for queries
    MYSQL_ROW row; // Row in the result set
    // MySQL server details
    const char *server = "127.0.0.1";
    // Use IP or "localhost"
    const char *user = "root"; // MySQL username
    const char *password = "root";
    // MySQL password
    const char *database = "library_db";
    // Name of the database
    // Initialize MySQL connection
    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    add_book(conn,"book1", "author1", 2019);
    add_book(conn,"book2", "author2", 2020);
    add_book(conn,"book3", "author3", 2021);
    add_book(conn,"book4", "author4", 2022);
    add_book(conn,"book5", "author5", 2023);

    int c = 0;
    while (1) {
        char title[255] = {0};
        char author[255] = {0};
        int year = 0;
        printf("\nConnected to the MySQL database successfully.\n");
        printf("Press 1: Add new book\n");
        printf("Press 2: View all books\n");
        printf("Press 3: Search for a book by title\n");
        printf("Press 4: Exit\n");
        scanf("%d", &c);

        switch (c) {
            case 1:
                printf("Insert title: ");
                scanf(" %s", title);
                printf("Insert author: ");
                scanf(" %s", author);
                printf("Insert year: ");
                scanf(" %d", &year);
                add_book(conn, title, author, year);
                break;
            case 2:
                display_books(conn);
                break;
            case 3:
                printf("Insert title: ");
                scanf(" %s", title);
                matching_books(conn, title);
                break;
            case 4:
                mysql_close(conn);
                printf("Connection closed\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice\n");
        }
    }

    // Free result set and close connection
    mysql_close(conn);
    printf("Connection closed.\n");
    return EXIT_SUCCESS;
}
