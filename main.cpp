#include <iostream>
#include <mysql/mysql.h>

using namespace std;

struct connection_details
{
    const char *server, *user, *password, *database;
};

MYSQL *mysql_connection_setup(struct connection_details mysql_details)
{
    MYSQL *connection = mysql_init(NULL);

    if (!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0))
    {
        cout << "Connection Error: " << mysql_error(connection) << endl;
        exit(1);
    }

    return connection;
}

MYSQL_RES *mysql_execute_query(MYSQL *connection, const char *sql_query)
{
    if (mysql_query(connection, sql_query))
    {
        cout << "MySQL query error: " << mysql_error(connection) << endl;
        exit(1);
    }

    return mysql_use_result(connection);
}

int main(int argc, char const *argv[])
{
    MYSQL *con;
    MYSQL_RES *res;
    MYSQL_ROW row;

    struct connection_details mysqlDetails;
    mysqlDetails.server = "127.0.0.1";
    mysqlDetails.user = "root";
    mysqlDetails.password = "";
    mysqlDetails.database = "test";

    con = mysql_connection_setup(mysqlDetails);
    res = mysql_execute_query(con, "SELECT * FROM User");

    cout << "Displaying database output:\n"
         << endl;

    while ((row = mysql_fetch_row(res)) != NULL)
    {
        cout << row[0] << "    |    " << row[1] << "    |    " << row[2] << endl;
    }

    mysql_free_result(res);
    mysql_close(con);

    return 0;
}
